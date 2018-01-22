using Osrmnet;
using Xunit;

namespace osrm.net.test
{
    public class EngineConfigTest
    {
        [Fact]
        public void DefaultEngineConfigAlgorithmIsMld()
        {
            var sut = new EngineConfig();

            Assert.Equal(Algorithm.MLD, sut.Algorithm);
        }

        [Fact]
        public void DefaultEngineConfigSharedMemoryIsFalse()
        {
            var sut = new EngineConfig();
            Assert.False(sut.UseSharedMemory);
        }
    }
}