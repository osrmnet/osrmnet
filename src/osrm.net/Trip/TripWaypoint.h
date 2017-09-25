// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"
#include "..\Waypoint.h"

namespace Osrmnet
{
	ref class Coordinate;

	namespace TripService
	{
		public ref class TripWaypoint : public Waypoint
		{
		public:
			property int TripsIndex;
			property int WaypointIndex;

		internal:
			TripWaypoint(const osrm::util::json::Object&);
			static TripWaypoint^ FromJsonObject(const osrm::util::json::Object&);
		};
	}
}