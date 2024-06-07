using OpenQA.Selenium;
using OpenQA.Selenium.Edge;
using System.Text;

namespace Lab11.Driver
{
    public class DriverInstance
    {
        private static IWebDriver driver;

        private DriverInstance() { }

        public static IWebDriver GetInstance()
        {
            string driverPath = @"C:\Users\halal\.nuget\packages\selenium.webdriver.msedgedriver\123.0.2420.65\driver\win64\msedgedriver.exe";
            EdgeOptions edgeOptions = new EdgeOptions();
            edgeOptions.BinaryLocation = @"C:\Program Files (x86)\Microsoft\Edge\Application\124.0.2478.51\msedge.exe";
            driver = new EdgeDriver(driverPath, edgeOptions);
            return driver;
        }

        public static void CloseBrowser()
        {
            driver.Quit();
            driver = null;
        }
    }
}
