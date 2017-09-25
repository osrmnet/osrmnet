#pragma once
// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\OsrmFwdDecl.h"
#include "NearestWaypoint.h"

using namespace System::Collections::Generic;

namespace Osrmnet
{
	ref class Coordinate;

	namespace NearestService
	{
		public ref class NearestResult
		{
		public:
			property IList<NearestWaypoint^>^ WayPoints;
			property System::String^ Code;

			NearestResult()
			{
				WayPoints = gcnew List<NearestWaypoint^>();
			}

			static NearestResult^ FromJsonObject(const osrm::util::json::Object&);
		};
	}
}

