// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "stdafx.h"
#include "EngineConfig.h"
#include "engine\engine_config.hpp"

using namespace Osrmnet;

EngineConfig::EngineConfig() : engineConfig(new osrm::engine::EngineConfig())
{
	// Default shared memory is off
	this->UseSharedMemory = false;
	this->Algorithm = Osrmnet::Algorithm::MLD;
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

Osrmnet::Algorithm EngineConfig::Algorithm::get()
{
	return static_cast<Osrmnet::Algorithm>(engineConfig->algorithm);
}
void EngineConfig::Algorithm::set(Osrmnet::Algorithm algorithm)
{
	engineConfig->algorithm = static_cast<osrm::engine::EngineConfig::Algorithm>(algorithm);
}

bool EngineConfig::IsValid()
{
	return engineConfig->IsValid();
}
