// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "stdafx.h"
#include "EngineConfig.h"
#include "engine\engine_config.hpp"

osrmnet::EngineConfig::EngineConfig() : engineConfig(new osrm::engine::EngineConfig())
{
}

osrmnet::EngineConfig::~EngineConfig()
{
	this->!EngineConfig();
	System::GC::SuppressFinalize(this);
}
osrmnet::EngineConfig::!EngineConfig()
{
	delete engineConfig;
}

System::String^ osrmnet::EngineConfig::StorageConfig::get()
{
	return { gcnew System::String(engineConfig->storage_config.datasource_names_path.c_str()) };
}

void osrmnet::EngineConfig::StorageConfig::set(System::String^ value)
{
	engineConfig->storage_config = { msclr::interop::marshal_as<std::string>(value) };
}

bool osrmnet::EngineConfig::UseSharedMemory::get()
{
	return engineConfig->use_shared_memory;
}
void osrmnet::EngineConfig::UseSharedMemory::set(bool value)
{
	engineConfig->use_shared_memory = value;
}

bool osrmnet::EngineConfig::IsValid()
{
	return engineConfig->IsValid();
}
