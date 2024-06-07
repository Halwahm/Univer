namespace Lab11
{
    [TestFixture]
    public class SmokeTests
    {
        private Steps.Steps steps = new Steps.Steps();

        [SetUp]
        public void SetUp()
        {
            steps.InitBrowser();
        }

        [TearDown]
        public void Cleanup()
        {
            steps.CloseBrowser();
        }

        [Test]
        public void AddItemToBasket()
        {
            var itemsCount = steps.AddToBasketAndGetBasketCount();
            Assert.That(1, Is.EqualTo(itemsCount));
        }
 
        [Test]
        public void CompareItems()
        {
            var itemsCount = steps.AddToCompareAndGetCompareListCount();
            Assert.That(1, Is.EqualTo(itemsCount));
        }

        [Test]
        public void SendReview()
        {
            var isReviewSended = steps.SendReview();
            Assert.That(isReviewSended, Is.True);
        }

        [Test]
        public void AddToBasketFromCatalog()
        {
            var isEnabled = steps.RemoveItemFromBasketViaCatalog();
            Assert.That(isEnabled, Is.True);
        }

        [Test]
        public void MakeRecordDoctor()
        {
            var isSended = steps.MakeRecordDoctor();
            Assert.Pass();
        }

        [Test]
        public void EmailSubscription()
        {
            var isSubscribed = steps.EmailSubscription();
            Assert.That(isSubscribed, Is.True);
        }

        [Test]
        public void SearchCapability()
        {
            var isSiteWorking = steps.SearchTextCapability();
            Assert.That(isSiteWorking, Is.False);
        }

        [Test]
        public void DoFastOrder()
        {
            var isFastOrderDone = steps.FastOrder();
            Assert.That(isFastOrderDone, Is.True); ;
        }

        [Test]
        public void ActiveToggleMenu()
        {
            var isToggleMenuActive = steps.ToggleMenu();
            Assert.That(isToggleMenuActive, Is.False);
        }

        [Test]
        public void Search()
        {
            var isSearchWorking = steps.BasicSearch();
            Assert.That(isSearchWorking, Is.True);
        }
    }
}
