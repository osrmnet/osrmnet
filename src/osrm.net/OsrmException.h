// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once

namespace Osrmnet 
{
	[System::Serializable]
	public ref class OsrmException : public System::Exception
	{
	public:
		OsrmException(System::String^ exceptionMessage) : System::Exception(exceptionMessage)
		{
		}
	};
}
