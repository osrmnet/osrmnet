﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using osrmnet;
using Xunit;

namespace osrm.net.test
{
    public class OrlandoEngineConfig : IDisposable
    {
        public EngineConfig EngineConfig { get; }

        public OrlandoEngineConfig()
        {
            // Locating TestData folder

            // This is kinda hacky but tryign to find where the current executing assembly
            // for 3 different kind of test runner (xunit console in appveyor, resharper, visual studio, and whatever
            // in the future), this seems to satisfy all of them for now.
            var codeBaseUrl = new Uri(Assembly.GetExecutingAssembly().CodeBase);
            var codeBasePath = Uri.UnescapeDataString(codeBaseUrl.AbsolutePath);
            var currentAssemblyDir = Path.GetDirectoryName(codeBasePath) ?? string.Empty;

            // Compute TestData folder relative to currentAssemblyDir
            var index = currentAssemblyDir.IndexOf("osrm.net.test", StringComparison.Ordinal);
            // Grab everything from the beginning up to osrm.net.test (index + strelen(osrm.net.test))
            var testDataPath = System.Environment.CurrentDirectory.Substring(0, index + 13);
            testDataPath = Path.Combine(testDataPath, "TestData", "Orlando.osrm");
            EngineConfig = new EngineConfig()
            {
                StorageConfig = testDataPath,
                UseSharedMemory = false
            };
        }
        public void Dispose()
        {
            EngineConfig.Dispose();
        }
    }
    public class InvalidEngineConfig : IDisposable
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
    public class When_UsingOrlandoDataFile : IClassFixture<OrlandoEngineConfig>
    {
        private readonly OrlandoEngineConfig _orlandoEngineConfig;

        public When_UsingOrlandoDataFile(OrlandoEngineConfig orlandoEngineConfig)
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
        public void RoutingWithInvalidCoordinate_ShouldReturnStatusError()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
            {
                IEnumerable<RouteResult> routeResults;
                // No coordinate specified
                var result = sut.Route(new RouteParameters(), out routeResults);
                Assert.Equal(result, Status.Error);
            }
        }

        [Fact]
        public void RoutingWithValidStartEndCoordinate_ShouldReturnStatusOk()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
            {
                IEnumerable<RouteResult> routeResults;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                }, out routeResults);
                Assert.Equal(result, Status.Ok);
            }
        }

        [Fact]public void RoutingWithAnnotationTrue_ShouldReturnStatusOkWithValidAnnotations()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
            {
                IEnumerable<RouteResult> routeResults;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Annotations = true,
                }, out routeResults);

                var annotations = routeResults.SelectMany(x => x.Legs).Select(y => y.Annotation).Where(x => x != null);
                var enumerable = annotations as IList<Annotation> ?? annotations.ToList();
                var distances = enumerable.SelectMany(x => x.Distance);
                var nodes = enumerable.SelectMany(x => x.Nodes);

                Assert.Equal(result, Status.Ok);
                Assert.NotEmpty(distances);
                Assert.NotEmpty(nodes);
            }
        }

        [Fact]
        public void RoutingWithAnnotationFalse_ShouldReturnStatusOkWithEmptyAnnotations()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
            {
                IEnumerable<RouteResult> routeResults;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Annotations = true,
                }, out routeResults);

                var annotations = routeResults.SelectMany(x => x.Legs).Select(y => y.Annotation).Where(x => x != null);

                Assert.Equal(result, Status.Ok);
                Assert.NotEmpty(annotations);
            }
        }

        [Fact]
        public void RoutingWithStepsTrue_ShouldReturnValidSteps()
        {
            using (Osrm sut = new Osrm(_orlandoEngineConfig.EngineConfig))
            {
                IEnumerable<RouteResult> routeResults;
                var result = sut.Route(new RouteParameters()
                {
                    Coordinates = new List<Coordinate>()
                    {
                        new Coordinate(28.479065, -81.463945),
                        new Coordinate(28.598181, -81.207633)
                    },
                    Steps = true,
                }, out routeResults);

                var steps = routeResults.SelectMany(x => x.Legs).Select(x => x.Steps);
                Assert.NotEmpty(steps);
            }
        }
    }
    public class When_UsingInvalidEngineConfig : IClassFixture<InvalidEngineConfig>
    {
        private readonly InvalidEngineConfig _invalidEngine;

        public When_UsingInvalidEngineConfig(InvalidEngineConfig invalidEngine)
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