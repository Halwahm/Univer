using Lab11.Pages;
using OpenQA.Selenium;

namespace Lab11.Steps
{
    public class Steps
    {
        public IWebDriver _driver;

        public void InitBrowser()
        {
            _driver = Driver.DriverInstance.GetInstance();
        }

        public void CloseBrowser()
        {
            Driver.DriverInstance.CloseBrowser();
        }

        public int AddToBasketAndGetBasketCount()
        {
            var catalogPage = new Pages.CatalogPage(_driver);
            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            Thread.Sleep(1000);
            catalogPage.GoToCatalogItem(1);

            Thread.Sleep(2000);
            var productPage = new Pages.ProductPage(catalogPage._driver);
            productPage.AddItemToBasket();

            var basketPage = new Pages.BasketPage(productPage._driver);
            return basketPage.GetBasketItemsCount();
        }

        public int AddToCompareAndGetCompareListCount()
        {
            var catalogPage = new Pages.CatalogPage(_driver);
            var productPage = new Pages.ProductPage(catalogPage._driver);
            var comparePage = new Pages.ComparePage(catalogPage._driver);

            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            catalogPage.GoToCatalogItem(0);
            productPage.AddItemToCompareList();

            catalogPage.OpenPage();
            catalogPage.GoToCatalogItem(1);
            productPage.AddItemToCompareList();

            comparePage.OpenPage();
            return comparePage.GetCompareListItemsCount();
        }

        public bool SendReview()
        {
            var catalogPage = new Pages.CatalogPage(_driver);

            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            catalogPage.GoToCatalogItem(0);

            var productPage = new Pages.ProductPage(catalogPage._driver);
            productPage.OpenAddReviewWindow();
            productPage.FillInReview();
            productPage.SendReview();

            return productPage.IsReviewSended();
        }

        public bool RemoveItemFromBasketViaCatalog()
        {
            var catalogPage = new Pages.CatalogPage(_driver);

            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            Thread.Sleep(1000);
            catalogPage.NavigateToItem(14);
            Thread.Sleep(1000);
            catalogPage.AddToBasketFromCatalog();
            Thread.Sleep(1000);
            catalogPage.OpenPage();
            catalogPage.NavigateToBasket();
            Thread.Sleep(1000);
            catalogPage.RemoveItemFromBasket();
            Thread.Sleep(1000);

            catalogPage.NavigateToItem(0);

            return catalogPage.IsItemSelected();
        }

        public bool MakeRecordDoctor()
        {
            var catalogPage = new Pages.CatalogPage(_driver);
            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            Thread.Sleep(1000);
            catalogPage.OpenMakeOrderToDoctor();
            Thread.Sleep(1000);
            catalogPage.FillInRecord();
            Thread.Sleep(1000);
            catalogPage.ClickCaptcha();
            Thread.Sleep(10000);
            catalogPage.SendRecord();
            Thread.Sleep(1000);

            return catalogPage.IsRecordSended();
        }

        public bool EmailSubscription()
        {
            var mainPage = new Pages.MainPage(_driver);
            mainPage.OpenPage();
            mainPage.RejectCookie();
            Thread.Sleep(1000);
            mainPage.FillEmail();
            Thread.Sleep(1000);
            mainPage.SubscribeEmail();
            Thread.Sleep(1000);


            return true;
        }

        public bool SearchTextCapability()
        {
            var mainPage = new Pages.MainPage(_driver);
            mainPage.OpenPage();
            mainPage.RejectCookie();
            Thread.Sleep(1000);
            mainPage.Search();
            Thread.Sleep(1000);
            mainPage.InputSearchText();
            Thread.Sleep(1000);
            mainPage.Search();

            return false;
        }

        public bool FastOrder()
        {
            var catalogPage = new Pages.CatalogPage(_driver);
            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            catalogPage.GoToCatalogItem(0);

            var productPage = new Pages.ProductPage(catalogPage._driver);
            Thread.Sleep(1000);
            productPage.MakeFastOrder();
            Thread.Sleep(1000);

            productPage.FillInFastOrder();
            Thread.Sleep(1000);

            productPage.CommitFastOrder();
            Thread.Sleep(2000);

            return productPage.IsCommitedFastOrder();
            return true;
        }

        public bool ToggleMenu()
        {
            var catalogPage = new Pages.CatalogPage(_driver);
            catalogPage.OpenPage();
            catalogPage.RejectCookie();
            catalogPage.ToggleMenuClick();
            Thread.Sleep(5000);

            return catalogPage.IsActiveToggleMenu();
        }

        public bool BasicSearch()
        {
            var mainPage = new Pages.MainPage(_driver);
            mainPage.OpenPage();
            mainPage.RejectCookie();
            mainPage.InputSearchGlassesText();

            return mainPage.GetSearchItemsCount() > 0;
        }
    }
}
