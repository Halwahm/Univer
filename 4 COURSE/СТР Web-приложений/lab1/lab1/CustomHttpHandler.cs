public class CustomHttpHandler
{
    private readonly RequestDelegate _next;

    public CustomHttpHandler(RequestDelegate next)
    {
        _next = next;
    }

    public async Task InvokeAsync(HttpContext context)
    {
        await context.Session.LoadAsync(); // Загружаем данные сессии

        if (!context.Session.Keys.Contains("Result"))
        {
            context.Session.SetInt32("Result", 0);
        }

        if (!context.Session.Keys.Contains("Stack"))
        {
            context.Session.Set("Stack", System.Text.Json.JsonSerializer.SerializeToUtf8Bytes(new Stack<int>()));
        }

        var request = context.Request;

        if (request.Path.StartsWithSegments("/han"))
        {
            switch (request.Method)
            {
                case "GET":
                    await HandleGetRequest(context);
                    break;
                case "POST":
                    await HandlePostRequest(context);
                    break;
                case "PUT":
                    await HandlePutRequest(context);
                    break;
                case "DELETE":
                    await HandleDeleteRequest(context);
                    break;
                default:
                    context.Response.StatusCode = 405;
                    break;
            }
        }
        else
        {
            if (_next != null)
            {
                await _next(context);
            }
        }
    }

    private async Task HandleGetRequest(HttpContext context)
    {
        int? result = context.Session.GetInt32("Result");
        context.Response.ContentType = "application/json";
        await context.Response.WriteAsync($"{{ \"result\": {result} }}");
    }

    private async Task HandlePostRequest(HttpContext context)
    {
        if (int.TryParse(context.Request.Query["RESULT"], out int newResult))
        {
            context.Session.SetInt32("Result", newResult);
            await context.Response.WriteAsync($"RESULT изменен на: {newResult}");
        }
        else
        {
            context.Response.StatusCode = 400;
            await context.Response.WriteAsync("Некорректное значение RESULT.");
        }
    }

    private async Task HandlePutRequest(HttpContext context)
    {
        if (int.TryParse(context.Request.Query["ADD"], out int addValue))
        {
            Stack<int> stack = GetStackFromSession(context);
            stack.Push(addValue);
            SetStackToSession(context, stack);
            await context.Response.WriteAsync($"Значение {addValue} добавлено в стек.");
        }
        else
        {
            context.Response.StatusCode = 400;
            await context.Response.WriteAsync("Некорректное значение ADD.");
        }
    }

    private async Task HandleDeleteRequest(HttpContext context)
    {
        Stack<int> stack = GetStackFromSession(context);

        if (stack.Count > 0)
        {
            int popValue = stack.Pop();
            int? result = context.Session.GetInt32("Result");
            result += popValue;
            context.Session.SetInt32("Result", result.Value);
            SetStackToSession(context, stack);
            await context.Response.WriteAsync($"Значение {popValue} удалено из стека. RESULT = {result}");
        }
        else
        {
            context.Response.StatusCode = 400;
            await context.Response.WriteAsync("Стек пуст.");
        }
    }

    private Stack<int> GetStackFromSession(HttpContext context)
    {
        byte[] stackBytes = context.Session.Get("Stack");
        return System.Text.Json.JsonSerializer.Deserialize<Stack<int>>(stackBytes);
    }

    private void SetStackToSession(HttpContext context, Stack<int> stack)
    {
        context.Session.Set("Stack", System.Text.Json.JsonSerializer.SerializeToUtf8Bytes(stack));
    }
}
