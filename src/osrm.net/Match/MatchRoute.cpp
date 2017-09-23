// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Coordinate.h"
#include "..\Utils.h"
#include "MatchRoute.h"

#include "osrm/json_container.hpp"

using namespace Osrmnet;
using namespace Osrmnet::MatchService;
using namespace osrm::util::json;

MatchRoute::MatchRoute(const osrm::json::Object &jsonRoute, bool generateSteps, AnnotationsType annotations, GeometriesType geometries, OverviewType overview) : Route(jsonRoute, generateSteps, annotations, geometries, overview)
{
}

MatchRoute^ MatchRoute::FromJsonObject(const osrm::json::Object &jsonRoute, bool generateSteps, AnnotationsType annotations, GeometriesType geometries, OverviewType overview)
{
	/*
	{
		"distance": 34918.3,
		"duration": 1854.1,
		"weight": 1854.1,
		"weight_name": "routability",
		"geometry": ...,
		"legs": [ RouteLeg,... ],
		"confidence": 0.977938
	}
	*/
	auto result = gcnew MatchRoute(jsonRoute, generateSteps, annotations, geometries, overview);
	result->Confidence = jsonRoute.values.at("confidence").get<Number>().value;
	return result;
}