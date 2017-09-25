// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Utils.h"

#include "RouteResult.h"
#include "RouteParameters.h"

#include "osrm\json_container.hpp"

using namespace Osrmnet::RouteService;
using namespace osrm::util::json;

RouteResult^ RouteResult::FromJsonObject(const osrm::util::json::Object& jsonObject, RouteParameters^ routeParameters)
{
	/*
	{
		"waypoints": [ { ... } ],
		"routes": [ { ... } ],
		"code": "Ok"
	}
	*/

	auto result = gcnew RouteResult();

	// Process waypoint
	auto code = jsonObject.values.at("code").get<String>().value;
	result->Code = Osrmnet::Utils::ConvertFromUtf8(code);
	

	// Process Routes
	const auto &routes = jsonObject.values.at("routes").get<Array>().values;
	for (const auto &route : routes)
	{
		const auto &routeObject = route.get<osrm::util::json::Object>();
		result->Routes->Add(Route::FromJsonObject(routeObject, routeParameters->Steps, routeParameters->Annotations, routeParameters->Geometries, routeParameters->Overview));
	}

	// Process waypoint
	const auto &waypoints = jsonObject.values.at("waypoints").get<Array>().values;
	for (const auto &waypoint : waypoints)
	{
		const auto &waypointObject = waypoint.get<osrm::util::json::Object>();
		result->Waypoints->Add(Waypoint::FromJsonObject(waypointObject));
	}

	return result;
}