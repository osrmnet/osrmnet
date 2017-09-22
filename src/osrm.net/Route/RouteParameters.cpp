// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "RouteParameters.h"

#include "engine\api\route_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::RouteService;

RouteParameters::RouteParameters() : BaseParameters(new osrm::engine::api::RouteParameters())
{
}

osrm::engine::api::RouteParameters* const RouteParameters::InnerObject()
{
	return (osrm::engine::api::RouteParameters*)baseParameters;
}

bool RouteParameters::Steps::get()
{
	return InnerObject()->steps;
}
void RouteParameters::Steps::set(bool value)
{
	InnerObject()->steps = value;
}
unsigned int RouteParameters::NumberOfAlternatives::get()
{
	return InnerObject()->number_of_alternatives;
}
void RouteParameters::NumberOfAlternatives::set(unsigned int value)
{
	InnerObject()->number_of_alternatives = value;
}
AnnotationsType RouteParameters::Annotations::get()
{
	return static_cast<AnnotationsType>(InnerObject()->annotations_type);
}
void RouteParameters::Annotations::set(AnnotationsType value)
{
	InnerObject()->annotations_type = static_cast<osrm::engine::api::RouteParameters::AnnotationsType>(value);
}
GeometriesType RouteParameters::Geometries::get()
{
	return static_cast<GeometriesType>(InnerObject()->geometries);
}
void RouteParameters::Geometries::set(GeometriesType value)
{
	InnerObject()->geometries = static_cast<osrm::engine::api::RouteParameters::GeometriesType>(value);
}
OverviewType RouteParameters::Overview::get()
{
	return static_cast<OverviewType>(InnerObject()->overview);
}
void RouteParameters::Overview::set(OverviewType value)
{
	InnerObject()->overview = static_cast<osrm::engine::api::RouteParameters::OverviewType>(value);
}
bool RouteParameters::ContinueStraight::get()
{
	return InnerObject()->continue_straight.get();
}
void RouteParameters::ContinueStraight::set(bool value)
{
	InnerObject()->continue_straight = value;
}