// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "OsrmFwdDecl.h"
#include <msclr\marshal_cppstd.h>

namespace osrmnet
{
	public ref class EngineConfig
	{
	public:
		bool IsValid();
		property System::String^ StorageConfig { System::String^ get();  void set(System::String^); }
		property bool UseSharedMemory { bool get(); void set(bool); }

		EngineConfig();
		~EngineConfig();
		!EngineConfig();		

	private:
		osrm::engine::EngineConfig* const engineConfig;
	internal:
		osrm::engine::EngineConfig* const InnerObject()
		{
			return engineConfig;
		}
	};
}
