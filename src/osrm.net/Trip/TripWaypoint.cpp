// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Coordinate.h"
#include "..\Utils.h"

#include "TripWaypoint.h"

#include "osrm/json_container.hpp"

using namespace Osrmnet::TripService;
using namespace osrm::util::json;

TripWaypoint::TripWaypoint(const osrm::util::json::Object& jsonObject) : Waypoint(jsonObject)
{
}

TripWaypoint^ TripWaypoint::FromJsonObject(const osrm::util::json::Object& jsonObject)
{
	/*
	{
		"location": [
			2.349566,
			48.82971
		],
		"name": "Autoroute du Soleil",
		"hint": "7HIBgP___38AAAAAJAAAACYCAABsAQAAAAAAACQAAAAmAgAAbAEAAEAYAADRGCUACMXlAsUYJQAExeUCCwC_CYHseTw=",
		"trips_index": 0,
		"waypoint_index": 1
	}
	*/
	auto result = gcnew TripWaypoint(jsonObject);
	result->TripsIndex = System::Convert::ToInt32(jsonObject.values.at("trips_index").get<Number>().value);
	result->WaypointIndex = System::Convert::ToInt32(jsonObject.values.at("waypoint_index").get<Number>().value);
	return result;
}