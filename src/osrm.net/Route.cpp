﻿// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.


#include "stdafx.h"
#include "Coordinate.h"
#include "Utils.h"
#include "Route.h"
#include "Waypoint.h"

#include "osrm/json_container.hpp"
#include "engine/polyline_compressor.hpp"

using namespace System::Collections::Generic;
using namespace Osrmnet;
using namespace osrm::json;

Annotation^ ProcessAnnotation(const Object jsonAnnotation, AnnotationsType annotations)
{
	if (annotations == AnnotationsType::None)
		return nullptr;
	auto annotation = gcnew Annotation();
	if (annotations.HasFlag(AnnotationsType::Speed))
	{
		const auto &annotationSpeeds = jsonAnnotation.values.at("speed").get<Array>().values;
		for (auto i = 0; i < annotationSpeeds.size(); i++)
		{
			annotation->Speed->Add(annotationSpeeds[i].get<Number>().value);
		}
	}
	if (annotations.HasFlag(AnnotationsType::Duration))
	{
		const auto &annotationDurations = jsonAnnotation.values.at("duration").get<Array>().values;
		for (auto i = 0; i < annotationDurations.size(); i++)
		{
			annotation->Duration->Add(annotationDurations[i].get<Number>().value);
		}
	}
	if (annotations.HasFlag(AnnotationsType::Nodes))
	{
		const auto &annotationNodes = jsonAnnotation.values.at("nodes").get<Array>().values;
		for (auto i = 0; i < annotationNodes.size(); i++)
		{
			annotation->Nodes->Add(static_cast<std::int64_t>(annotationNodes[i].get<Number>().value));
		}
	}
	if (annotations.HasFlag(AnnotationsType::Distance))
	{
		const auto &annotationDistances = jsonAnnotation.values.at("distance").get<Array>().values;
		for (auto i = 0; i < annotationDistances.size(); i++)
		{
			annotation->Distance->Add(annotationDistances[i].get<Number>().value);
		}
	}
	if (annotations.HasFlag(AnnotationsType::Datasources))
	{
		const auto &annotationDatasources = jsonAnnotation.values.at("datasources").get<Array>().values;
		for (auto i = 0; i < annotationDatasources.size(); i++)
		{
			annotation->Datasources->Add(static_cast<std::int32_t>(annotationDatasources[i].get<Number>().value));
		}
	}
	if (annotations.HasFlag(AnnotationsType::Weight))
	{
		const auto &annotationWeights = jsonAnnotation.values.at("weight").get<Array>().values;
		for (auto i = 0; i < annotationWeights.size(); i++)
		{
			annotation->Weight->Add(annotationWeights[i].get<Number>().value);
		}
	}
	return annotation;
}

Geometry^ ProcessGeometry(const Value jsonValue, GeometriesType geometries)
{
	auto result = gcnew Geometry();
	switch (geometries)
	{
	case GeometriesType::Polyline:
	case GeometriesType::Polyline6:
	{
		const auto encoded = jsonValue.get<osrm::json::String>().value;
		result->Encoded = Osrmnet::Utils::ConvertFromUtf8(encoded);
		break;
	}
	case GeometriesType::GeoJSON:
	{
		/*
		{
			"type": "LineString",
			"coordinates": [
				[
					2.349566,
					48.82971
				]
			]
		}
		*/
		const auto &geometryObject = jsonValue.get<Object>();
		const auto type = geometryObject.values.at("type").get<String>().value;
		result->Type = Osrmnet::Utils::ConvertFromUtf8(type);
		const auto& coordinates = geometryObject.values.at("coordinates").get<osrm::json::Array>().values;
		for (const auto &coordinate : coordinates)
		{
			const auto &location = coordinate.get<Array>().values;
			result->Coordinates->Add(gcnew Coordinate(location[1].get<Number>().value, location[0].get<Number>().value));
		}
		break;
	}
	default:
		break;
	}
	return result;
}

Lane^ ProcessLane(const Value jsonLane)
{
	/*
	{
		"indications": [
			"straight"
		],
		"valid" : true
	}
	*/

	auto result = gcnew Lane();
	const auto &lane = jsonLane.get<Object>();

	const auto &indications = lane.values.at("indications").get<Array>().values;
	for (const auto &indication : indications)
	{
		result->Indications->Add(Osrmnet::Utils::ConvertFromUtf8(indication.get<String>().value));
	}
	result->Valid = lane.values.at("valid").is<True>();
	return result;
}

Intersection^ ProcessIntersection(const Value jsonIntersection)
{
	/*
	{
		"location": [
			2.346587,
			48.825755
		],
		"in": 0,
		"bearings": [
			0,
			105,
			180,
			285
		],
		"entry": [
			false,
			true,
			true,
			true
		],
		"out": 1
	}
	*/

	auto result = gcnew Intersection();
	const auto &intersection = jsonIntersection.get<Object>();

	// In and Out
	// in or out can be there or not depending on maneuver type	
	if (intersection.values.count("out") > 0)
	{
		result->Out = System::Convert::ToInt32(intersection.values.at("out").get<Number>().value);
	}
	if (intersection.values.count("in") > 0)
	{
		result->In = System::Convert::ToInt32(intersection.values.at("in").get<Number>().value);

	}

	// Entry collections
	const auto &entries = intersection.values.at("entry").get<Array>().values;
	for (const auto &entry : entries)
	{
		bool entryTrue = entry.is<True>();
		result->Entry->Add(entryTrue);
	}

	// Bearings
	const auto &bearings = intersection.values.at("bearings").get<Array>().values;
	for (const auto &bearing : bearings)
	{
		result->Bearings->Add(System::Convert::ToInt32(bearing.get<Number>().value));
	}

	// Lanes
	// Lanes can be optional
	if (intersection.values.count("lanes") > 0)
	{
		const auto &lanes = intersection.values.at("lanes").get<Array>().values;
		for (const auto &lane : lanes)
		{
			result->Lanes->Add(ProcessLane(lane));
		}
	}

	// Location
	// Caution osrm is long,lat but osrmnet is lat,long just like google
	const auto &location = intersection.values.at("location").get<Array>().values;
	result->Location = gcnew Osrmnet::Coordinate(location[1].get<Number>().value, location[0].get<Number>().value);
	return result;
}

StepManeuver^ ProcessManeuver(Object jsonManeuver)
{
	/*
	{
		"type": "merge",
		"exit": 1,
		"modifier": "slight right",
		"location": [
			2.423833,
			48.620961
		],
		"bearing_before": 149,
		"bearing_after": 136
	},
	*/

	auto result = gcnew StepManeuver();
	result->BearingAfter = System::Convert::ToInt32(jsonManeuver.values.at("bearing_after").get<Number>().value);
	result->BearingBefore = System::Convert::ToInt32(jsonManeuver.values.at("bearing_before").get<Number>().value);
	result->Type = Osrmnet::Utils::ConvertFromUtf8(jsonManeuver.values.at("type").get<String>().value);
	const auto &location = jsonManeuver.values.at("location").get<Array>().values;
	result->Location = gcnew Osrmnet::Coordinate(location[1].get<Number>().value, location[0].get<Number>().value);

	// Optional Modifier property
	if(jsonManeuver.values.count("modifier"))
	{
		result->Modifier = Osrmnet::Utils::ConvertFromUtf8(jsonManeuver.values.at("modifier").get<String>().value);
	}

	// Optional Exit property
	if (jsonManeuver.values.count("exit"))
	{
		result->Exit = System::Convert::ToInt32(jsonManeuver.values.at("exit").get<Number>().value);
	}
	return result;
}

RouteStep^ ProcessStep(Value jsonStep, GeometriesType geometries)
{
	/*
	{
		"distance": 83.7,
		"mode": "driving",
		"duration": 14.8,
		"weight": 14.8,
		"geometry": ...,
		"intersections": [ Intersection,... ],
		"name": "Boulevard Auguste Blanqui",
		"maneuver": StepManeuver
	}
	*/

	auto routeStep = gcnew RouteStep();

	const auto &stepObject = jsonStep.get<Object>();
	const auto distance = stepObject.values.at("distance").get<Number>().value;
	const auto duration = stepObject.values.at("duration").get<Number>().value;
	const auto name = stepObject.values.at("name").get<String>().value;
	const auto mode = stepObject.values.at("mode").get<String>().value;

	routeStep->Geometry = ProcessGeometry(stepObject.values.at("geometry"), geometries);
	routeStep->Mode = Osrmnet::Utils::ConvertFromUtf8(mode);
	routeStep->Duration = duration;
	routeStep->Distance = distance;
	routeStep->Name = Osrmnet::Utils::ConvertFromUtf8(name);

	// Create maneuver
	routeStep->Maneuver = ProcessManeuver(stepObject.values.at("maneuver").get<Object>());

	// Create intersections
	const auto &intersections = stepObject.values.at("intersections").get<Array>().values;
	for (const auto &intersection : intersections)
	{
		routeStep->Intersections->Add(ProcessIntersection(intersection));
	}

	// Process optional properties
	if (stepObject.values.count("weight") > 0)
	{
		routeStep->Weight = stepObject.values.at("weight").get<Number>().value;
	}

	if (stepObject.values.count("pronounciation") > 0)
	{
		routeStep->Pronounciation = Osrmnet::Utils::ConvertFromUtf8(stepObject.values.at("pronounciation").get<String>().value);
	}

	if (stepObject.values.count("destinations") > 0)
	{
		routeStep->Destinations = Osrmnet::Utils::ConvertFromUtf8(stepObject.values.at("destinations").get<String>().value);
	}

	if (stepObject.values.count("rotary_name") > 0)
	{
		routeStep->RotaryName = Osrmnet::Utils::ConvertFromUtf8(stepObject.values.at("rotary_name").get<String>().value);
	}

	if (stepObject.values.count("rotary_pronounciation") > 0)
	{
		routeStep->RotaryName = Osrmnet::Utils::ConvertFromUtf8(stepObject.values.at("rotary_pronounciation").get<String>().value);
	}

	if (stepObject.values.count("ref") > 0)
	{
		routeStep->Ref = Osrmnet::Utils::ConvertFromUtf8(stepObject.values.at("ref").get<String>().value);
	}

	return routeStep;
}

RouteLeg^ ProcessRouteLeg(const Value& jsonLeg, bool generateSteps, AnnotationsType annotations, GeometriesType geometries)
{
	/*
	{
		"distance": 34918.3,
		"duration": 1854.1,
		"weight": 1854.1,
		"summary": "Autoroute du Soleil, Autoroute du Soleil",
		"steps": [ RouteStep,... ]
	}
	*/

	const auto &legObject = jsonLeg.get<Object>();
	const auto distance = legObject.values.at("distance").get<Number>().value;
	const auto duration = legObject.values.at("duration").get<Number>().value;
	const auto weight = legObject.values.at("weight").get<Number>().value;
	const auto summary = legObject.values.at("summary").get<String>().value;

	auto result = gcnew RouteLeg();
	result->Distance = distance;
	result->Duration = duration;
	result->Weight = weight;
	result->Summary = Osrmnet::Utils::ConvertFromUtf8(summary);

	if (generateSteps)
	{
		const auto &steps = legObject.values.at("steps").get<Array>().values;
		for (const auto &step : steps)
		{
			result->Steps->Add(ProcessStep(step, geometries));
		}
	}
	if (annotations != AnnotationsType::None)
	{
		result->Annotation = ProcessAnnotation(legObject.values.at("annotation").get<Object>(), annotations);
	}
	return result;
}

Route::Route(const osrm::json::Object &jsonRoute, bool generateSteps, AnnotationsType annotations, GeometriesType geometries, OverviewType overview) : Route()
{
	/*
	{
		"distance": 34918.3,
		"duration": 1854.1,
		"weight": 1854.1,
		"weight_name": "routability",
		"geometry": ...,
		"legs": [ RouteLeg,... ]
	}
	*/

	this->Distance = jsonRoute.values.at("distance").get<Number>().value;
	this->Duration = jsonRoute.values.at("duration").get<Number>().value;
	this->Weight = jsonRoute.values.at("weight").get<osrm::json::Number>().value;
	this->WeightName = Osrmnet::Utils::ConvertFromUtf8(jsonRoute.values.at("weight_name").get<String>().value);
	if (overview != OverviewType::False)
		this->Geometry = ProcessGeometry(jsonRoute.values.at("geometry"), geometries);

	// Process Legs
	const auto &osrmLegs = jsonRoute.values.at("legs").get<Array>().values;
	for (const auto &leg : osrmLegs)
	{
		this->Legs->Add(ProcessRouteLeg(leg, generateSteps, annotations, geometries));
	}
}

Route^ Route::FromJsonObject(const osrm::json::Object &jsonRoute, bool generateSteps, AnnotationsType annotations, GeometriesType geometries, OverviewType overview)
{
	return gcnew Route(jsonRoute, generateSteps, annotations, geometries, overview);
}