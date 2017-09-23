// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "Stdafx.h"
#include "Coordinate.h"
#include "Utils.h"

#include "Waypoint.h"

#include "osrm/json_container.hpp"

using namespace Osrmnet;
using namespace osrm::util::json;

Waypoint::Waypoint(const osrm::util::json::Object& jsonObject)
{
	/*
	{
		"location": [
			2.349566,
			48.82971
		],
		"name": "Boulevard Auguste Blanqui",
		"hint": "AQ4AgP___38AAAAACgAAAPIAAAAAAAAAAAAAAAoAAADyAAAAAAAAAEAYAAD-2SMADhXpAv7ZIwAVFekCBgDvEIHseTw="
	}
	*/

	this->Name = Osrmnet::Utils::ConvertFromUtf8(jsonObject.values.at("name").get<String>().value);
	const auto &location = jsonObject.values.at("location").get<Array>().values;
	this->Location = gcnew Osrmnet::Coordinate(location[1].get<Number>().value, location[0].get<Number>().value);
	if (jsonObject.values.count("hint") > 0) // hint depends on GenerateHints paramters
	{
		this->Hint = Osrmnet::Utils::ConvertFromUtf8(jsonObject.values.at("hint").get<String>().value);
	}
}

Waypoint^ Waypoint::FromJsonObject(const osrm::util::json::Object& jsonObject)
{
	return gcnew Waypoint(jsonObject);
}