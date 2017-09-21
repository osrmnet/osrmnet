#pragma once
// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\OsrmFwdDecl.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;

	namespace Route
	{
		ref class RouteItem;
		ref class RouteParameters;
		ref class RouteWayPoint;

		public ref class RouteResult
		{
		public:
			property IList<RouteItem^>^ Routes;
			property IList<RouteWayPoint^>^ WayPoints;
			property System::String^ Code;

			RouteResult()
			{
				Routes = gcnew List<RouteItem^>();
				WayPoints = gcnew List<RouteWayPoint^>();
			}

			static RouteResult^ FromJsonObject(const osrm::util::json::Object&, RouteParameters^);
		};
	}
}

