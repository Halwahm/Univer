using System;
using System.Text;
using NUnit.Framework;
using OpenQA.Selenium;
using OpenQA.Selenium.Edge;
// C:\Users\user\.nuget\packages\nunit.consolerunner\3.16.3\tools

namespace SeleniumTests
{
    public class Tests
    {

        private IWebDriver driver;
        private StringBuilder verificationErrors;
        private string baseURL;

        [SetUp]
        public void Setup()
        {
            string driverPath = @"C:\Users\halal\.nuget\packages\selenium.webdriver.msedgedriver\123.0.2420.65\driver\win64\msedgedriver.exe";

            EdgeOptions edgeOptions = new EdgeOptions();
            edgeOptions.BinaryLocation = @"C:\Program Files (x86)\Microsoft\Edge\Application\124.0.2478.51\msedge.exe";

            driver = new EdgeDriver(driverPath, edgeOptions);
            baseURL = "https://wdl.by/";
            verificationErrors = new StringBuilder();
        }

        [TearDown]
        public void TearDownTest()
        {
            try
            {
                driver.Quit();
            } 
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }

            Assert.That(verificationErrors.ToString(), Is.EqualTo(""));
        }

        [Test]
        public void TestAddItemToBasket()
        {
            driver.Navigate().GoToUrl(baseURL);

            Assert.That(driver.Title, Is.EqualTo("Оптика WDL: магазины оптики в Минске и Гомеле (очки для зрения, оправы, солнцезащитные очки, контактные линзы)"));
            
            driver.FindElement(By.ClassName("bottom-menu__ankor")).Click();

            Assert.That(driver.Title, Is.EqualTo("Каталог оптики WDL: оправы для очков, солнцезащитные очки, контактные линзы и аксессуары"));
            driver.FindElement(By.ClassName("js-cookie__dis")).Click();
            driver.FindElement(By.ClassName("product-item")).Click();

            Assert.That(driver.Title, Is.EqualTo("Купить контактные линзы WDL COLOR MONTHLY FOREST с бесплатной доставкой по Минску и Беларуси в интернет-магазине WDL.BY и салонах оптики WDL"));

            driver.FindElement(By.ClassName("js-add-to-basket-detail")).Click();

            driver.Navigate().GoToUrl("https://wdl.by/basket/");

            Assert.That(driver.FindElements(By.ClassName("cart-item")).Count, Is.EqualTo(1));
        }
    }
}