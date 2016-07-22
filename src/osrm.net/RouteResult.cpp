// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.


#include "stdafx.h"
#include "RouteResult.h"
#include "Coordinate.h"
#include "RouteParameters.h"

#include "osrm/json_container.hpp"
#include "engine/polyline_compressor.hpp"

#include <msclr\marshal_cppstd.h>

osrmnet::RouteStep^ ProcessStep(osrm::util::json::Value jsonStep)
{
	// TODO: 0.2.x
	// Implement steps object processing


	/*const auto &stepObject = jsonStep.get<osrm::json::Object>();
	const auto distance = stepObject.values.at("distance").get<osrm::json::Number>().value;
	const auto duration = stepObject.values.at("duration").get<osrm::json::Number>().value;
	const auto summary = stepObject.values.at("name").get<osrm::json::String>().value;
	const auto mode = stepObject.values.at("mode").get<osrm::json::String>().value;
	const auto summary = stepObject.values.at("pronounciation").get<osrm::json::String>().value;

	const auto codedGeometry = stepObject.values.at("geometry").get<osrm::json::String>().value;
	const auto geometries = osrm::engine::decodePolyline(codedGeometry);
	for (const osrm::util::Coordinate &coordinate : geometries)
	{
	}


		const auto &maneuver = stepObject.values.at("maneuver").get<json::Object>().values;
	const auto type = maneuver.at("type").get<osrm::json::String>().value;*/



	return gcnew osrmnet::RouteStep();
}

osrmnet::RouteLeg^ ProcessLeg(const osrm::util::json::Value& jsonLeg, bool generateSteps, bool generateAnnotations)
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
		/* Sample Annotation json object.
		nodes include the start and the end of user supplied so it's always n+1 size
		{
			"distance": [5,5,10,5,5],
			"duration": [15,15,40,15,15],
			"datasources": [1,0,0,0,1],
			"nodes": [49772551,49772552,49786799,49786800,49786801,49786802]
		}
		*/

		auto annotation = gcnew osrmnet::Annotation();
		for (auto i = 0; i < annonDistances.size(); i++)
		{
			annotation->Distance->Add(annonDistances[i].get<osrm::json::Number>().value);
			annotation->Duration->Add(annonDuration[i].get<osrm::json::Number>().value);
		}
		for (auto i = 0; i < annonNodes.size(); i++)
		{
			annotation->Nodes->Add(static_cast<std::uint64_t>(annonNodes[i].get<osrm::json::Number>().value));
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
		const auto& routeObj = route.get<osrm::json::Object>();

		// Build RouteResult^ from json object
		RouteResult^ routeResult = gcnew RouteResult();

		routeResult->Distance = routeObj.values.at("distance").get<osrm::json::Number>().value;
		routeResult->Duration = routeObj.values.at("duration").get<osrm::json::Number>().value;

		// Process Legs
		const auto &osrmLegs = routeObj.values.at("legs").get<osrm::json::Array>().values;
		for (const auto &leg : osrmLegs)
		{
			routeResult->Legs->Add(ProcessLeg(leg, routeParameters->Steps, routeParameters->Annotations));
		}

		result->Add(routeResult);

	}

	return result;
}
