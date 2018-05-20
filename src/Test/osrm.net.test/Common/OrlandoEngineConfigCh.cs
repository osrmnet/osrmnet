using System;
using System.IO;
using Osrmnet;

namespace osrm.net.test.Common
{
    public class OrlandoEngineConfigCh : BaseEngineConfig, IDisposable
    {
        public EngineConfig EngineConfig { get; }

        public OrlandoEngineConfigCh()
        {
            var testDataPath = Path.Combine(TestDataPath, "CH", "Orlando.osrm");
            EngineConfig = new EngineConfig()
            {
                StorageConfig = testDataPath,
                UseSharedMemory = false,
                Algorithm = Algorithm.CH
            };
        }
        public void Dispose()
        {
            EngineConfig.Dispose();
        }
    }
}