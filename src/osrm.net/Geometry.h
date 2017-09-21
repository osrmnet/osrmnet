// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

using namespace System::Collections::Generic;

namespace Osrmnet
{
	ref class Coordinate;

	public ref class Geometry
	{
	public:
		property System::String^ Encoded;
		property System::String^ Type;
		property IList<Coordinate^>^ Coordinates;

		Geometry()
		{
			Coordinates = gcnew List<Coordinate^>();
		}
	};
}