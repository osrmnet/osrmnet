#pragma once

#include <string>
#include <locale>
#include <codecvt>

#include <msclr\marshal_cppstd.h>

namespace Osrmnet
{
	namespace Utils
	{
		System::String^ ConvertFromUtf8(std::string src);
		std::string ConvertToUtf8(System::String^ src);
	}
};

