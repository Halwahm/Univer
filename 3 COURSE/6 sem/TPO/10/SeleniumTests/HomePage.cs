using OpenQA.Selenium;
using OpenQA.Selenium.Support.UI;
using SeleniumExtras.PageObjects;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeleniumTests
{
    public class HomePage
    {
        private readonly IWebDriver _driver;
        private readonly WebDriverWait _wait;

        public HomePage(IWebDriver driver)
        {
            this._driver = driver;
            _wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
            PageFactory.InitElements(driver, this);
        }

        public void GoToUrl(string url)
        {
            _driver.Navigate().GoToUrl(url);
        }

        public string GetPageTitle()
        {
            return _driver.Title;
        }

        public IWebElement GetElementByClass(string className)
        {
            return _driver.FindElement(By.ClassName(className));
        } 

        public ReadOnlyCollection<IWebElement> GetElementsByClass(string className)
        {
            return _driver.FindElements(By.ClassName(className));
        }
    }
}
