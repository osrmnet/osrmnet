// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include "..\BaseParameters.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	namespace TableService {
		public ref class TableParameters : public BaseParameters
		{
		public:
			property IList<size_t>^ Sources { void set(IList<size_t>^); }
			property IList<size_t>^ Destinations { void set(IList<size_t>^); }

			TableParameters();

		internal:
			osrm::engine::api::TableParameters* const InnerObject();
		};
	}
}
