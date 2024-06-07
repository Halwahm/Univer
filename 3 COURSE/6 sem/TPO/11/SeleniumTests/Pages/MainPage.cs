using Lab11.Utils;
using OpenQA.Selenium;
using SeleniumExtras.PageObjects;

namespace Lab11.Pages
{
    public class MainPage
    {
        private const string BASE_URL = "https://wdl.by/";

        [FindsBy(How = How.ClassName, Using = "bottom-menu__ankor")]
        private readonly IWebElement _buttonCatalog;

        [FindsBy(How = How.ClassName, Using = "open-popup-link")]
        private readonly IWebElement _linkAppointmentDoctor;

        [FindsBy(How = How.Name, Using = "email")]
        private readonly IWebElement _inputEmail;

        [FindsBy(How = How.XPath, Using = "//*[@id=\"comp_478666d64dac3cbecdb7287f87a871f9\"]/div/div/div/div/form/button")]
        private readonly IWebElement _subscribe;

        [FindsBy(How = How.XPath, Using = "/html/body/header/div[4]/div/div/div/div/div[1]/div[1]")]
        private readonly IWebElement _search;

        [FindsBy(How = How.XPath, Using = "/html/body/header/div[4]/div/div/div/div/div[1]/form/input")]
        private readonly IWebElement _inputSearchText;

        [FindsBy(How = How.ClassName, Using = "product-item")]
        private readonly IList<IWebElement> _searchItems;

        [FindsBy(How = How.ClassName, Using = "js-cookie__dis")]
        private readonly IWebElement _buttonCookie;

        public IWebDriver _driver;

        public MainPage(IWebDriver driver)
        {
            Thread.Sleep(2000);
            _driver = driver;
            PageFactory.InitElements(driver, this);
        }

        public void OpenPage()
        {
            _driver.Navigate().GoToUrl(BASE_URL);
        }

        public void RejectCookie()
        {
            _buttonCookie.Click();
        }

        public void GoToCatalog()
        {
            _buttonCatalog.Click();
        }

        public void GoToAppointmentDoctorPage()
        {
            _linkAppointmentDoctor.Click();
        }

        public void FillEmail()
        {
            _inputEmail.SendKeys("testtest@gmail.com");
        }

        public void SubscribeEmail()
        {
            _subscribe.Click();
        }

        public void Search()
        {
            _search.Click();
        }

        public void InputSearchText()
        {
            _inputSearchText.SendKeys(RandomGenerator.GetRandomString(100));
        }

        public void InputSearchGlassesText()
        {
            _inputSearchText.SendKeys("очки");
        }

        public int GetSearchItemsCount()
        {
            return _searchItems.Count;
        }
    }
}
