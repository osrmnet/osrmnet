// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Coordinate.h"
#include "..\Utils.h"

#include "MatchWaypoint.h"

#include "osrm/json_container.hpp"

using namespace Osrmnet::MatchService;
using namespace osrm::util::json;

MatchWaypoint::MatchWaypoint(const osrm::util::json::Object& jsonObject) : Waypoint(jsonObject)
{
}

MatchWaypoint^ MatchWaypoint::FromJsonObject(const osrm::util::json::Object& jsonObject)
{
	/*
	{
		"location": [
			2.349566,
			48.82971
		],
		"name": "Autoroute du Soleil",
		"hint": "7HIBgP___38AAAAAJAAAACYCAABsAQAAAAAAACQAAAAmAgAAbAEAAEAYAADRGCUACMXlAsUYJQAExeUCCwC_CYHseTw=",
		"matchings_index": 0,
		"waypoint_index": 1,
		"alternatives_count": 1
	}
	*/
	auto result = gcnew MatchWaypoint(jsonObject);
	result->MatchingsIndex = System::Convert::ToInt32(jsonObject.values.at("matchings_index").get<Number>().value);
	result->WaypointIndex = System::Convert::ToInt32(jsonObject.values.at("waypoint_index").get<Number>().value);
	result->AlternativesCount = System::Convert::ToInt32(jsonObject.values.at("alternatives_count").get<Number>().value);
	return result;
}