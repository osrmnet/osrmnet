#include "Stdafx.h"
#include "Utils.h"

System::String^ Osrmnet::Utils::ConvertFromUtf8(std::string src)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wstr = converter.from_bytes(src);

	return msclr::interop::marshal_as<System::String^>(wstr);
}

std::string Osrmnet::Utils::ConvertToUtf8(System::String^ src)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring wstr = msclr::interop::marshal_as<std::wstring>(src);

	return converter.to_bytes(wstr);
}