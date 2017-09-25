// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "stdafx.h"
#include "Coordinate.h"
#include "Utils.h"
#include "Bearing.h"

#include "BaseParameters.h"

#include "engine\api\base_parameters.hpp"
#include "osrm\coordinate.hpp"

using namespace Osrmnet;

BaseParameters::BaseParameters(osrm::engine::api::BaseParameters* parameters) : baseParameters(parameters)
{
}
BaseParameters::~BaseParameters()
{
	this->!BaseParameters();
	System::GC::SuppressFinalize(this);
}
BaseParameters::!BaseParameters()
{
	delete baseParameters;
}

void BaseParameters::Coordinates::set(System::Collections::Generic::IList<Coordinate^>^ value)
{
	// Copy array value
	baseParameters->coordinates.clear();
	for each (Coordinate^ coordinate in value)
	{
		baseParameters->coordinates.push_back({ osrm::util::FloatLongitude{ coordinate->Long }, osrm::util::FloatLatitude{ coordinate->Lat } });
	}
}
void BaseParameters::Bearings::set(System::Collections::Generic::IList<Bearing^>^ value)
{
	// Copy array value
	baseParameters->radiuses.clear();
	for each (Bearing^ bearing in value)
	{
		if (bearing)
		{
			osrm::engine::Bearing osrmBearing;
			osrmBearing.bearing = bearing->Value;
			osrmBearing.range = bearing->Range;
			baseParameters->bearings.push_back(osrmBearing);
		}
		else
		{
			baseParameters->bearings.push_back(boost::optional<osrm::engine::Bearing>());
		}
	}
}
void BaseParameters::Radiuses::set(System::Collections::Generic::IList<System::Nullable<double>>^ value)
{
	// Copy array value
	baseParameters->radiuses.clear();
	for each (System::Nullable<double> radius in value)
	{
		if (radius.HasValue)
			baseParameters->radiuses.push_back(radius.Value);
		else
			baseParameters->radiuses.push_back(boost::optional<double>());
	}
}
void BaseParameters::GenerateHints::set(bool value)
{
	baseParameters->generate_hints = value;
}
void BaseParameters::Hints::set(System::Collections::Generic::IList<System::String^>^ value)
{
	// Copy array value
	baseParameters->hints.clear();
	for each (System::String^ hint in value)
	{
		if (!System::String::IsNullOrEmpty(hint))
		{
			osrm::engine::Hint osrmHint = osrm::engine::Hint::FromBase64(Osrmnet::Utils::ConvertToUtf8(hint));
			baseParameters->hints.push_back(osrmHint);
		}
		else
		{
			baseParameters->hints.push_back(boost::optional<osrm::engine::Hint>());
		}
	}
}
void BaseParameters::Approaches::set(System::Collections::Generic::IList<System::Nullable<Approach>>^ value)
{
	// Copy array value
	baseParameters->approaches.clear();
	for each (System::Nullable<Approach> approach in value)
	{
		if (approach.HasValue)
			baseParameters->approaches.push_back(static_cast<osrm::engine::Approach>(approach.Value));
		else
			baseParameters->approaches.push_back(boost::optional<osrm::engine::Approach>());
	}
}
void BaseParameters::Exclude::set(System::Collections::Generic::IList<System::String^>^ value)
{
	// Copy array value
	baseParameters->exclude.clear();
	for each (System::String^ exclude in value)
	{
		baseParameters->exclude.push_back(Osrmnet::Utils::ConvertToUtf8(exclude));
	}
}

bool BaseParameters::IsValid()
{
	return baseParameters->IsValid();
}