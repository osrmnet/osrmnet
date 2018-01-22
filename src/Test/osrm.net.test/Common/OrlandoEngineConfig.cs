using System;
using System.IO;
using Osrmnet;

namespace osrm.net.test.Common
{
    public class OrlandoEngineConfig : BaseEngineConfig, IDisposable
    {
        public EngineConfig EngineConfig { get; }

        public OrlandoEngineConfig()
        {
            var testDataPath = Path.Combine(TestDataPath, "mld", "Orlando.osrm");
            EngineConfig = new EngineConfig()
            {
                StorageConfig = testDataPath,
                UseSharedMemory = false,
                Algorithm = Algorithm.MLD
            };
        }
        public void Dispose()
        {
            EngineConfig.Dispose();
        }
    }
}