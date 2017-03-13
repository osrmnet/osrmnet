// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

#include "OsrmFwdDecl.h"

namespace Osrmnet
{
	ref class EngineConfig;

	namespace Route {
		ref class RouteParameters;
		ref class RouteResult;
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
		
		Status Route(Route::RouteParameters^ routeParameters, [System::Runtime::InteropServices::Out] Route::RouteResult^% result);

		Osrm(EngineConfig^ engineConfig);
		~Osrm()
		{
			this->!Osrm();
			System::GC::SuppressFinalize(this);
		}
		!Osrm();		
	};
}

