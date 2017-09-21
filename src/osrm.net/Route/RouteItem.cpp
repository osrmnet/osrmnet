// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.


#include "..\stdafx.h"
#include "..\Coordinate.h"
#include "..\Utils.h"

#include "RouteLeg.h"
#include "RouteParameters.h"
#include "RouteItem.h"
#include "RouteWayPoint.h"


#include "osrm/json_container.hpp"
#include "engine/polyline_compressor.hpp"
#include <msclr\marshal_cppstd.h>

using namespace System::Collections::Generic;
using namespace Osrmnet;
using namespace Osrmnet::Route;
using namespace osrm::json;


Intersection^ ProcessIntersection(const Value jsonIntersection)
{
	auto result = gcnew Intersection();
	const auto &intersection = jsonIntersection.get<Object>();

	// In and Out
	// in or out can be there or not depending on maneuver type	
	if(intersection.values.count("out") > 0)
	{
		result->Out = System::Convert::ToInt32(intersection.values.at("out").get<Number>().value);
	}
	if(intersection.values.count("in") > 0)
	{
		result->In = System::Convert::ToInt32(intersection.values.at("in").get<Number>().value);

	}

	// Entry collections
	const auto& entryList = intersection.values.at("entry").get<Array>().values;
	for(const auto &entry : entryList)
	{
		bool entryTrue = entry.is<True>();
		result->Entry->Add(entryTrue);
	}

	// Bearings
	const auto& bearings = intersection.values.at("bearings").get<Array>().values;
	for (const auto &bearing : bearings)
	{
		result->Bearings->Add(System::Convert::ToInt32(bearing.get<Number>().value));
	}

	// Lanes
	// Lanes can be optional
	if (intersection.values.count("lanes") > 0)
	{
		const auto& laneList = intersection.values.at("lanes").get<Array>().values;
		for (const auto &lane : laneList)
		{
			result->Lanes->Add(Osrmnet::Utils::ConvertFromUtf8(lane.get<String>().value));
		}
	}

	// Location
	// Caution osrm is long,lat but osrmnet is lat,long just like google
	const auto &location = intersection.values.at("location").get<Array>().values;
	result->Location = gcnew Osrmnet::Coordinate(location[1].get<Number>().value, location[0].get<Number>().value);

	return result;
}

Maneuver^ ProcessManeuver(Object jsonManeuver)
{
	auto result = gcnew Maneuver();
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

RouteStep^ ProcessStep(Value jsonStep)
{
	auto routeStep = gcnew RouteStep();

	const auto &stepObject = jsonStep.get<Object>();
	const auto distance = stepObject.values.at("distance").get<Number>().value;
	const auto duration = stepObject.values.at("duration").get<Number>().value;
	const auto name = stepObject.values.at("name").get<String>().value;
	const auto mode = stepObject.values.at("mode").get<String>().value;
	const auto geometry = stepObject.values.at("geometry").get<String>().value;
	
	routeStep->Geometry = Osrmnet::Utils::ConvertFromUtf8(geometry);
	routeStep->Mode = Osrmnet::Utils::ConvertFromUtf8(mode);
	routeStep->Duration = duration;
	routeStep->Distance = distance;
	routeStep->Name = Osrmnet::Utils::ConvertFromUtf8(name);

	// Create maneuver
	routeStep->Maneuver = ProcessManeuver(stepObject.values.at("maneuver").get<Object>());	

	// Create intersections
	const auto &intersections = stepObject.values.at("intersections").get<Array>().values;
	for(const auto &intersection : intersections)
	{
		routeStep->Intersections->Add(ProcessIntersection(intersection));
	}

	// Process optional properties
	if(stepObject.values.count("weight") > 0)
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

	return routeStep;
}

RouteLeg^ ProcessRouteLeg(const Value& jsonLeg, bool generateSteps, bool generateAnnotations)
{
	const auto &legObject = jsonLeg.get<Object>();
	const auto distance = legObject.values.at("distance").get<Number>().value;
	const auto duration = legObject.values.at("duration").get<Number>().value;
	const auto summary = legObject.values.at("summary").get<String>().value;

	auto result = gcnew RouteLeg();
	result->Distance = distance;
	result->Duration = duration;
	result->Summary = Osrmnet::Utils::ConvertFromUtf8(summary);

	if (generateSteps)
	{
		const auto &steps = legObject.values.at("steps").get<Array>().values;
		for (const auto &step : steps)
		{
			result->Steps->Add(ProcessStep(step));

		}
	}
	if (generateAnnotations)
	{
		const auto &annotationObj = legObject.values.at("annotation").get<Object>();
		const auto &annonDistances = annotationObj.values.at("distance").get<Array>().values;
		const auto &annonDuration = annotationObj.values.at("duration").get<Array>().values;
		const auto &annonNodes = annotationObj.values.at("nodes").get<Array>().values;
		auto annotation = gcnew Annotation();
		for (auto i = 0; i < annonDistances.size(); i++)
		{
			annotation->Distance->Add(annonDistances[i].get<Number>().value);
			annotation->Duration->Add(annonDuration[i].get<Number>().value);
		}
		for (auto i = 0; i < annonNodes.size(); i++)
		{
			annotation->Nodes->Add(static_cast<std::int64_t>(annonNodes[i].get<Number>().value));
		}

		result->Annotation = annotation;
	}
	return result;
}

RouteItem^ RouteItem::FromJsonObject(const osrm::json::Object& jsonRoute, RouteParameters^ routeParameters)
{
	auto result = gcnew RouteItem();

	result->Distance = jsonRoute.values.at("distance").get<Number>().value;
	result->Duration = jsonRoute.values.at("duration").get<Number>().value;
	auto geoJson = jsonRoute.values.at("geometry").get<String>().value;
	result->Geometry = Osrmnet::Utils::ConvertFromUtf8(geoJson);

	// Process Legs
	const auto &osrmLegs = jsonRoute.values.at("legs").get<Array>().values;
	for (const auto &leg : osrmLegs)
	{
		result->Legs->Add(ProcessRouteLeg(leg, routeParameters->Steps, routeParameters->Annotations));
	}
	
	return result;
}
