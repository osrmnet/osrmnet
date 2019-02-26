using osrm.net.test.Common;
using Osrmnet;
using Xunit;

namespace osrm.net.test.Tests
{
    public class WhenUsingInvalidEngineConfig : IClassFixture<InvalidEngineConfig>
    {
        private readonly InvalidEngineConfig _invalidEngine;

        public WhenUsingInvalidEngineConfig(InvalidEngineConfig invalidEngine)
        {
            _invalidEngine = invalidEngine;
        }

        [Fact]
        public void InitEngine_ShouldThrowOsrmnetException()
        {
            var ex = Assert.Throws<OsrmException>(() =>
            {
                using (var sut = new Osrm(_invalidEngine.EngineConfig))
                {
                }
            });
        }
    }
}