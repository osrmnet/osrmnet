#pragma once
// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\OsrmFwdDecl.h"
#include "..\Route.h"
#include "..\Waypoint.h"

using namespace System::Collections::Generic;

namespace Osrmnet
{
	ref class Coordinate;

	namespace RouteService
	{
		ref class RouteParameters;

		public ref class RouteResult
		{
		public:
			property IList<Route^>^ Routes;
			property IList<Waypoint^>^ Waypoints;
			property System::String^ Code;

			RouteResult()
			{
				Routes = gcnew List<Route^>();
				Waypoints = gcnew List<Waypoint^>();
			}

			static RouteResult^ FromJsonObject(const osrm::util::json::Object&, RouteParameters^);
		};
	}
}

