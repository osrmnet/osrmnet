using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.RouteService;
using Xunit;

using static osrm.net.test.Common.OsrmTestAssert;

namespace osrm.net.test.Routing
{
    public class WhenUsingOrlandoDataFileWithCHAlgorithm : IClassFixture<OrlandoEngineConfigCHAlgorithm>
    {
        private readonly OrlandoEngineConfigCHAlgorithm _engineConfig;

        public WhenUsingOrlandoDataFileWithCHAlgorithm(OrlandoEngineConfigCHAlgorithm engineConfig)
        {
            _engineConfig = engineConfig;
        }

        [Fact]
        public void InitOsrmEngine_ShouldCreateOsrmObject()
        {
            using (Osrm sut = new Osrm(_engineConfig.EngineConfig))
            {
                Assert.NotNull(sut);
            }
        }

        [Fact]
        public void RoutingWithValidStartEndCoordinate_ShouldReturnStatusOk()
        {
            using (Osrm sut = new Osrm(_engineConfig.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                }, out routeResult);
                Assert.Equal(Status.Ok, result);
                AssertValidRoute(routeResult);
            }
        }
    }
}
