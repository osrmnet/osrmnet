// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
namespace osrm
{
	class OSRM;
	namespace engine
	{
		struct EngineConfig;
		namespace api
		{
			struct BaseParameters;
			struct NearestParameters;
			struct RouteParameters;
			struct TableParameters;
			struct MatchParameters;
			struct TripParameters;
			struct TileParameters;
		}
	}
	namespace storage
	{
		struct StorageConfig;
	}

	namespace util
	{
		namespace json
		{
			struct Object;
			struct Array;
			struct String;
			struct Number;
			struct True;
			struct False;
			struct Array;
		}
	}
}
