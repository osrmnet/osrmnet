// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "MatchParameters.h"

#include "engine\api\match_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::MatchService;

MatchParameters::MatchParameters() : RouteParameters(new osrm::engine::api::MatchParameters())
{
}

osrm::engine::api::MatchParameters* const MatchParameters::InnerMatchParameters()
{
	return (osrm::engine::api::MatchParameters*)baseParameters;
}

void MatchParameters::Timestamps::set(System::Collections::Generic::IList<unsigned>^ value)
{
	// Copy array value
	InnerMatchParameters()->timestamps.clear();
	for each (unsigned timestamp in value)
	{
		InnerMatchParameters()->timestamps.push_back(timestamp);
	}
}
GapsType MatchParameters::Gaps::get()
{
	return static_cast<GapsType>(InnerMatchParameters()->gaps);
}
void MatchParameters::Gaps::set(GapsType value)
{
	InnerMatchParameters()->gaps = static_cast<osrm::engine::api::MatchParameters::GapsType>(value);
}
bool MatchParameters::Tidy::get()
{
	return InnerMatchParameters()->tidy;
}
void MatchParameters::Tidy::set(bool value)
{
	InnerMatchParameters()->tidy = value;
}