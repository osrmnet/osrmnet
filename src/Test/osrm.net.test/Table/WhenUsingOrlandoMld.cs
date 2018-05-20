using System.Collections.Generic;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.RouteService;
using Osrmnet.TableService;
using Xunit;
using AnnotationsType = Osrmnet.TableService.AnnotationsType;

namespace osrm.net.test.Table
{
    public class WhenUsingOrlandoMld : IClassFixture<OrlandoEngineConfigMld>
    {
        public WhenUsingOrlandoMld(OrlandoEngineConfigMld config)
        {
            _config = config;
        }

        private readonly OrlandoEngineConfigMld _config;

        [Fact]
        public void TableWithDefaultConfig_ShouldReturnGoodResultWithDurationAsDefault()
        {
            using (Osrm sut = new Osrm(_config.EngineConfig))
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
            using (Osrm sut = new Osrm(_config.EngineConfig))
            {
                var result = sut.Table(new TableParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.551750, -81.450598),
                        new Coordinate(28.774844, -81.242909),
                        new Coordinate(28.636579, -81.427413)
                    },
                    Annotations = AnnotationsType.Distance

                }, out TableResult tableResult);
                Assert.NotEmpty(tableResult.Distances);
                Assert.Empty(tableResult.Durations);
            }
        }

        [Fact]
        public void TableWithAllAnnotation_ShouldReturnDurationsAndDistances()
        {
            using (Osrm sut = new Osrm(_config.EngineConfig))
            {
                var result = sut.Table(new TableParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.551750, -81.450598),
                        new Coordinate(28.774844, -81.242909),
                        new Coordinate(28.636579, -81.427413)
                    },
                    Annotations = AnnotationsType.All

                }, out TableResult tableResult);
                Assert.Equal(Status.Ok, result);
                Assert.NotEmpty(tableResult.Durations);
                Assert.NotEmpty(tableResult.Distances);
            }
        }
    }
}