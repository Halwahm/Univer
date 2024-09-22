package report

import (
	"fmt"

	"github.com/xuri/excelize/v2"
)

func BuildCharHistogram(data string, sheetName string, fileName string) error {
	f := excelize.NewFile()

	f.NewSheet(sheetName)

	if err := f.SetCellValue(sheetName, "A1", "Character"); err != nil {
		return err
	}
	if err := f.SetCellValue(sheetName, "B1", "Count"); err != nil {
		return err
	}

	counts := make(map[rune]int)
	for _, b := range data {
		counts[rune(b)]++
	}

	row := 2
	for char, count := range counts {
		if err := f.SetCellValue(sheetName, fmt.Sprintf("A%d", row), string(char)); err != nil {
			return err
		}
		if err := f.SetCellValue(sheetName, fmt.Sprintf("B%d", row), count); err != nil {
			return err
		}
		row++
	}

	if err := f.AddChart(sheetName, "C1", &excelize.Chart{
		Type: "col",
		Series: []excelize.ChartSeries{
			{
				Name:       sheetName + "!$B$1",
				Categories: sheetName + "!$A$2:$A$" + fmt.Sprint(row),
				Values:     sheetName + "!$B$2:$B$" + fmt.Sprint(row),
			},
		},
		Title: excelize.ChartTitle{
			Name: "Frequency",
		},
		XAxis: excelize.ChartAxis{
			Font: excelize.Font{
				Family: "Calibri",
				Color:  "#000000",
			},
		},
		YAxis: excelize.ChartAxis{
			Font: excelize.Font{
				Family: "Calibri",
				Color:  "#000000",
			},
		},
	}); err != nil {
		return err
	}

	f.SetColWidth(sheetName, "A", "B", 20)

	if err := f.SaveAs(fileName); err != nil {
		return err
	}

	return nil
}
