#pragma once
// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\OsrmFwdDecl.h"
#include "..\Waypoint.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;

	namespace TableService
	{
		public ref class TableResult
		{
		public:
			property IList<Waypoint^>^ Sources;
			property IList<Waypoint^>^ Destinations;
			property System::String^ Code;
			property IList<IList<double>^>^ Durations;

			TableResult()
			{
				Sources = gcnew List<Waypoint^>();
				Destinations = gcnew List<Waypoint^>();
				Durations = gcnew List<IList<double>^>();
			}

			static TableResult^ FromJsonObject(const osrm::util::json::Object&);
		};
	}
}

