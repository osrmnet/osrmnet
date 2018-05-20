//////////////////////////////////////////////////////////////////////
// Constant
//////////////////////////////////////////////////////////////////////
var slnName = "osrmnet.sln";
var slnPath = @".\src\";
var libosrmMajorVersion = "5.18";
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
      DeleteDirectory(testDataPath + "TestData", true);
      DeleteDirectory(libOsrmPath + "libosrm", true);
    });

Task("Build")
.Description("Build Project")
.IsDependentOn("GetDependencies")
.Does(() =>
{
  // msbuild instruction:
  // msbuild .\src\osrm.net.sln /t:Rebuild /p:Configuration=Release;Platform="x64" /m
  MSBuild("./src/osrm.net.sln", configurator => {
    configurator.UseToolVersion(MSBuildToolVersion.VS2017)
    .SetConfiguration("Release")
    .SetPlatformTarget(PlatformTarget.x64)
    .WithTarget("Rebuild");
  });
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