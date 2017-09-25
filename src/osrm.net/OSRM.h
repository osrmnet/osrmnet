// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "OsrmFwdDecl.h"

namespace Osrmnet
{
	ref class EngineConfig;

	namespace NearestService {
		ref class NearestParameters;
		ref class NearestResult;
	}

	namespace RouteService {
		ref class RouteParameters;
		ref class RouteResult;
	}	

	namespace TableService {
		ref class TableParameters;
		ref class TableResult;
	}

	namespace MatchService {
		ref class MatchParameters;
		ref class MatchResult;
	}

	namespace TripService {
		ref class TripParameters;
		ref class TripResult;
	}

	namespace TileService {
		ref class TileParameters;
		ref class TileResult;
	}

	public enum class Status
	{
		Ok,
		Error
	};

	public ref class Osrm 
	{		
	private:
		osrm::OSRM* const osrmEngine;

	public: 
		Status Nearest(NearestService::NearestParameters^, [System::Runtime::InteropServices::Out] NearestService::NearestResult^%);
		Status Route(RouteService::RouteParameters^, [System::Runtime::InteropServices::Out] RouteService::RouteResult^%);
		Status Table(TableService::TableParameters^, [System::Runtime::InteropServices::Out] TableService::TableResult^%);
		Status Match(MatchService::MatchParameters^, [System::Runtime::InteropServices::Out] MatchService::MatchResult^%);
		Status Trip(TripService::TripParameters^, [System::Runtime::InteropServices::Out] TripService::TripResult^%);
		Status Tile(TileService::TileParameters^, [System::Runtime::InteropServices::Out] System::String^%);

		Osrm(EngineConfig^);
		~Osrm()
		{
			this->!Osrm();
			System::GC::SuppressFinalize(this);
		}
		!Osrm();		
	};
}

