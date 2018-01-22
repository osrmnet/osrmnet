using Osrmnet.RouteService;
using Xunit;

namespace osrm.net.test.Common
{
    public static class OsrmTestAssert
    {
        public static void AssertValidRoute(RouteResult routeResult)
        {
            Assert.Equal("Ok", routeResult.Code);
            Assert.NotEmpty(routeResult.Routes);
            Assert.NotEmpty(routeResult.Waypoints);
        }
    }
}