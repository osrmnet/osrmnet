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
		"waypoints": [ { ... } ],
		"code": "Ok"
	}
	*/

	auto result = gcnew TableResult();

	auto codeJson = jsonObject.values.at("code").get<String>().value;
	result->Code = Osrmnet::Utils::ConvertFromUtf8(codeJson);
	
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

	return result;
}