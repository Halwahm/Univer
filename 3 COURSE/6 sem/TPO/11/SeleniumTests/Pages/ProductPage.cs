using OpenQA.Selenium;
using SeleniumExtras.PageObjects;

namespace Lab11.Pages
{
    public class ProductPage
    {
        [FindsBy(How = How.ClassName, Using = "js-add-to-basket-detail")]
        private readonly IWebElement _buttonAddToBasket;

        [FindsBy(How = How.ClassName, Using = "js-add-compare")]
        private readonly IWebElement _buttonAddToCompare;

        [FindsBy(How = How.XPath, Using = "/html/body/main/div[2]/div/div[4]/div[1]/div/div[4]/div/div[1]/a")]
        private readonly IWebElement _buttonAddReview;

        [FindsBy(How = How.Name, Using = "NAME")]
        private readonly IWebElement _inputName;

        [FindsBy(How = How.Name, Using = "CITY")]
        private readonly IWebElement _inputCity;

        [FindsBy(How = How.Name, Using = "ADVANTAGES")]
        private readonly IWebElement _inputAdvantages;

        [FindsBy(How = How.Name, Using = "LIMITATIONS")]
        private readonly IWebElement _inputLimitations;

        [FindsBy(How = How.Name, Using = "COMMENT")]
        private readonly IWebElement _inputComment;

        [FindsBy(How = How.Name, Using = "PHONE")]
        private readonly IWebElement _inputPhone;

        [FindsBy(How = How.XPath, Using = "//*[@id=\"popup-comment\"]/form/div[6]/div/button")]
        private readonly IWebElement _buttonSendReview;

        [FindsBy(How = How.XPath, Using = "//*[@id=\"success_popup\"]/button[2]")]
        private readonly IWebElement _buttonCloseSendedReview;

        [FindsBy(How = How.XPath, Using = "/html/body/main/div[2]/div/div[4]/div[1]/div/ul/li[2]/a")]
        private readonly IWebElement _buttonReviews;

        //[FindsBy(How = How.XPath, Using = "/html/body/main/div[2]/div/div[2]/div[2]/div/div[5]/div[2]/button[1]")]
        [FindsBy(How = How.ClassName, Using = "js-one-click-order-detail")]
        private readonly IWebElement _buttonFastOrder;

        [FindsBy(How = How.XPath, Using = "//*[@id=\"fast_order\"]/div[3]/button")]
        private readonly IWebElement _buttonCommitFastOrder;

        [FindsBy(How = How.ClassName, Using = "w242")]
        private readonly IWebElement _buttonAgree;

        [FindsBy(How = How.ClassName, Using = "button--blue")]
        private readonly IWebElement _buttonPlaceAnOrder;

        [FindsBy(How = How.XPath, Using = "//*[@id=\"order-ok\"]/button[2]")]
        private readonly IWebElement _buttonCommitedFastOrder;


        public IWebDriver _driver;

        public ProductPage(IWebDriver driver)
        {
            Thread.Sleep(2000);
            _driver = driver;
            PageFactory.InitElements(driver, this);
        }

        public void AddItemToBasket()
        {
            _buttonAddToBasket.Click();
        }

        public void AddItemToCompareList()
        {
            _buttonAddToCompare.Click();
        }

        public void OpenAddReviewWindow()
        {
            _buttonReviews.Click();
            Thread.Sleep(2000);
            _buttonAddReview.Click();
        }

        public void FillInReview()
        {
            _inputName.SendKeys("Ivan");
            _inputCity.SendKeys("Minsk");
            _inputAdvantages.SendKeys("TestTestTest");
            _inputLimitations.SendKeys("TestTestTest");
            _inputComment.SendKeys("TestTestTest");
        }

        public void SendReview()
        {
            _buttonSendReview.Click();
            Thread.Sleep(2000);
        }

        public bool IsReviewSended()
        {
            return _buttonCloseSendedReview.Displayed;
        }

        public void MakeFastOrder()
        {
            _buttonFastOrder.Click();
            Thread.Sleep(5000);
            /*IJavaScriptExecutor executor = (IJavaScriptExecutor)_driver;
            executor.ExecuteScript("document.body.removeChild(document.getElementsByClassName('cube-loader-wrap')[0]);");*/
        }

        public void FillInFastOrder()
        {
            _inputName.SendKeys("Ivan");
            _inputPhone.SendKeys("+375333333333");
        }

        public void CommitFastOrder()
        {
            _buttonCommitFastOrder.Click();
            _buttonAgree.Click();
            _buttonPlaceAnOrder.Click();
            Thread.Sleep(1500);
            /*IJavaScriptExecutor executor = (IJavaScriptExecutor)_driver;
            executor.ExecuteScript("document.body.removeChild(document.getElementsByClassName('cube-loader-wrap')[0]);");*/
        }

        public bool IsCommitedFastOrder()
        {
            return _buttonCommitedFastOrder.Displayed;
        }
    }
}
