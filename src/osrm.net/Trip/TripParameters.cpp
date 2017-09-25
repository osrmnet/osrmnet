// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "TripParameters.h"

#include "engine\api\trip_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::TripService;

TripParameters::TripParameters() : RouteParameters(new osrm::engine::api::TripParameters())
{
}

osrm::engine::api::TripParameters* const TripParameters::InnerTripParameters()
{
	return (osrm::engine::api::TripParameters*)baseParameters;
}

bool TripParameters::Roundtrip::get()
{
	return InnerTripParameters()->roundtrip;
}
void TripParameters::Roundtrip::set(bool value)
{
	InnerTripParameters()->roundtrip = value;
}
SourceType TripParameters::Source::get()
{
	return static_cast<SourceType>(InnerTripParameters()->source);
}
void TripParameters::Source::set(SourceType value)
{
	InnerTripParameters()->source = static_cast<osrm::engine::api::TripParameters::SourceType>(value);
}
DestinationType TripParameters::Destination::get()
{
	return static_cast<DestinationType>(InnerTripParameters()->destination);
}
void TripParameters::Destination::set(DestinationType value)
{
	InnerTripParameters()->destination = static_cast<osrm::engine::api::TripParameters::DestinationType>(value);
}