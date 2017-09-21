// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "stdafx.h"
#include "EngineConfig.h"
#include "engine\engine_config.hpp"

using namespace Osrmnet;

EngineConfig::EngineConfig() : engineConfig(new osrm::engine::EngineConfig())
{
}

EngineConfig::~EngineConfig()
{
	this->!EngineConfig();
	System::GC::SuppressFinalize(this);
}
EngineConfig::!EngineConfig()
{
	delete engineConfig;
}

System::String^ EngineConfig::StorageConfig::get()
{
	return { gcnew System::String(engineConfig->storage_config.base_path.c_str()) };
}

void EngineConfig::StorageConfig::set(System::String^ value)
{
	engineConfig->storage_config = { msclr::interop::marshal_as<std::string>(value) };
}

bool EngineConfig::UseSharedMemory::get()
{
	return engineConfig->use_shared_memory;
}
void EngineConfig::UseSharedMemory::set(bool value)
{
	engineConfig->use_shared_memory = value;
}

bool EngineConfig::IsValid()
{
	return engineConfig->IsValid();
}
