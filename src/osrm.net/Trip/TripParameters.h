// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include "..\Route\RouteParameters.h"
#include "..\Route.h"

using namespace System::Collections::Generic;

namespace Osrmnet
{
	namespace TripService
	{
		public enum class SourceType
		{
			Any,
			First
		};

		public enum class DestinationType
		{
			Any,
			Last
		};

		public ref class TripParameters : public Osrmnet::RouteService::RouteParameters
		{
		public:
			property bool Roundtrip { bool get(); void set(bool); }
			property SourceType Source { SourceType get(); void set(SourceType); }
			property DestinationType Destination { DestinationType get(); void set(DestinationType); }
			
			TripParameters();

		internal:
			osrm::engine::api::TripParameters* const InnerTripParameters();
		};
	}
}
