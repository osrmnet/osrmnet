// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"
#include "..\Waypoint.h"

namespace Osrmnet
{
	ref class Coordinate;

	namespace MatchService
	{
		public ref class MatchWaypoint : public Waypoint
		{
		public:
			property int MatchingsIndex;
			property int WaypointIndex;
			property int AlternativesCount;

		internal:
			MatchWaypoint(const osrm::util::json::Object&);
			static MatchWaypoint^ FromJsonObject(const osrm::util::json::Object&);
		};
	}
}