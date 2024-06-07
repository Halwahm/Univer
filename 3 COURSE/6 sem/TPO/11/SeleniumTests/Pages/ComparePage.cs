using OpenQA.Selenium;
using SeleniumExtras.PageObjects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab11.Pages
{
    public class ComparePage
    {
        private const string BASE_URL = "https://wdl.by/compare/";

        [FindsBy(How = How.ClassName, Using = "swiper-slide-active")]
        private readonly IList<IWebElement> _compareListItems;

        public IWebDriver _driver;

        public ComparePage(IWebDriver driver)
        {
            Thread.Sleep(2000);
            _driver = driver;
            PageFactory.InitElements(driver, this);
        }

        public void OpenPage()
        {
            _driver.Navigate().GoToUrl(BASE_URL);
        }

        public int GetCompareListItemsCount()
        {
            return _compareListItems.Count;
        }
    }
}
