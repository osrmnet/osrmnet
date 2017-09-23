#pragma once
// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\OsrmFwdDecl.h"
#include "..\Route.h"
#include "TripWaypoint.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;

	namespace TripService
	{
		ref class TripParameters;

		public ref class TripResult
		{
		public:
			property IList<TripWaypoint^>^ Waypoints;
			property IList<Route^>^ Trips;
			property System::String^ Code;

			TripResult()
			{
				Waypoints = gcnew List<TripWaypoint^>();
				Trips = gcnew List<Route^>();
			}

			static TripResult^ FromJsonObject(const osrm::util::json::Object&, TripParameters^);
		};
	}
}

