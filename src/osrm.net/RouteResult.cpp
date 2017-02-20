// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.


#include "stdafx.h"
#include "RouteResult.h"
#include "Coordinate.h"
#include "RouteParameters.h"

#include "osrm/json_container.hpp"
#include "engine/polyline_compressor.hpp"

#include <msclr\marshal_cppstd.h>

osrmnet::Intersection^ ProcessIntersection(const osrm::util::json::Value jsonIntersection)
{
	auto result = gcnew osrmnet::Intersection();
	const auto &intersection = jsonIntersection.get<osrm::json::Object>();

	// In and Out
	// in or out can be there or not depending on maneuver type	
	if(intersection.values.count("out") > 0)
	{
		result->Out = System::Convert::ToInt32(intersection.values.at("out").get<osrm::json::Number>().value);
	}
	if(intersection.values.count("in") > 0)
	{
		result->In = System::Convert::ToInt32(intersection.values.at("in").get<osrm::json::Number>().value);

	}

	// Entry collections
	const auto& entryList = intersection.values.at("entry").get<osrm::json::Array>().values;
	for(const auto &entry : entryList)
	{
		bool entryTrue = entry.is<osrm::json::True>();
		result->Entry->Add(entryTrue);
	}

	// Bearings
	const auto& bearings = intersection.values.at("bearings").get<osrm::json::Array>().values;
	for (const auto &bearing : bearings)
	{
		result->Bearings->Add(System::Convert::ToInt32(bearing.get<osrm::json::Number>().value));
	}

	// Lanes
	// Lanes can be optional
	if (intersection.values.count("lanes") > 0)
	{
		const auto& laneList = intersection.values.at("lanes").get<osrm::json::Array>().values;
		for (const auto &lane : laneList)
		{
			result->Lanes->Add(msclr::interop::marshal_as<System::String^>(lane.get<osrm::json::String>().value));
		}
	}

	// Location
	// Caution osrm is long,lat but osrmnet is lat,long just like google
	const auto &location = intersection.values.at("location").get<osrm::json::Array>().values;
	result->Location = gcnew osrmnet::Coordinate(location[1].get<osrm::json::Number>().value, location[0].get<osrm::json::Number>().value);

	return result;
}

osrmnet::Maneuver^ ProcessManeuver(osrm::util::json::Object jsonManeuver)
{
	auto result = gcnew osrmnet::Maneuver();
	result->BearingAfter = System::Convert::ToInt32(jsonManeuver.values.at("bearing_after").get<osrm::json::Number>().value);
	result->BearingBefore = System::Convert::ToInt32(jsonManeuver.values.at("bearing_before").get<osrm::json::Number>().value);
	result->Type = msclr::interop::marshal_as<System::String^>(jsonManeuver.values.at("type").get<osrm::json::String>().value);
	const auto &location = jsonManeuver.values.at("location").get<osrm::json::Array>().values;
	result->Location = gcnew osrmnet::Coordinate(location[1].get<osrm::json::Number>().value, location[0].get<osrm::json::Number>().value);

	// Optional Modifier property
	if(jsonManeuver.values.count("modifier"))
	{
		result->Modifier = msclr::interop::marshal_as<System::String^>(jsonManeuver.values.at("modifier").get<osrm::json::String>().value);
	}

	// Optional Exit property
	if (jsonManeuver.values.count("exit"))
	{
		result->Exit = System::Convert::ToInt32(jsonManeuver.values.at("exit").get<osrm::json::Number>().value);
	}

	return result;
}

osrmnet::RouteStep^ ProcessStep(osrm::util::json::Value jsonStep)
{
	auto routeStep = gcnew osrmnet::RouteStep();

	const auto &stepObject = jsonStep.get<osrm::json::Object>();
	const auto distance = stepObject.values.at("distance").get<osrm::json::Number>().value;
	const auto duration = stepObject.values.at("duration").get<osrm::json::Number>().value;
	const auto name = stepObject.values.at("name").get<osrm::json::String>().value;
	const auto mode = stepObject.values.at("mode").get<osrm::json::String>().value;
	const auto geometry = stepObject.values.at("geometry").get<osrm::json::String>().value;
	
	routeStep->Geometry = msclr::interop::marshal_as<System::String^>(geometry);
	routeStep->Mode = msclr::interop::marshal_as<System::String^>(mode);
	routeStep->Duration = duration;
	routeStep->Distance = distance;
	routeStep->Name = msclr::interop::marshal_as<System::String^>(name);

	// Create maneuver
	routeStep->Maneuver = ProcessManeuver(stepObject.values.at("maneuver").get<osrm::json::Object>());	

	// Create intersections
	const auto &intersections = stepObject.values.at("intersections").get<osrm::json::Array>().values;
	for(const auto &intersection : intersections)
	{
		routeStep->Intersections->Add(ProcessIntersection(intersection));
	}

	// Process optional properties
	if(stepObject.values.count("weight") > 0)
	{
		routeStep->Weight = stepObject.values.at("weight").get<osrm::json::Number>().value;
	}

	if (stepObject.values.count("pronounciation") > 0)
	{
		routeStep->Pronounciation = msclr::interop::marshal_as<System::String^>(stepObject.values.at("pronounciation").get<osrm::json::String>().value);
	}

	if (stepObject.values.count("destinations") > 0)
	{
		routeStep->Destinations = msclr::interop::marshal_as<System::String^>(stepObject.values.at("destinations").get<osrm::json::String>().value);
	}

	if (stepObject.values.count("rotary_name") > 0)
	{
		routeStep->RotaryName = msclr::interop::marshal_as<System::String^>(stepObject.values.at("rotary_name").get<osrm::json::String>().value);
	}

	if (stepObject.values.count("rotary_pronounciation") > 0)
	{
		routeStep->RotaryName = msclr::interop::marshal_as<System::String^>(stepObject.values.at("rotary_pronounciation").get<osrm::json::String>().value);
	}

	return routeStep;
}

osrmnet::RouteLeg^ ProcessRouteLeg(const osrm::util::json::Value& jsonLeg, bool generateSteps, bool generateAnnotations)
{
	const auto &legObject = jsonLeg.get<osrm::json::Object>();
	const auto distance = legObject.values.at("distance").get<osrm::json::Number>().value;
	const auto duration = legObject.values.at("duration").get<osrm::json::Number>().value;
	const auto summary = legObject.values.at("summary").get<osrm::json::String>().value;

	auto result = gcnew osrmnet::RouteLeg();
	result->Distance = distance;
	result->Duration = duration;
	result->Summary = msclr::interop::marshal_as<System::String^>(summary);

	if (generateSteps)
	{
		const auto &steps = legObject.values.at("steps").get<osrm::json::Array>().values;
		for (const auto &step : steps)
		{
			result->Steps->Add(ProcessStep(step));

		}
	}
	if (generateAnnotations)
	{
		const auto &annotationObj = legObject.values.at("annotation").get<osrm::json::Object>();
		const auto &annonDistances = annotationObj.values.at("distance").get<osrm::json::Array>().values;
		const auto &annonDuration = annotationObj.values.at("duration").get<osrm::json::Array>().values;
		const auto &annonNodes = annotationObj.values.at("nodes").get<osrm::json::Array>().values;
		auto annotation = gcnew osrmnet::Annotation();
		for (auto i = 0; i < annonDistances.size(); i++)
		{
			annotation->Distance->Add(annonDistances[i].get<osrm::json::Number>().value);
			annotation->Duration->Add(annonDuration[i].get<osrm::json::Number>().value);
		}
		for (auto i = 0; i < annonNodes.size(); i++)
		{
			annotation->Nodes->Add(static_cast<std::int64_t>(annonNodes[i].get<osrm::json::Number>().value));
		}

		result->Annotation = annotation;
	}
	return result;
}

System::Collections::Generic::IEnumerable<osrmnet::RouteResult^>^ osrmnet::RouteResult::FromJsonObject(osrm::util::json::Object& jsonResult, osrmnet::RouteParameters^ routeParameters)
{
	using namespace osrmnet;

	auto result = gcnew System::Collections::Generic::List<RouteResult^>();

	auto &routes = jsonResult.values["routes"].get<osrm::json::Array>().values;
	for (const auto& route : routes)
	{
		RouteResult^ routeResult = gcnew RouteResult();

		const auto& routeObj = route.get<osrm::json::Object>();
		routeResult->Distance = routeObj.values.at("distance").get<osrm::json::Number>().value;
		routeResult->Duration = routeObj.values.at("duration").get<osrm::json::Number>().value;

		// Process Legs
		const auto &osrmLegs = routeObj.values.at("legs").get<osrm::json::Array>().values;
		for (const auto &leg : osrmLegs)
		{
			routeResult->Legs->Add(ProcessRouteLeg(leg, routeParameters->Steps, routeParameters->Annotations));
		}

		result->Add(routeResult);

	}

	return result;
}
