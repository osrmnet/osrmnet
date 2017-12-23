# osrmnet
[![Build status](https://ci.appveyor.com/api/projects/status/temd3bf4l84h3lyh/branch/master?svg=true)](https://ci.appveyor.com/project/ssuluh/osrmnet/branch/master)


This project provides necessary .NET wrapper to use OSRM library directly without the web server (https://github.com/Project-OSRM/osrm-backend).

Our design goal is to follow as close as possible the OSRM project APIs and data type.  User should be able to use the existing OSRM documentation to use this library.

Contribution is always welcome, please email me:  ssuluh@yahoo.com

# Build Locally
Please read the OSRM Wiki:  https://github.com/Project-OSRM/osrm-backend/wiki/Windows-Compilation.
Ensure the correct MS C/C++ runtime library version installed and valid temp directory specified in your .stxxl.txt before you run osrm-extract and other osrm binaries.
To build locally:
1. Open Powershell code and run .\build.ps1
2. Use msbuild.exe or Visual Studio 2015/2017 to build the project. (If you use VS 2017, make sure you don't upgrade the project).

# Status
This project is still at pre-release state, it can use more unit test coverage but other than that all OSRM method should be implemented.

# Installation
Use nuget (http://www.nuget.org/packages/osrmnet)

# License
MIT License

Copyright (c) 2016 Surya Suluh and contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

