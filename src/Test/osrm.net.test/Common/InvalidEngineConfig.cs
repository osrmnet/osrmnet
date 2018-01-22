using System;
using Osrmnet;

namespace osrm.net.test.Common
{
    public class InvalidEngineConfig : BaseEngineConfig, IDisposable
    {
        public EngineConfig EngineConfig { get; }

        public InvalidEngineConfig()
        {
            EngineConfig = new EngineConfig()
            {
                StorageConfig = "Bad path",
                UseSharedMemory = false
            };
        }
        public void Dispose()
        {
            EngineConfig.Dispose();
        }
    }
}