using System.Collections.Generic;
using System.Linq;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.RouteService;
using Osrmnet.TableService;
using Xunit;
using AnnotationsType = Osrmnet.AnnotationsType;

namespace osrm.net.test.Tests
{
    public class WhenUsingOrlandoMld : IClassFixture<OrlandoEngineConfigMld>
    {
        private readonly OrlandoEngineConfigMld _orlandoEngineConfigMld;

        public WhenUsingOrlandoMld(OrlandoEngineConfigMld orlandoEngineConfigMld)
        {
            _orlandoEngineConfigMld = orlandoEngineConfigMld;
        }

        [Fact]
        public void InitOsrmEngine_ShouldCreateOsrmObject()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
            {
                Assert.NotNull(sut);
            }
        }

        [Fact]
        public void RoutingWithValidStartEndCoordinate_ShouldReturnStatusOk()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
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
        public void RoutingWithAnnotationTrue_ShouldReturnStatusOkWithValidAnnotations()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Annotations = AnnotationsType.All,
                }, out routeResult);

                var annotations = routeResult.Routes.SelectMany(x => x.Legs).Select(y => y.Annotation).Where(x => x != null);
                var enumerable = annotations as IList<Annotation> ?? annotations.ToList();
                var distances = enumerable.SelectMany(x => x.Distance);
                var nodes = enumerable.SelectMany(x => x.Nodes);

                Assert.Equal(Status.Ok, result);
                OsrmTestAssert.AssertValidRoute(routeResult);

                Assert.NotEmpty(distances);
                Assert.NotEmpty(nodes);
            }
        }

        [Fact]
        public void RoutingWithAnnotationFalse_ShouldReturnStatusOkWithEmptyAnnotations()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Annotations = AnnotationsType.All,
                }, out routeResult);

                var annotations = routeResult.Routes.SelectMany(x => x.Legs).Select(y => y.Annotation).Where(x => x != null);

                Assert.Equal(Status.Ok, result);
                OsrmTestAssert.AssertValidRoute(routeResult);
                Assert.NotEmpty(annotations);
            }
        }

        [Fact]
        public void RoutingWithStepsTrue_ShouldReturnValidSteps()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Steps = true,
                }, out routeResult);

                Assert.Equal(Status.Ok, result);
                OsrmTestAssert.AssertValidRoute(routeResult);
                var steps = routeResult.Routes.SelectMany(x => x.Legs).SelectMany(x => x.Steps);
                Assert.NotEmpty(steps);
            }
        }

        [Fact]
        public void RoutingWithStepsFalse_ShouldReturnEmpty()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Steps = false,
                }, out routeResult);

                Assert.Equal(Status.Ok, result);
                OsrmTestAssert.AssertValidRoute(routeResult);
                var steps = routeResult.Routes.SelectMany(x => x.Legs).SelectMany(x => x.Steps);
                Assert.Empty(steps);
            }
        }

        [Fact]
        public void RoutingWithMoreAlternateAllowed_ShouldFailWithTooBigCode()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
            {
                RouteResult routeResult;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633),
                        new Coordinate(28.598181, -81.207633),
                        new Coordinate(28.598181, -81.207633),
                    },
                    Steps = false,
                    NumberOfAlternatives = 4
                }, out routeResult);

                Assert.Equal(Status.Error, result);
                Assert.Equal("TooBig", routeResult.Code);
            }
        }

        [Fact]
        public void TableWithDefaultConfig_ShouldReturnGoodResultWithDurationAsDefault()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
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
        public void TableWithAnnotationDistance_ShouldReturnDistanceOnly()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
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
                Assert.NotEmpty(tableResult.Distances);
                Assert.Empty(tableResult.Durations);
            }
        }

        [Fact]
        public void TableWithAllAnnotation_ShouldReturnDurationsAndDistances()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfigMld.EngineConfig))
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