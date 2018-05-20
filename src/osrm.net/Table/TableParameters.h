// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include "..\BaseParameters.h"

using namespace System::Collections::Generic;

namespace Osrmnet
{
	namespace TableService
	{
		public enum class AnnotationsType
		{
			None = 0,
			Duration = 0x01,
			Distance = 0x02,
			All = Duration | Distance
		};

		public ref class TableParameters : public BaseParameters
		{
		public:
			property IList<size_t>^ Sources { void set(IList<size_t>^); }
			property IList<size_t>^ Destinations { void set(IList<size_t>^); }
			property AnnotationsType Annotations { void set(AnnotationsType); }

			TableParameters();

		internal:
			osrm::engine::api::TableParameters* const InnerObject();
		};
	}
}
