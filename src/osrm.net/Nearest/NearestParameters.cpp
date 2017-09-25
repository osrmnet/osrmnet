// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "NearestParameters.h"

#include "engine\api\nearest_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::NearestService;

NearestParameters::NearestParameters() : BaseParameters(new osrm::engine::api::NearestParameters())
{
}

osrm::engine::api::NearestParameters* const NearestParameters::InnerNearestParameters()
{
	return (osrm::engine::api::NearestParameters*)baseParameters;
}

unsigned int NearestParameters::NumberOfResults::get()
{
	return InnerNearestParameters()->number_of_results;
}
void NearestParameters::NumberOfResults::set(unsigned int value)
{
	InnerNearestParameters()->number_of_results = value;
}
