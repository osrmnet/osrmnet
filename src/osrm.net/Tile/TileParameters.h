// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"

using namespace System::Collections::Generic;

namespace Osrmnet
{
	namespace TileService
	{
		public ref class TileParameters
		{
		public:
			property unsigned X { unsigned get(); void set(unsigned); }
			property unsigned Y { unsigned get(); void set(unsigned); }
			property unsigned Z { unsigned get(); void set(unsigned); }

			bool IsValid();

			TileParameters();

		internal:
			osrm::engine::api::TileParameters* const InnerTileParameters();
			osrm::engine::api::TileParameters* const tileParameters;
		};
	}
}
