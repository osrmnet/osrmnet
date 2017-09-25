// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "TileParameters.h"

#include "engine\api\tile_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::TileService;

TileParameters::TileParameters() : tileParameters(new osrm::engine::api::TileParameters())
{
}

osrm::engine::api::TileParameters* const TileParameters::InnerTileParameters()
{
	return tileParameters;
}

unsigned TileParameters::X::get()
{
	return tileParameters->x;
}
void TileParameters::X::set(unsigned value)
{
	tileParameters->x = value;
}
unsigned TileParameters::Y::get()
{
	return tileParameters->y;
}
void TileParameters::Y::set(unsigned value)
{
	tileParameters->y = value;
}
unsigned TileParameters::Z::get()
{
	return tileParameters->z;
}
void TileParameters::Z::set(unsigned value)
{
	tileParameters->z = value;
}

bool TileParameters::IsValid()
{
	return tileParameters->IsValid();
}