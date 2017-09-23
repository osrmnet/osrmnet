// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"
#include "..\Utils.h"

#include "MatchResult.h"
#include "MatchParameters.h"

#include "osrm\json_container.hpp"

using namespace Osrmnet::MatchService;
using namespace osrm::util::json;

MatchResult^ MatchResult::FromJsonObject(const osrm::util::json::Object& jsonObject, MatchParameters^ matchParameters)
{
	/*
	{
		"tracepoints": [ MatchWaypoint,... ],
		"matchings": [ Route,... ],
		"code": "Ok"
	}
	*/

	auto result = gcnew MatchResult();

	const auto &tracepoints = jsonObject.values.at("tracepoints").get<Array>().values;
	for (const auto &tracepoint : tracepoints)
	{
		const auto &tracepointObject = tracepoint.get<osrm::util::json::Object>();
		result->Tracepoints->Add(MatchWaypoint::FromJsonObject(tracepointObject));
	}

	const auto &matchings = jsonObject.values.at("matchings").get<Array>().values;
	for (const auto &matching : matchings)
	{
		const auto &matchingObject = matching.get<osrm::util::json::Object>();
		result->Matchings->Add(Route::FromJsonObject(matchingObject, matchParameters->Steps, matchParameters->Annotations, matchParameters->Geometries, matchParameters->Overview));
	}

	auto code = jsonObject.values.at("code").get<String>().value;
	result->Code = Osrmnet::Utils::ConvertFromUtf8(code);

	return result;
}