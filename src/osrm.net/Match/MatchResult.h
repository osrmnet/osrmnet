#pragma once
// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\OsrmFwdDecl.h"
#include "..\Route.h"
#include "MatchWaypoint.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;

	namespace MatchService
	{
		ref class MatchParameters;

		public ref class MatchResult
		{
		public:
			property IList<MatchWaypoint^>^ Tracepoints;
			property IList<Route^>^ Matchings;
			property System::String^ Code;

			MatchResult()
			{
				Tracepoints = gcnew List<MatchWaypoint^>();
				Matchings = gcnew List<Route^>();
			}

			static MatchResult^ FromJsonObject(const osrm::util::json::Object&, MatchParameters^);
		};
	}
}

