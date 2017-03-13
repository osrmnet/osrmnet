// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;
}

namespace Osrmnet {
	namespace Route {
		public enum class GeometriesType
		{
			Polyline,
			GeoJSON
		};
		public enum class OverviewType
		{
			Simplified,
			Full,
			False
		};

		public ref class RouteParameters
		{
		public:
			property bool Steps { bool get(); void set(bool); }
			property bool Alternatives { bool get(); void set(bool); }
			property bool Annotations { bool get(); void set(bool); }
			property GeometriesType Geometries { GeometriesType get(); void set(GeometriesType); }
			property OverviewType Overview { OverviewType get(); void set(OverviewType); }
			property bool ContinueStraight { bool get(); void set(bool); }
			property IList<Coordinate^>^ Coordinates { void set(IList<Coordinate^>^); }

			bool IsValid();

			RouteParameters();
			~RouteParameters();
			!RouteParameters();

		internal:
			osrm::engine::api::RouteParameters* const InnerObject();

		private:
			osrm::engine::api::RouteParameters* const routeParameters;
		};
	}
}
