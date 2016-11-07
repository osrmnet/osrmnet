// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

// Microsoft C++/CLI Specific when using BOOST 1.6.x.
// Boost is using reserved words 'generic' in boost/filesystem/path.hpp
#ifdef __cplusplus_cli
#define generic __identifier(generic)
#endif
#include <boost/filesystem.hpp>
#ifdef __cplusplus_cli
#undef generic
#endif


