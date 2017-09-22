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
		Status Nearest(NearestService::NearestParameters^ nearestParameters, [System::Runtime::InteropServices::Out] NearestService::NearestResult^% result);
		Status Route(RouteService::RouteParameters^ routeParameters, [System::Runtime::InteropServices::Out] RouteService::RouteResult^% result);
		Status Table(TableService::TableParameters^ tableParameters, [System::Runtime::InteropServices::Out] TableService::TableResult^% result);

		Osrm(EngineConfig^ engineConfig);
		~Osrm()
		{
			this->!Osrm();
			System::GC::SuppressFinalize(this);
		}
		!Osrm();		
	};
}

