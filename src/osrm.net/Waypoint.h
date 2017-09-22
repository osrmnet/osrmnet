// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "OsrmFwdDecl.h"

namespace Osrmnet {
	ref class Coordinate;

	public ref class Waypoint
	{
	public:
		property System::String^ Hint;
		property System::String^ Name;
		property Coordinate^ Location;

	internal:
		static Waypoint^ FromJsonObject(const osrm::util::json::Object& jsonObject);
	};
}