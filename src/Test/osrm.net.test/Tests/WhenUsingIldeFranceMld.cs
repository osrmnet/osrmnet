using System.Collections.Generic;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.RouteService;
using Xunit;

namespace osrm.net.test.Tests
{
    public class WhenUsingIldeFranceMld : IClassFixture<IledeFranceEngineConfigMld>
    {
        public WhenUsingIldeFranceMld(IledeFranceEngineConfigMld config)
        {
            _config = config;
        }

        private readonly IledeFranceEngineConfigMld _config;

        [Fact(Skip = "il-de-france test data is not uploaded by default")]
        //[Fact]
        public void RoutingWithValidStartEndCoordinate_ShouldReturnStatusOk()
        {
            using (var sut = new Osrm(_config.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters
                {
                    Coordinates = new List<Coordinate>
                    {
                        new Coordinate(48.829717, 2.349566),
                        new Coordinate(48.629575, 2.472986)
                    }
                }, out routeResult);
                Assert.Equal(Status.Ok, result);
                OsrmTestAssert.AssertValidRoute(routeResult);
            }
        }
    }
}