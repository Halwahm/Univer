using Microsoft.AspNetCore.Http;
using System.Collections.Generic;
using System.Threading.Tasks;

public class CustomHttpHandler
{
    private readonly RequestDelegate _next;
    private static int Result = 0; 
    private static Stack<int> Stack = new Stack<int>();

    public CustomHttpHandler(RequestDelegate next)
    {
        _next = next;
    }

    public async Task InvokeAsync(HttpContext context)
    {
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
        context.Response.ContentType = "application/json";
        await context.Response.WriteAsync($"{{ \"result\": {Result} }}");
    }

    private async Task HandlePostRequest(HttpContext context)
    {
        if (int.TryParse(context.Request.Query["RESULT"], out int newResult))
        {
            Result = newResult;
            await context.Response.WriteAsync($"RESULT изменен на: {Result}");
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
            Stack.Push(addValue);
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
        if (Stack.Count > 0)
        {
            int popValue = Stack.Pop();
            Result += popValue;
            await context.Response.WriteAsync($"Значение {popValue} удалено из стека. RESULT = {Result}");
        }
        else
        {
            context.Response.StatusCode = 400;
            await context.Response.WriteAsync("Стек пуст.");
        }
    }
}
