// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"
#include "..\Coordinate.h"

#include "RouteParameters.h"

#include "engine\api\route_parameters.hpp"
#include "osrm/coordinate.hpp"

using namespace Osrmnet;
using namespace Osrmnet::Route;

RouteParameters::RouteParameters() : routeParameters(new osrm::engine::api::RouteParameters())
{
}

RouteParameters::~RouteParameters()
{
	this->!RouteParameters();
	System::GC::SuppressFinalize(this);
}
RouteParameters::!RouteParameters()
{
	delete routeParameters;
}

osrm::engine::api::RouteParameters* const RouteParameters::InnerObject()
{
	return routeParameters;
}

bool RouteParameters::Steps::get()
{
	return routeParameters->steps;
}
void RouteParameters::Steps::set(bool value)
{
	routeParameters->steps = value;
}
bool RouteParameters::Alternatives::get()
{
	return routeParameters->alternatives;
}
void RouteParameters::Alternatives::set(bool value)
{
	routeParameters->alternatives = value;
}
bool RouteParameters::Annotations::get()
{
	return routeParameters->annotations;
}
void RouteParameters::Annotations::set(bool value)
{
	routeParameters->annotations = value;
}
GeometriesType RouteParameters::Geometries::get()
{
	return static_cast<GeometriesType>(routeParameters->geometries);
}
void RouteParameters::Geometries::set(GeometriesType value)
{
	routeParameters->geometries = static_cast<osrm::engine::api::RouteParameters::GeometriesType>(value);
}
OverviewType RouteParameters::Overview::get()
{
	return static_cast<OverviewType>(routeParameters->overview);
}
void RouteParameters::Overview::set(OverviewType value)
{
	routeParameters->overview = static_cast<osrm::engine::api::RouteParameters::OverviewType>(value);
}
bool RouteParameters::ContinueStraight::get()
{
	return routeParameters->continue_straight.get();
}
void RouteParameters::ContinueStraight::set(bool value)
{
	routeParameters->continue_straight = value;
}
void RouteParameters::Coordinates::set(System::Collections::Generic::IList<Coordinate^>^ value)
{
	// Copy array value
	routeParameters->coordinates.clear();
	for each (Coordinate^ coordinate in value)
	{
		routeParameters->coordinates.push_back({osrm::util::FloatLongitude{coordinate->Long}, osrm::util::FloatLatitude{coordinate->Lat}});
	}
}

bool RouteParameters::IsValid()
{
	return routeParameters->IsValid();
}