using ASPCMVC6.Controllers;
internal class Program
{
    private static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);

        builder.Services.AddControllersWithViews();
        builder.Services.AddScoped<TMResearchController>();

        var app = builder.Build();

        app.UseHttpsRedirection();
        app.UseStaticFiles();
        app.UseRouting();
        app.UseAuthorization();

        app.MapControllerRoute(
            name: "M01",
            pattern: "{controller=TMResearch}/{action=M01}/1");

        app.MapControllerRoute(
            name: "M01_1",
            pattern: "V3/{controller=TMResearch}/{id}/{M01}/");

        app.MapControllerRoute(
            name: "M02",
            pattern: "V2/{controller=TMResearch}/{action=M02}");

        app.MapControllerRoute(
            name: "M02_1",
            pattern: "V3/{controller=TMResearch}/{id}/{M02}");

        app.MapControllerRoute(
            name: "M03",
            pattern: "V3/{controller=TMResearch}/{id?}/{action=M03}");

        app.MapControllerRoute(
            name: "M03_1",
            pattern: "V3/{controller=TMResearch}/{action=M03}");

        app.MapControllerRoute(
            name: "default",
            pattern: "{controller=TMResearch}/{action=M01}");

        app.MapControllerRoute(
            name: "MXX",
            pattern: "{VX}/{controller=TMResearch}/{id?}/{action=MXX}");

        app.Run();
    }
}