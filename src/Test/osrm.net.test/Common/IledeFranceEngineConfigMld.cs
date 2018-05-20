using System;
using System.IO;
using Osrmnet;

namespace osrm.net.test.Common
{
    public class IledeFranceEngineConfigMld : BaseEngineConfig, IDisposable
    {
        public IledeFranceEngineConfigMld()
        {
            var testDataPath = Path.Combine(TestDataPath, "mld", "ile-de-france-latest.osrm");
            EngineConfig = new EngineConfig
            {
                StorageConfig = testDataPath,
                UseSharedMemory = false,
                Algorithm = Algorithm.MLD
            };
        }

        public EngineConfig EngineConfig { get; }

        public void Dispose()
        {
            EngineConfig.Dispose();
        }
    }
}