package route

import "strings"

func Encrypt(input string, rows int, cols int) string {
	grid := make([][]rune, rows)
	for i := range grid {
		grid[i] = make([]rune, cols)
	}

	x, y := 0, 0
	dir := 1
	for _, char := range input {
		grid[x][y] = char
		y += dir
		if y < 0 || y >= cols {
			dir = -dir
			y += dir
			x++
		}
	}

	var output strings.Builder
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if grid[i][j] != 0 {
				output.WriteRune(grid[i][j])
			}
		}
	}
	return output.String()
}

func Decrypt(input string, rows int, cols int) string {
	grid := make([][]rune, rows)
	for i := range grid {
		grid[i] = make([]rune, cols)
	}

	for i := range grid {
		for j := range grid[i] {
			grid[i][j] = ' '
		}
	}

	pos := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if pos < len(input) {
				grid[i][j] = rune(input[pos])
				pos++
			}
		}
	}

	var output strings.Builder
	x, y := 0, 0
	dir := 1
	for i := 0; i < rows*cols; i++ {
		output.WriteRune(grid[x][y])
		y += dir
		if y < 0 || y >= cols {
			dir = -dir
			y += dir
			x++
		}
	}
	return output.String()
}
