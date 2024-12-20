using System.Data.Services.Common;
using System.Data.Services;
using System.Data.Services.Providers;
using System.Linq;
using System;
using System.ServiceModel.Web;
using System.ServiceModel.Activation;

namespace PWS_Lab6
{
    // ПРИМЕЧАНИЕ. Команду "Переименовать" в меню "Рефакторинг" можно использовать для одновременного изменения имени класса "Service" в коде, SVC-файле и файле конфигурации.
    // ПРИМЕЧАНИЕ. Чтобы запустить клиент проверки WCF для тестирования службы, выберите элементы Service.svc или Service.svc.cs в обозревателе решений и начните отладку.

    //чтобы работало совместимость со средой ASP.NET
    [AspNetCompatibilityRequirements(RequirementsMode = AspNetCompatibilityRequirementsMode.Allowed)]
    public class Service1 : EntityFrameworkDataService<WSHANEntities>
    {
        public static void InitializeService(DataServiceConfiguration config)
        {
            // предосталвяет CRUD операции к таблицам и сущностям
            config.SetEntitySetAccessRule("*", EntitySetRights.All);
            // Устанавливает правила доступа к пользовательским операциям сервиса (например, к методам, добавленным разработчиком).
            config.SetServiceOperationAccessRule("*", ServiceOperationRights.All);
            // Определяет максимальную версию протокола OData, поддерживаемую службой.
            config.DataServiceBehavior.MaxProtocolVersion = DataServiceProtocolVersion.V3;
            // Включает подробные сообщения об ошибках для отладки.
            config.UseVerboseErrors = true;
        }
    }
}
