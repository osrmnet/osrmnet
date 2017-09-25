// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"
#include "..\Route.h"

namespace Osrmnet
{
	ref class Coordinate;

	namespace MatchService
	{
		public ref class MatchRoute : public Route
		{
		public:
			property double Confidence;

		internal:
			MatchRoute(const osrm::util::json::Object&, bool, AnnotationsType, GeometriesType, OverviewType);
			static MatchRoute^ FromJsonObject(const osrm::util::json::Object&, bool, AnnotationsType, GeometriesType, OverviewType);
		};
	}
}