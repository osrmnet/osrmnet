// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "Stdafx.h"
#include "OSRM.h"
#include "EngineConfig.h"
#include "OsrmException.h"

#include ".\Route\RouteParameters.h"
#include ".\Route\RouteResult.h"

#include "osrm\osrm.hpp"
#include "engine\engine_config.hpp"
#include "osrm\json_container.hpp"
#include "util\exception.hpp"

using namespace Osrmnet;

Osrm::Osrm(EngineConfig^ engineConfig) try : osrmEngine (new osrm::OSRM(*(engineConfig->InnerObject())))
{
}
catch(osrm::util::exception exception)
{
	throw gcnew OsrmException(gcnew System::String(exception.what()));
}

Osrm::!Osrm()
{
	delete osrmEngine;
}

Status Osrm::Route(Route::RouteParameters^ routeParameters, [System::Runtime::InteropServices::Out] Route::RouteResult^% result)
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
				result = Route::RouteResult::FromJsonObject(jsonResult, routeParameters);
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
		throw gcnew OsrmException("Unexpected exception is thrown within internal libosrm library.");
	}
	return static_cast<Status>(retVal);
}
