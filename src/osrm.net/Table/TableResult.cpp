// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Utils.h"

#include "TableResult.h"
#include "TableParameters.h"

#include "osrm\json_container.hpp"

using namespace Osrmnet::TableService;
using namespace osrm::util::json;

TableResult^ TableResult::FromJsonObject(const osrm::util::json::Object& jsonObject)
{
	/*
	{
		"sources": [ Waypoint,... ],
		"destinations": [ Waypoint,... ],
		"code": "Ok"
		"durations": [
			[
				0,
				1854.1
			],
			[
				1801.4,
				0
			]
		],
		}
	*/

	auto result = gcnew TableResult();

	const auto &sources = jsonObject.values.at("sources").get<Array>().values;
	for (const auto &source : sources)
	{
		const auto &sourceObject = source.get<osrm::util::json::Object>();
		result->Sources->Add(Waypoint::FromJsonObject(sourceObject));
	}

	const auto &destinations = jsonObject.values.at("destinations").get<Array>().values;
	for (const auto &destination : destinations)
	{
		const auto &destinationObject = destination.get<osrm::util::json::Object>();
		result->Destinations->Add(Waypoint::FromJsonObject(destinationObject));
	}

	auto code = jsonObject.values.at("code").get<String>().value;
	result->Code = Osrmnet::Utils::ConvertFromUtf8(code);


	// durations (optional)
	if (jsonObject.values.find("durations") != jsonObject.values.end()) {
		const auto &durations = jsonObject.values.at("durations").get<Array>().values;
		for (const auto &duration : durations)
		{
			auto values = gcnew List<double>();
			const auto &jsonValues = duration.get<Array>().values;
			for (const auto &jsonValue : jsonValues)
				values->Add(jsonValue.get<Number>().value);
			result->Durations->Add(values);
		}
	}

	// distance (optional)
	if (jsonObject.values.find("distances") != jsonObject.values.end()) {
		const auto &distances = jsonObject.values.at("distances").get<Array>().values;
		for (const auto &distance : distances)
		{
			auto values = gcnew List<double>();
			const auto &jsonValues = distance.get<Array>().values;
			for (const auto &jsonValue : jsonValues)
				values->Add(jsonValue.get<Number>().value);
			result->Distances->Add(values);
		}
	}

	return result;
}