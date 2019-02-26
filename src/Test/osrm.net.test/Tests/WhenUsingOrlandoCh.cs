using System.Collections.Generic;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.RouteService;
using Osrmnet.TableService;
using Xunit;

namespace osrm.net.test.Tests
{
    public class WhenUsingOrlandoCh : IClassFixture<OrlandoEngineConfigCh>
    {
        private readonly OrlandoEngineConfigCh _engineConfig;

        public WhenUsingOrlandoCh(OrlandoEngineConfigCh engineConfig)
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
                OsrmTestAssert.AssertValidRoute(routeResult);
            }
        }

        [Fact]
        public void TableWithDefaultConfig_ShouldReturnGoodResultWithDurationAsDefault()
        {
            using (Osrm sut = new Osrm(_engineConfig.EngineConfig))
            {
                var result = sut.Table(new TableParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.551750, -81.450598),
                        new Coordinate(28.774844, -81.242909),
                        new Coordinate(28.636579, -81.427413)
                    },

                }, out TableResult tableResult);
                Assert.Equal(Status.Ok, result);
                Assert.NotEmpty(tableResult.Durations);
            }
        }

        [Fact]
        public void TableWithDistanceAnnotation_ShouldReturnGoodResultWithDistances()
        {
            using (Osrm sut = new Osrm(_engineConfig.EngineConfig))
            {
                var result = sut.Table(new TableParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.551750, -81.450598),
                        new Coordinate(28.774844, -81.242909),
                        new Coordinate(28.636579, -81.427413)
                    },
                    Annotations = Osrmnet.TableService.AnnotationsType.Distance

                }, out TableResult tableResult);
                Assert.Equal(Status.Ok, result);
                Assert.Empty(tableResult.Durations);
                Assert.NotEmpty(tableResult.Distances);
            }
        }

        [Fact]
        public void TableWithAllAnnotation_ShouldReturnDurationsAndDistances()
        {
            using (Osrm sut = new Osrm(_engineConfig.EngineConfig))
            {
                var result = sut.Table(new TableParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.551750, -81.450598),
                        new Coordinate(28.774844, -81.242909),
                        new Coordinate(28.636579, -81.427413)
                    },
                    Annotations = Osrmnet.TableService.AnnotationsType.All

                }, out TableResult tableResult);
                Assert.Equal(Status.Ok, result);
                Assert.NotEmpty(tableResult.Durations);
                Assert.NotEmpty(tableResult.Distances);
            }
        }
    }
}
