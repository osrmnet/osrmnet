//////////////////////////////////////////////////////////////////////
// Constant
//////////////////////////////////////////////////////////////////////
var slnName = "osrmnet.sln";
var slnPath = @".\src\";
var libosrmMajorVersion = "5.26";
var libosrmMinorVersion = "0";
var s3Path = @"https://s3.amazonaws.com/osrmnet/" + libosrmMajorVersion + @"/";

var testDataPath = slnPath + @"Test\osrm.net.test\";
var libOsrmPath = slnPath + @"osrm.net\";

//////////////////////////////////////////////////////////////////////
// InitDependencies
//////////////////////////////////////////////////////////////////////
Task("GetDependencies")
    .Description("Get project dependencies")
    .Does(() =>
    {
      if(!DirectoryExists(testDataPath + "TestData"))
      {
        var testDataSrc = s3Path + "testdata.zip";
        var testDataDest = testDataPath + "TestData.zip";
        DownloadFile(testDataSrc, testDataDest);
        CleanDirectory(testDataPath + "TestData");
        Unzip(testDataDest, testDataPath + "TestData");
        DeleteFile(testDataDest);
      }

      if(!DirectoryExists(libOsrmPath + "libosrm"))
      {
        var libOsrmSrc = s3Path + $"libosrm-{libosrmMajorVersion}.{libosrmMinorVersion}.zip";
        var libOsrmDest = libOsrmPath + "libosrm.zip";
        DownloadFile(libOsrmSrc, libOsrmDest);
        CleanDirectory(libOsrmPath + "libosrm");
        Unzip(libOsrmDest, libOsrmPath + "libosrm");
        DeleteFile(libOsrmDest);
      }      
    });

//////////////////////////////////////////////////////////////////////
// CleanDependencies
//////////////////////////////////////////////////////////////////////
Task("CleanDependencies")
    .Description("Clean project dependencies")
    .Does(() =>
    {
      var recurseForceDirSetting = new DeleteDirectorySettings
      {
        Recursive = true,
        Force = true        
      };
      DeleteDirectory(testDataPath + "TestData", recurseForceDirSetting);
      DeleteDirectory(libOsrmPath + "libosrm", recurseForceDirSetting);
    });

Task("Build")
.Description("Build Project")
.IsDependentOn("GetDependencies")
.Does(() =>
{
  // msbuild instruction:
  // msbuild .\src\osrm.net.sln /t:Rebuild /p:Configuration=Release;Platform="x64" /m
  MSBuild("./src/osrm.net.sln", configurator => {
    configurator.UseToolVersion(MSBuildToolVersion.VS2022)
    .SetConfiguration("Release")
    .SetPlatformTarget(PlatformTarget.x64)
    .WithTarget("Rebuild");
  });
});

Task("Test")
.Description("Test Project")
.Does(() =>
{
  DotNetVSTest("./src/Test/osrm.net.test/bin/Release/net6.0/osrm.net.test.dll");
});

//////////////////////////////////////////////////////////////////////
// Default
//////////////////////////////////////////////////////////////////////
var target = Argument("target", "Default");
Task("Default")
  .IsDependentOn("Build")
  .Does(() =>
{  
});

RunTarget(target);