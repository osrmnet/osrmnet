using System;
using System.IO;
using osrmnet;

namespace osrm.net.test
{
    public class DefaultEngineConfig : IDisposable
    {
        public DefaultEngineConfig()
        {
            var index = Environment.CurrentDirectory.IndexOf("osrm.net.test", StringComparison.Ordinal);
            // Grab everything from the beginning up to osrm.net.test (index + strelen(osrm.net.test))
            var testDataPath = Environment.CurrentDirectory.Substring(0, index + 13);
            testDataPath = Path.Combine(testDataPath, "TestData", "Orlando.osrm");
            if (!File.Exists(testDataPath))
            {
                throw new InvalidOperationException("Test is invalid as it can't find test data folder.");
            }

            EngineConfig = new EngineConfig
            {
                StorageConfig = testDataPath,
                UseSharedMemory = false
            };
        }

        public EngineConfig EngineConfig { get; private set; }

        public void Dispose()
        {
        }
    }
}