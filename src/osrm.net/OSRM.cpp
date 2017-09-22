// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "Stdafx.h"
#include "OSRM.h"
#include "EngineConfig.h"
#include "OsrmException.h"

#include ".\Nearest\NearestParameters.h"
#include ".\Nearest\NearestResult.h"

#include ".\Route\RouteParameters.h"
#include ".\Route\RouteResult.h"

#include ".\Table\TableParameters.h"
#include ".\Table\TableResult.h"

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

Status Osrm::Nearest(NearestService::NearestParameters^ nearestParameters, [System::Runtime::InteropServices::Out] NearestService::NearestResult^% result)
{
	osrm::util::json::Object jsonResult;
	osrm::Status retVal = osrm::Status::Error;
	try
	{
		if (nearestParameters->IsValid())
		{
			retVal = osrmEngine->Nearest(*nearestParameters->InnerObject(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = NearestService::NearestResult::FromJsonObject(jsonResult);
			}
		}
	}
	catch (osrm::util::exception routeException)
	{
		retVal = osrm::Status::Error;
	}
	catch (System::Exception^)
	{
		// Rethrown managed exception as it is
		throw;
	}
	catch (...)
	{
		throw gcnew OsrmException("Unexpected exception is thrown within internal libosrm library.");
	}
	return static_cast<Status>(retVal);
}

Status Osrm::Route(RouteService::RouteParameters^ routeParameters, [System::Runtime::InteropServices::Out] RouteService::RouteResult^% result)
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
				result = RouteService::RouteResult::FromJsonObject(jsonResult, routeParameters);
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

Status Osrm::Table(TableService::TableParameters^ tableParameters, [System::Runtime::InteropServices::Out] TableService::TableResult^% result)
{
	osrm::util::json::Object jsonResult;
	osrm::Status retVal = osrm::Status::Error;
	try
	{
		if (tableParameters->IsValid())
		{
			retVal = osrmEngine->Table(*tableParameters->InnerObject(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = TableService::TableResult::FromJsonObject(jsonResult);
			}
		}
	}
	catch (osrm::util::exception routeException)
	{
		retVal = osrm::Status::Error;
	}
	catch (System::Exception^)
	{
		// Rethrown managed exception as it is
		throw;
	}
	catch (...)
	{
		throw gcnew OsrmException("Unexpected exception is thrown within internal libosrm library.");
	}
	return static_cast<Status>(retVal);
}