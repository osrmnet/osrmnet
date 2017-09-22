// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Utils.h"

#include "NearestResult.h"
#include "NearestParameters.h"

#include "osrm\json_container.hpp"

using namespace Osrmnet::NearestService;
using namespace osrm::util::json;

NearestResult^ NearestResult::FromJsonObject(const osrm::util::json::Object& jsonObject)
{
	/*
	{
		"waypoints": [ { ... } ],
		"code": "Ok"
	}
	*/

	auto result = gcnew NearestResult();

	auto codeJson = jsonObject.values.at("code").get<String>().value;
	result->Code = Osrmnet::Utils::ConvertFromUtf8(codeJson);
	
	const auto &routeWayPoints = jsonObject.values.at("waypoints").get<Array>().values;
	for (const auto &wayPointJson : routeWayPoints)
	{
		const auto &wayPointObj = wayPointJson.get<osrm::util::json::Object>();
		result->WayPoints->Add(Waypoint::FromJsonObject(wayPointObj));
	}

	return result;
}