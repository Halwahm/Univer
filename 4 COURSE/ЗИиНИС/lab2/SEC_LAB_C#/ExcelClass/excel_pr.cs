using Microsoft.VisualBasic;
using System.Collections.Generic;
using System.IO;
using System.IO.Packaging;
using Excel = Microsoft.Office.Interop.Excel;

namespace SEC_LAB_C_.ExcelClass
{
    public class excel_pr
    {

        public static void ExcelPrint1(string filepath_tosave, string filepath_yomainmsg, string header)
        {
            
            Excel.Application excel = new Excel.Application();
            excel.Visible = true;
            Excel.Workbook workbook = excel.Workbooks.Add();
            Excel.Worksheet worksheet = (Excel.Worksheet)workbook.ActiveSheet;

            string fileContent = File.ReadAllText(filepath_yomainmsg);
            char[] chars = new char[] { 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ь', 'ы', 'ъ', 'э', 'ю', 'я' };
            Dictionary<char, int> charCount = new Dictionary<char, int>();


            foreach (char c in chars)
            {
                charCount.Add(c, 0);
            }


            foreach (char c in fileContent)
            {
                if (charCount.ContainsKey(c))
                {
                    charCount[c]++;
                }
            }
            Excel.Chart chart = (Excel.Chart)workbook.Charts.Add();
            chart.ChartType = Excel.XlChartType.xlColumnClustered;
            foreach (KeyValuePair<char, int> pair in charCount)
            {
                worksheet.Cells[1, pair.Key - 'а' + 1] = pair.Key.ToString();
                worksheet.Cells[2, pair.Key - 'а' + 1] = pair.Value;
            }
            Excel.Range chartRange = worksheet.get_Range("A1:Z2");
            chart.SetSourceData(chartRange);

            chart.HasTitle = true;
            chart.ChartTitle.Text = header;

            Excel.Axis xAxis = (Excel.Axis)chart.Axes(Excel.XlAxisType.xlCategory, Excel.XlAxisGroup.xlPrimary);
            xAxis.HasTitle = true;
            xAxis.AxisTitle.Text = "Symbols";

            Excel.Axis yAxis = (Excel.Axis)chart.Axes(Excel.XlAxisType.xlValue, Excel.XlAxisGroup.xlPrimary);
            yAxis.HasTitle = true;
            yAxis.AxisTitle.Text = "Count";
            string saveFilePath = filepath_tosave;
            workbook.SaveAs(saveFilePath);
            workbook.Close();
            excel.Quit();
        }
    }
}
