osrmnet
=======
[![Build status](https://ci.appveyor.com/api/projects/status/temd3bf4l84h3lyh/branch/master?svg=true)](https://ci.appveyor.com/project/ssuluh/osrmnet/branch/master)
[![NuGet](https://img.shields.io/nuget/dt/osrmnet.svg)]()

** Help Wanted To Maintain This Repo ! **

This project provides necessary .NET wrapper to use OSRM library directly without the web server (https://github.com/Project-OSRM/osrm-backend).

Our design goal is to follow as close as possible OSRM project's APIs and data types.  User should be able to use OSRM documentation to use this library.

Contribution is always welcome, please email me:  ssuluh@yahoo.com

# What's New
- Dotnet Core 3.1 runtime is now deprecated. Dotnet 6 is now the current supported runtime
- License has changed from MIT to Apache V2 effective from [this commit](https://github.com/osrmnet/osrmnet/commit/a8b886f9e39fcafdc292292d76cfe406f4bcd95d) moving forward.
# Supported OSRM Version
[GitHub Project-OSRM/osrm-backend 5.26](https://github.com/Project-OSRM/osrm-backend/tree/5.26)

# Installation
1. System Requirements:
   - Minimum: Windows 10 1803 or greater (and its Windows Server equivalence)
   - Microsoft Visual C++ Redistributable (https://docs.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170)
   - Dotnet 6.0 Runtime (https://dotnet.microsoft.com/en-us/download/dotnet/6.0)

1. Pull package osrmnet package (http://www.nuget.org/packages/osrmnet) in your project

# Build Locally
Please read the OSRM Wiki:  https://github.com/Project-OSRM/osrm-backend/wiki/Windows-Compilation.
Ensure the correct MS C/C++ runtime library version installed and valid temp directory specified in your .stxxl.txt before you run osrm-extract and other osrm binaries.

To build locally:

Open Powershell and run .\build.ps1 from the root directory of the project.

# How To Get Precompiled osrm libraries and tools
osrm-backend project does not officially support Windows platform. The windows binaries in that project are not the latest.
1. Clone this project
2. Run this command from powershell:
`.\build.ps1 -Target "GetDependencies"
3. Location of the osrm libraries and app: .\osrmnet\src\osrm.net\libosrm\redist\osrm_5.26.0.zip

# License
Copyright 2016 Surya Suluh and OSRMNET

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

