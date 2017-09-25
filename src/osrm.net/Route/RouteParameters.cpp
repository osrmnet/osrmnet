// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "RouteParameters.h"

#include "engine\api\route_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::RouteService;

RouteParameters::RouteParameters(osrm::engine::api::RouteParameters* parameters) : BaseParameters(parameters)
{
}
RouteParameters::RouteParameters() : BaseParameters(new osrm::engine::api::RouteParameters())
{
}

osrm::engine::api::RouteParameters* const RouteParameters::InnerRouteParameters()
{
	return (osrm::engine::api::RouteParameters*)baseParameters;
}

bool RouteParameters::Steps::get()
{
	return InnerRouteParameters()->steps;
}
void RouteParameters::Steps::set(bool value)
{
	InnerRouteParameters()->steps = value;
}
unsigned int RouteParameters::NumberOfAlternatives::get()
{
	return InnerRouteParameters()->number_of_alternatives;
}
void RouteParameters::NumberOfAlternatives::set(unsigned int value)
{
	InnerRouteParameters()->number_of_alternatives = value;
}
AnnotationsType RouteParameters::Annotations::get()
{
	return static_cast<AnnotationsType>(InnerRouteParameters()->annotations_type);
}
void RouteParameters::Annotations::set(AnnotationsType value)
{
	InnerRouteParameters()->annotations_type = static_cast<osrm::engine::api::RouteParameters::AnnotationsType>(value);
}
GeometriesType RouteParameters::Geometries::get()
{
	return static_cast<GeometriesType>(InnerRouteParameters()->geometries);
}
void RouteParameters::Geometries::set(GeometriesType value)
{
	InnerRouteParameters()->geometries = static_cast<osrm::engine::api::RouteParameters::GeometriesType>(value);
}
OverviewType RouteParameters::Overview::get()
{
	return static_cast<OverviewType>(InnerRouteParameters()->overview);
}
void RouteParameters::Overview::set(OverviewType value)
{
	InnerRouteParameters()->overview = static_cast<osrm::engine::api::RouteParameters::OverviewType>(value);
}
bool RouteParameters::ContinueStraight::get()
{
	return InnerRouteParameters()->continue_straight.get();
}
void RouteParameters::ContinueStraight::set(bool value)
{
	InnerRouteParameters()->continue_straight = value;
}