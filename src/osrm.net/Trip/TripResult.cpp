// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Utils.h"

#include "TripResult.h"
#include "TripParameters.h"

#include "osrm\json_container.hpp"

using namespace Osrmnet::TripService;
using namespace osrm::util::json;

TripResult^ TripResult::FromJsonObject(const osrm::util::json::Object& jsonObject, TripParameters^ tripParameters)
{
	/*
	{
		"waypoints": [ TripWaypoint,... ],
		"trips": [ Route,... ],
		"code": "Ok"
	}
	*/

	auto result = gcnew TripResult();

	const auto &waypoints = jsonObject.values.at("waypoints").get<Array>().values;
	for (const auto &waypoint : waypoints)
	{
		const auto &waypointObject = waypoint.get<osrm::util::json::Object>();
		result->Waypoints->Add(TripWaypoint::FromJsonObject(waypointObject));
	}

	const auto &trips = jsonObject.values.at("trips").get<Array>().values;
	for (const auto &trip : trips)
	{
		const auto &tripObject = trip.get<osrm::util::json::Object>();
		result->Trips->Add(Route::FromJsonObject(tripObject, tripParameters->Steps, tripParameters->Annotations, tripParameters->Geometries, tripParameters->Overview));
	}

	auto code = jsonObject.values.at("code").get<String>().value;
	result->Code = Osrmnet::Utils::ConvertFromUtf8(code);

	return result;
}