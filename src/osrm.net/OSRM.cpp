// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#include "Stdafx.h"
#include "OSRM.h"
#include "EngineConfig.h"
#include "OsrmException.h"
#include <msclr\marshal_cppstd.h>

#include ".\Nearest\NearestParameters.h"
#include ".\Nearest\NearestResult.h"

#include ".\Route\RouteParameters.h"
#include ".\Route\RouteResult.h"

#include ".\Table\TableParameters.h"
#include ".\Table\TableResult.h"

#include ".\Match\MatchParameters.h"
#include ".\Match\MatchResult.h"

#include ".\Trip\TripParameters.h"
#include ".\Trip\TripResult.h"

#include ".\Tile\TileParameters.h"

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
			retVal = osrmEngine->Nearest(*nearestParameters->InnerNearestParameters(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = NearestService::NearestResult::FromJsonObject(jsonResult);
			}
		}
	}
	catch (osrm::util::exception exception)
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
			retVal = osrmEngine->Route(*routeParameters->InnerRouteParameters(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = RouteService::RouteResult::FromJsonObject(jsonResult, routeParameters);
			}
		}		
	}
	catch(osrm::util::exception exception)
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
	catch (osrm::util::exception exception)
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

Status Osrm::Match(MatchService::MatchParameters^ matchParameters, [System::Runtime::InteropServices::Out] MatchService::MatchResult^% result)
{
	osrm::util::json::Object jsonResult;
	osrm::Status retVal = osrm::Status::Error;
	try
	{
		if (matchParameters->IsValid())
		{
			retVal = osrmEngine->Match(*matchParameters->InnerMatchParameters(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = MatchService::MatchResult::FromJsonObject(jsonResult, matchParameters);
			}
		}
	}
	catch (osrm::util::exception exception)
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

Status Osrm::Trip(TripService::TripParameters^ tripParameters, [System::Runtime::InteropServices::Out] TripService::TripResult^% result)
{
	osrm::util::json::Object jsonResult;
	osrm::Status retVal = osrm::Status::Error;
	try
	{
		if (tripParameters->IsValid())
		{
			retVal = osrmEngine->Trip(*tripParameters->InnerTripParameters(), jsonResult);
			if (retVal == osrm::Status::Ok)
			{
				result = TripService::TripResult::FromJsonObject(jsonResult, tripParameters);
			}
		}
	}
	catch (osrm::util::exception exception)
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

Status Osrm::Tile(TileService::TileParameters^ tileParameters, [System::Runtime::InteropServices::Out] System::String^% result)
{
	std::string stringResult;
	osrm::Status retVal = osrm::Status::Error;
	try
	{
		if (tileParameters->IsValid())
		{
			retVal = osrmEngine->Tile(*tileParameters->InnerTileParameters(), stringResult);
			if (retVal == osrm::Status::Ok)
			{
				result = msclr::interop::marshal_as<System::String^>(stringResult);
			}
		}
	}
	catch (osrm::util::exception exception)
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