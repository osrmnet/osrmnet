using System.Collections.Generic;
using System.Linq;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.RouteService;
using Xunit;

namespace osrm.net.test.Routing
{
    public class WhenUsingOrlandoDataFile : IClassFixture<OrlandoEngineConfig>
    {
        private readonly OrlandoEngineConfig _orlandoEngineConfig;

        private void AssertValidRoute(RouteResult routeResult)
        {
            Assert.Equal("Ok", routeResult.Code);
            Assert.NotEmpty(routeResult.Routes);
            Assert.NotEmpty(routeResult.Waypoints);
        }

        public WhenUsingOrlandoDataFile(OrlandoEngineConfig orlandoEngineConfig)
        {
            _orlandoEngineConfig = orlandoEngineConfig;
        }

        [Fact]
        public void InitOsrmEngine_ShouldCreateOsrmObject()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
            {
                Assert.NotNull(sut);
            }
        }

        [Fact]
        public void RoutingWithValidStartEndCoordinate_ShouldReturnStatusOk()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
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

        [Fact]
        public void RoutingWithAnnotationTrue_ShouldReturnStatusOkWithValidAnnotations()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
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
                AssertValidRoute(routeResult);

                Assert.NotEmpty(distances);
                Assert.NotEmpty(nodes);
            }
        }

        [Fact]
        public void RoutingWithAnnotationFalse_ShouldReturnStatusOkWithEmptyAnnotations()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
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
                AssertValidRoute(routeResult);
                Assert.NotEmpty(annotations);
            }
        }

        [Fact]
        public void RoutingWithStepsTrue_ShouldReturnValidSteps()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
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
                AssertValidRoute(routeResult);
                var steps = routeResult.Routes.SelectMany(x => x.Legs).SelectMany(x => x.Steps);
                Assert.NotEmpty(steps);
            }
        }

        [Fact]
        public void RoutingWithStepsTrue_ShouldReturnEmpty()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
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
                AssertValidRoute(routeResult);
                var steps = routeResult.Routes.SelectMany(x => x.Legs).SelectMany(x => x.Steps);
                Assert.Empty(steps);
            }
        }
    }
}