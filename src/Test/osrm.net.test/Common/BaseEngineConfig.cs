using System;
using System.IO;
using System.Reflection;

namespace osrm.net.test.Common
{
    public class BaseEngineConfig
    {
        public string TestDataPath { get; }

        public BaseEngineConfig()
        {
            // This is kinda hacky but tryign to find where the current executing assembly
            // for 3 different kind of test runner (xunit console in appveyor, resharper, visual studio, and whatever
            // in the future), this seems to satisfy all of them for now.
            var executingAssembly = Assembly.GetExecutingAssembly();
            var codeBaseUrl = new Uri(executingAssembly.Location);
            var codeBasePath = Uri.UnescapeDataString(codeBaseUrl.AbsolutePath);
            var currentAssemblyDir = Path.GetDirectoryName(codeBasePath) ?? string.Empty;
            var assemblyName = Path.GetFileNameWithoutExtension(executingAssembly.ManifestModule.Name);
            
            // Compute TestData folder relative to currentAssemblyDir
            var index = currentAssemblyDir.IndexOf(assemblyName, StringComparison.Ordinal);
            // Grab everything from the beginning up to osrm.net.test (index + strelen(osrm.net.test))
            var testDataPath = Environment.CurrentDirectory.Substring(0, index + assemblyName.Length);
            TestDataPath = Path.Combine(testDataPath, "TestData");
        }
    }
}
