// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"

namespace Osrmnet {
	ref class Coordinate;

	namespace Route {

		ref class RouteParameters;

		public ref class RouteWayPoint
		{
		public:
			property System::String^ Hint;
			property double Distance;
			property System::String^ Name;
			property Coordinate^ Location;

		internal:
			RouteWayPoint^ FromJsonObject(const osrm::util::json::Object& jsonObject, RouteParameters^ routeParams);
		};
	}
}