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
unsigned int RouteParameters::NumberOfAlternatives::get()
{
	return routeParameters->number_of_alternatives;
}
void RouteParameters::NumberOfAlternatives::set(unsigned int value)
{
	routeParameters->number_of_alternatives = value;
}
AnnotationsType RouteParameters::Annotations::get()
{
	return static_cast<AnnotationsType>(routeParameters->annotations_type);
}
void RouteParameters::Annotations::set(AnnotationsType value)
{
	routeParameters->annotations_type = static_cast<osrm::engine::api::RouteParameters::AnnotationsType>(value);
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
		routeParameters->coordinates.push_back({ osrm::util::FloatLongitude{ coordinate->Long }, osrm::util::FloatLatitude{ coordinate->Lat } });
	}
}
void RouteParameters::GenerateHints::set(bool value)
{
	routeParameters->generate_hints = value;
}

bool RouteParameters::IsValid()
{
	return routeParameters->IsValid();
}