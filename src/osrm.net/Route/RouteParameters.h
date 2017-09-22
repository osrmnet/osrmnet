// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include "..\BaseParameters.h"
#include "..\Route.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;

	namespace RouteService {
		public ref class RouteParameters : public BaseParameters
		{
		public:
			property unsigned int NumberOfAlternatives { unsigned int get(); void set(unsigned int); }
			property bool Steps { bool get(); void set(bool); }
			property AnnotationsType Annotations { AnnotationsType get(); void set(AnnotationsType); }
			property GeometriesType Geometries { GeometriesType get(); void set(GeometriesType); }
			property OverviewType Overview { OverviewType get(); void set(OverviewType); }
			property bool ContinueStraight { bool get(); void set(bool); }
			
			RouteParameters();

		internal:
			osrm::engine::api::RouteParameters* const InnerObject();
		};
	}
}
