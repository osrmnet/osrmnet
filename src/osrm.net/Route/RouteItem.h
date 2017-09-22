// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;
	ref class Geometry;

	namespace Route
	{
		enum class GeometriesType;
		ref class RouteLeg;
		ref class RouteWayPoint;
		ref class RouteParameters;

		public ref class RouteItem
		{
		public:
			property double Distance;
			property double Duration;
			property double Weight;
			property System::String^ WeightName;
			property Geometry^ Geometry;
			property IList<RouteLeg^>^ Legs;

			RouteItem()
			{
				Legs = gcnew List<RouteLeg^>();
			}

			static RouteItem^ FromJsonObject(const osrm::util::json::Object&, RouteParameters^);
		};
	}
}
