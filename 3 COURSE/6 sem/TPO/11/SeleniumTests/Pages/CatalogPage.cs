using OpenQA.Selenium;
using SeleniumExtras.PageObjects;
using OpenQA.Selenium.Interactions;
using System;

namespace Lab11.Pages
{
    public class CatalogPage
    {
        private const string BASE_URL = "https://wdl.by/catalog/";

        [FindsBy(How = How.ClassName, Using = "product-item")]
        private readonly IList<IWebElement> _catalogItems;

        [FindsBy(How = How.ClassName, Using = "js-add-to-basket")]
        private readonly IWebElement _buttonAddToBasket;

        [FindsBy(How = How.ClassName, Using = "js-small-basket")]
        private readonly IWebElement _basket;

        [FindsBy(How = How.XPath, Using = "/html/body/header/div[4]/div/div/nav/div[3]/div[1]/a")]
        private readonly IWebElement _recordDoctor;

        [FindsBy(How = How.Name, Using = "FIO")]
        private readonly IWebElement _inputName;

        [FindsBy(How = How.Name, Using = "PHONE")]
        private readonly IWebElement _inputPhone;

        [FindsBy(How = How.Name, Using = "EMAIL")]
        private readonly IWebElement _inputEmail;

        [FindsBy(How = How.ClassName, Using = "cart-buttons")]
        private readonly IWebElement _buttonSendRecord;

        [FindsBy(How = How.XPath, Using = "//*[@id=\"success_popup\"]/button[2]")]
        private readonly IWebElement _buttonCloseSendedReview;

        [FindsBy(How = How.XPath, Using = "/html/body/footer/div/div[2]/div[1]/div[1]/div[2]/div")]
        private readonly IWebElement _toggleMenu;

        [FindsBy(How = How.XPath, Using = "/html/body/footer/div/div[2]/div[1]/div[1]/div[2]/ul")]
        private readonly IWebElement _toggleMenuBar;

        [FindsBy(How = How.ClassName, Using = "js-cookie__dis")]
        private readonly IWebElement _buttonCookie;


        public IWebDriver _driver;

        private Actions action;

        public CatalogPage(IWebDriver driver)
        {
            Thread.Sleep(2000);
            _driver = driver;
            action = new Actions(driver);
            PageFactory.InitElements(driver, this);
        }

        public void OpenPage()
        {
            _driver.Navigate().GoToUrl(BASE_URL);
        }

        public void RejectCookie()
        {
            _buttonCookie?.Click();
        }

        public IWebElement GetCatalogItem(int numberOfItem)
        {
            return _catalogItems[numberOfItem];
        }

        public void GoToCatalogItem(int numberOfItem)
        {
            _catalogItems[numberOfItem].Click();
        }

        public void NavigateToItem(int numberOfItem)
        {
            action.MoveToElement(_catalogItems[numberOfItem]);
            action.Pause(TimeSpan.FromSeconds(3));
            IJavaScriptExecutor js = (IJavaScriptExecutor)_driver;
            js.ExecuteScript("window.scrollBy(0,40);");
            action.Perform();
        }

        public void AddToBasketFromCatalog()
        {
            _buttonAddToBasket.Click();
        }

        public void NavigateToBasket()
        {
            action.MoveToElement(_basket);
            action.Perform();
            action.MoveByOffset(0, 20);
            action.Perform();
        }

        public void RemoveItemFromBasket()
        {
            action.MoveByOffset(30, 50);
            action.Perform();
            action.Click();
            action.Perform();
        }

        public bool IsItemSelected()
        {
            return _buttonAddToBasket.Enabled;
        }

        public void OpenMakeOrderToDoctor()
        {
            _recordDoctor.Click();
        }

        public void FillInRecord()
        {
            _inputName.SendKeys("Тест");
            _inputPhone.SendKeys("+375333333333");
            _inputEmail.SendKeys("testpochta@gmail.com");
        }

        public void SendRecord()
        {
            _buttonSendRecord.Click();
        }

        public bool IsRecordSended()
        {
            return _buttonCloseSendedReview.Displayed;
        }

        public void ClickCaptcha()
        {
            action.MoveToElement(_buttonSendRecord);
            action.Perform();
            action.MoveByOffset(0, -100);
            action.Perform();
            action.Click();
        }

        public void ToggleMenuClick()
        {
            _toggleMenu.Click();
        }

        public bool IsActiveToggleMenu()
        {
            return _toggleMenuBar.Displayed;
        }

    }
}
