// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "Stdafx.h"
#include "OSRM.h"
#include "EngineConfig.h"
#include "RouteParameters.h"
#include "RouteResult.h"
#include "OsrmException.h"

#include "osrm\osrm.hpp"
#include "engine\engine_config.hpp"
#include "osrm\json_container.hpp"
#include "util\exception.hpp"

osrmnet::Osrm::Osrm(EngineConfig^ engineConfig) try : osrmEngine (new osrm::OSRM(*(engineConfig->InnerObject())))
{
}
catch(osrm::util::exception exception)
{
	throw gcnew osrmnet::OsrmException(gcnew System::String(exception.what()));
}

osrmnet::Osrm::!Osrm()
{
	delete osrmEngine;
}

osrmnet::Status osrmnet::Osrm::Route(osrmnet::RouteParameters^ routeParameters, [System::Runtime::InteropServices::Out] System::Collections::Generic::IEnumerable<RouteResult^>^% result)
{
	osrm::util::json::Object jsonResult;
	osrm::Status retVal = osrm::Status::Error;
	try
	{
		if (routeParameters->IsValid())
		{
			retVal = osrmEngine->Route(*routeParameters->InnerObject(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = RouteResult::FromJsonObject(jsonResult, routeParameters);
			}
		}		
	}
	catch(osrm::util::exception routeException)
	{
		retVal = osrm::Status::Error;
	}
	catch(System::Exception^)
	{
		// Rethrown managed exception as it is
		throw;
	}
	catch(...)
	{
		throw gcnew osrmnet::OsrmException("Unexpected exception is thrown within internal libosrm library.");
	}
	return static_cast<osrmnet::Status>(retVal);
}
