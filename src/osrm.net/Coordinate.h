// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

namespace Osrmnet
{
	public ref class Coordinate
	{
	public:
		Coordinate(double latitude, double longitude)
		{
			Lat = latitude;
			Long = longitude;
		}
		property double Lat;
		property double Long;
	};
}