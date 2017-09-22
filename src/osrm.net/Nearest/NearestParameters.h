// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include "..\BaseParameters.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	namespace NearestService {
		public ref class NearestParameters : public BaseParameters
		{
		public:
			property unsigned int NumberOfResults { unsigned int get(); void set(unsigned int); }

			NearestParameters();

		internal:
			osrm::engine::api::NearestParameters* const InnerObject();
		};
	}
}
