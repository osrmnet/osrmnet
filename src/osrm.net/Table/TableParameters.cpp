// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "..\stdafx.h"

#include "TableParameters.h"

#include "engine\api\table_parameters.hpp"

using namespace Osrmnet;
using namespace Osrmnet::TableService;

TableParameters::TableParameters() : BaseParameters(new osrm::engine::api::TableParameters())
{
}

osrm::engine::api::TableParameters* const TableParameters::InnerObject()
{
	return (osrm::engine::api::TableParameters*)baseParameters;
}

void TableParameters::Sources::set(System::Collections::Generic::IList<size_t>^ value)
{
	// Copy array value
	InnerObject()->sources.clear();
	for each (size_t index in value)
	{
		InnerObject()->sources.push_back(index);
	}
}
void TableParameters::Destinations::set(System::Collections::Generic::IList<size_t>^ value)
{
	// Copy array value
	InnerObject()->destinations.clear();
	for each (size_t index in value)
	{
		InnerObject()->destinations.push_back(index);
	}
}