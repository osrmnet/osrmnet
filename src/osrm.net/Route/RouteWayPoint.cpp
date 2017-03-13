// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\Stdafx.h"

#include "RouteWayPoint.h"
#include "RouteParameters.h"

#include "osrm/json_container.hpp"
#include "engine/polyline_compressor.hpp"
#include <msclr\marshal_cppstd.h>

using namespace Osrmnet::Route;
using namespace osrm::util::json;

RouteWayPoint^ RouteWayPoint::FromJsonObject(const osrm::util::json::Object& jsonObject, RouteParameters^ routeParams)
{
	auto result = gcnew RouteWayPoint();
	jsonObject;
	routeParams;
	


	return result;
}