using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using osrm.net.test.Common;
using Osrmnet;
using Osrmnet.TableService;
using Xunit;
using AnnotationsType = Osrmnet.TableService.AnnotationsType;

namespace osrm.net.test.Table
{
    public class WhenUsingOrlandoCh : IClassFixture<OrlandoEngineConfigCh>
    {
        private readonly OrlandoEngineConfigCh _config;

        public WhenUsingOrlandoCh(OrlandoEngineConfigCh config)
        {
            _config = config;
        }

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
        public void TableWithDistanceAnnotation_ShouldReturnGoodResultWithDistances()
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
                Assert.Equal(Status.Ok, result);
                Assert.Empty(tableResult.Durations);
                Assert.NotEmpty(tableResult.Distances);
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
