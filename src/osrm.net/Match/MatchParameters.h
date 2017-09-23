// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "..\OsrmFwdDecl.h"
#include "..\Route\RouteParameters.h"
#include "..\Route.h"

using namespace System::Collections::Generic;

namespace Osrmnet
{
	namespace MatchService
	{
		public enum class GapsType
		{
			Split,
			Ignore
		};

		public ref class MatchParameters : public Osrmnet::RouteService::RouteParameters
		{
		public:
			property IList<unsigned>^ Timestamps { void set(IList<unsigned>^); }
			property GapsType Gaps { GapsType get(); void set(GapsType); }
			property bool Tidy { bool get(); void set(bool); }
			
			MatchParameters();

		internal:
			osrm::engine::api::MatchParameters* const InnerMatchParameters();
		};
	}
}
