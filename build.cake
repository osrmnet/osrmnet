//////////////////////////////////////////////////////////////////////
// Constant
//////////////////////////////////////////////////////////////////////
var slnName = "osrmnet.sln";
var slnPath = @".\src\";
var libosrmVersion = "5.4.2";
var s3Path = @"https://s3.amazonaws.com/osrmnet/" + libosrmVersion + @"/";

var testDataPath = slnPath + @"Test\osrm.net.test\";
var libOsrmPath = slnPath + @"osrm.net\";


//////////////////////////////////////////////////////////////////////
// InitDependencies
//////////////////////////////////////////////////////////////////////
Task("InitDependencies")
    .Description("Init project dependencies")
    .Does(() =>
    {
      if(!DirectoryExists(testDataPath + "TestData"))
      {
        var testDataSrc = s3Path + "TestData.zip";
        var testDataDest = testDataPath + "TestData.zip";
        DownloadFile(testDataSrc, testDataDest);
        CleanDirectory(testDataPath + "TestData");
        Unzip(testDataDest, testDataPath);
        DeleteFile(testDataDest);
      }

      if(!DirectoryExists(libOsrmPath + "libosrm"))
      {
        var libOsrmSrc = s3Path + "libosrm.zip";
        var libOsrmDest = libOsrmPath + "libosrm.zip";
        DownloadFile(libOsrmSrc, libOsrmDest);
        CleanDirectory(libOsrmPath + "libosrm");
        Unzip(libOsrmDest, libOsrmPath);
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

//////////////////////////////////////////////////////////////////////
// Default
//////////////////////////////////////////////////////////////////////
var target = Argument("target", "Default");
Task("Default")
  .IsDependentOn("InitDependencies")
  .Does(() =>
{  
});

RunTarget(target);