// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "OsrmFwdDecl.h"
#include "Approach.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;
	ref class Bearing;

	public ref class BaseParameters
	{
	public:
		property IList<Coordinate^>^ Coordinates { void set(IList<Coordinate^>^); }
		property IList<System::String^>^ Hints { void set(IList<System::String^>^); }
		property IList<System::Nullable<double>>^ Radiuses { void set(IList<System::Nullable<double>>^); }
		property IList<Bearing^>^ Bearings { void set(IList<Bearing^>^); }
		property IList<System::Nullable<Approach>>^ Approaches { void set(IList<System::Nullable<Approach>>^); }
		property bool GenerateHints { void set(bool); }
		property IList<System::String^>^ Exclude { void set(IList<System::String^>^); }

		bool IsValid();

		BaseParameters(osrm::engine::api::BaseParameters* parameters);
		~BaseParameters();
		!BaseParameters();

	protected:
		osrm::engine::api::BaseParameters* const baseParameters;
	};
}
