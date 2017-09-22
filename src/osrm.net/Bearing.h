// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

namespace Osrmnet
{
	public ref class Bearing
	{
	public:
		Bearing(short value, short range)
		{
			Value = value;
			Range = range;
		}
		property short Value;
		property short Range;
	};
}
