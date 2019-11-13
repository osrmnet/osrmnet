// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Coordinate.h"
#include "..\Utils.h"

#include "NearestWaypoint.h"

#include "osrm/json_container.hpp"

using namespace System::Collections::Generic;

using namespace Osrmnet::NearestService;
using namespace osrm::util::json;

NearestWaypoint::NearestWaypoint(const osrm::util::json::Object& jsonObject) : Waypoint(jsonObject)
{
	Nodes = gcnew List<UINT64>(2);
}

NearestWaypoint^ NearestWaypoint::FromJsonObject(const osrm::util::json::Object& jsonObject)
{
	/*
	{
	    "nodes": [
			1912916988,
			2286779175
		],
		"location": [
			2.349566,
			48.82971
		],
		"name": "Autoroute du Soleil",
		"hint": "7HIBgP___38AAAAAJAAAACYCAABsAQAAAAAAACQAAAAmAgAAbAEAAEAYAADRGCUACMXlAsUYJQAExeUCCwC_CYHseTw=",
		"distance": 4.152629
	}
	*/
	auto result = gcnew NearestWaypoint(jsonObject);

	const auto& nodes = jsonObject.values.at("nodes").get<Array>().values;
	for (const auto& node : nodes) {
		result->Nodes->Add((UINT64)node.get<Number>().value);
	}

	result->Distance = jsonObject.values.at("distance").get<Number>().value;
	return result;
}