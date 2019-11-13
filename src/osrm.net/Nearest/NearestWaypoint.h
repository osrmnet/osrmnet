// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"
#include "..\Waypoint.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;

	namespace NearestService
	{
		public ref class NearestWaypoint : public Waypoint
		{
		public:
			property IList<UINT64>^ Nodes;
			property double Distance;

		internal:
			NearestWaypoint(const osrm::util::json::Object&);
			static NearestWaypoint^ FromJsonObject(const osrm::util::json::Object&);
		};
	}
}