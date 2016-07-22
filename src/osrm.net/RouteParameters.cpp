// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "stdafx.h"
#include "RouteParameters.h"
#include "Coordinate.h"

#include "engine\api\route_parameters.hpp"
#include "osrm/coordinate.hpp"

osrmnet::RouteParameters::RouteParameters() : routeParameters(new osrm::engine::api::RouteParameters())
{
}

osrmnet::RouteParameters::~RouteParameters()
{
	this->!RouteParameters();
	System::GC::SuppressFinalize(this);
}
osrmnet::RouteParameters::!RouteParameters()
{
	delete routeParameters;
}

osrm::engine::api::RouteParameters* const osrmnet::RouteParameters::InnerObject()
{
	return routeParameters;
}

bool osrmnet::RouteParameters::Steps::get()
{
	return routeParameters->steps;
}
void osrmnet::RouteParameters::Steps::set(bool value)
{
	routeParameters->steps = value;
}
bool osrmnet::RouteParameters::Alternatives::get()
{
	return routeParameters->alternatives;
}
void osrmnet::RouteParameters::Alternatives::set(bool value)
{
	routeParameters->alternatives = value;
}
bool osrmnet::RouteParameters::Annotations::get()
{
	return routeParameters->annotations;
}
void osrmnet::RouteParameters::Annotations::set(bool value)
{
	routeParameters->annotations = value;
}
osrmnet::GeometriesType osrmnet::RouteParameters::Geometries::get()
{
	return static_cast<osrmnet::GeometriesType>(routeParameters->geometries);
}
void osrmnet::RouteParameters::Geometries::set(GeometriesType value)
{
	routeParameters->geometries = static_cast<osrm::engine::api::RouteParameters::GeometriesType>(value);
}
osrmnet::OverviewType osrmnet::RouteParameters::Overview::get()
{
	return static_cast<osrmnet::OverviewType>(routeParameters->overview);
}
void osrmnet::RouteParameters::Overview::set(osrmnet::OverviewType value)
{
	routeParameters->overview = static_cast<osrm::engine::api::RouteParameters::OverviewType>(value);
}
bool osrmnet::RouteParameters::ContinueStraight::get()
{
	return routeParameters->continue_straight.get();
}
void osrmnet::RouteParameters::ContinueStraight::set(bool value)
{
	routeParameters->continue_straight = value;
}
void osrmnet::RouteParameters::Coordinates::set(System::Collections::Generic::IList<osrmnet::Coordinate^>^ value)
{
	// Copy array value
	routeParameters->coordinates.clear();
	for each (osrmnet::Coordinate^ coordinate in value)
	{
		routeParameters->coordinates.push_back({osrm::util::FloatLongitude{coordinate->Long}, osrm::util::FloatLatitude{coordinate->Lat}});
	}
}

bool osrmnet::RouteParameters::IsValid()
{
	return routeParameters->IsValid();
}

