// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include <msclr\marshal_cppstd.h>
#include "..\Approach.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;
	ref class Bearing;
}

namespace Osrmnet {
	namespace Route {
		public enum class GeometriesType
		{
			Polyline,
			Polyline6,
			GeoJSON
		};
		public enum class OverviewType
		{
			Simplified,
			Full,
			False
		};
		public enum class AnnotationsType
		{
			None = 0,
			Duration = 0x01,
			Nodes = 0x02,
			Distance = 0x04,
			Weight = 0x08,
			Datasources = 0x10,
			Speed = 0x20,
			All = Duration | Nodes | Distance | Weight | Datasources | Speed
		};

		public ref class RouteParameters
		{
		public:
			property bool Steps { bool get(); void set(bool); }
			property unsigned int NumberOfAlternatives { unsigned int get(); void set(unsigned int); }
			property AnnotationsType Annotations { AnnotationsType get(); void set(AnnotationsType); }
			property GeometriesType Geometries { GeometriesType get(); void set(GeometriesType); }
			property OverviewType Overview { OverviewType get(); void set(OverviewType); }
			property bool ContinueStraight { bool get(); void set(bool); }
			property IList<Coordinate^>^ Coordinates { void set(IList<Coordinate^>^); }
			property IList<System::String^>^ Hints { void set(IList<System::String^>^); }
			property IList<System::Nullable<double>>^ Radiuses { void set(IList<System::Nullable<double>>^); }
			property IList<Bearing^>^ Bearings { void set(IList<Bearing^>^); }
			property IList<System::Nullable<Approach>>^ Approaches { void set(IList<System::Nullable<Approach>>^); }
			property bool GenerateHints { void set(bool); }
			property  IList<System::String^>^ Exclude { void set(IList<System::String^>^); }
			
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
