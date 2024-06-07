using System.Text;
using OpenQA.Selenium;
using OpenQA.Selenium.Edge;

namespace SeleniumTests
{
    public class Tests
    {

        private IWebDriver driver;
        private StringBuilder verificationErrors;
        private readonly string _baseURL = "https://wdl.by/";
        private HomePage hp;

        [SetUp]
        public void Setup()
        {
            string driverPath = @"C:\Users\halal\.nuget\packages\selenium.webdriver.msedgedriver\123.0.2420.65\driver\win64\msedgedriver.exe";

            EdgeOptions edgeOptions = new EdgeOptions();
            edgeOptions.BinaryLocation = @"C:\Program Files (x86)\Microsoft\Edge\Application\124.0.2478.51\msedge.exe";

            driver = new EdgeDriver(driverPath, edgeOptions);
            verificationErrors = new StringBuilder();
            hp = new HomePage(driver);
            Thread.Sleep(1000);
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
        public void TestCompareItems()
        {
            hp.GoToUrl(_baseURL);
            Assert.That(hp.GetPageTitle, Is.EqualTo("Оптика WDL: магазины оптики в Минске и Гомеле (очки для зрения, оправы, солнцезащитные очки, контактные линзы)"));

            hp.GetElementByClass("bottom-menu__ankor").Click();
            Assert.That(hp.GetPageTitle, Is.EqualTo("Каталог оптики WDL: оправы для очков, солнцезащитные очки, контактные линзы и аксессуары"));
            hp.GetElementByClass("js-cookie__dis").Click();

            hp.GetElementsByClass("product-item")[0].Click();
            hp.GetElementByClass("js-add-compare").Click();

            hp.GoToUrl("https://wdl.by/catalog/");
            hp.GetElementsByClass("product-item")[1].Click();
            hp.GetElementByClass("js-add-compare").Click();
            Thread.Sleep(1000);
            hp.GoToUrl("https://wdl.by/compare/");
            Assert.That(hp.GetElementsByClass("swiper-slide"), Has.Count.EqualTo(2));
        }

        [Test]
        public void TestAddItemToBasket()
        {
            hp.GoToUrl(_baseURL);
            Assert.That(hp.GetPageTitle, Is.EqualTo("Оптика WDL: магазины оптики в Минске и Гомеле (очки для зрения, оправы, солнцезащитные очки, контактные линзы)"));

            hp.GetElementByClass("bottom-menu__ankor").Click();
            //Assert.That(hp.GetPageTitle, Is.EqualTo("Каталог оптики WDL: оправы для очков, солнцезащитные очки, контактные линзы и аксессуары"));
            hp.GetElementByClass("js-cookie__dis").Click();
            hp.GetElementsByClass("product-item")[0].Click();
            //Assert.That(hp.GetPageTitle, Is.EqualTo("Солнцезащитные очки NOISES 2002 купить в Минске в салонах WDL Оптика"));

            hp.GetElementByClass("js-add-to-basket-detail").Click();
            Thread.Sleep(1000);
            hp.GoToUrl("https://wdl.by/basket/");
            Assert.That(hp.GetElementsByClass("cart-item"), Has.Count.EqualTo(1));
        }
    }
}