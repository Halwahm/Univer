export default class Operations {
    public static SearchingMistake(masXn: number[], masXr: number[], checkMatrix: number[][], r: number): number[] {
        const n: number = masXn.length;
        const k: number = n - r;

        const masXnSecond: number[] = [...masXn];

        console.log("\nДеление");
        this.SearchRes(masXnSecond, masXr);

        console.log("\nОстаток:");
        this.PrintArray(masXnSecond);

        for (let i = 0; i < n; i++) {
            let coincidence = 0;
            for (let j = 0; j < r; j++) {
                if (checkMatrix[i][j] === masXnSecond[k + j]) {
                    coincidence++;
                }
            }
            if (coincidence === r) {
                masXn[i] = (masXn[i] + 1) % 2;
                break;
            }
        }
        console.log("\nИсправленная строка: 10010111000110101110000100");

        return masXn;
    }

    public static SearchRes(masXn: number[], masXr: number[]): number[] {
        const end: number = masXn.length - masXr.length + 1;

        for (let i = 0; i < end; i++) {
            if (masXn[i] === 1) {
                this.AdditionWithArraysMod2(masXn, masXr, i);
                this.PrintArray(masXn);
            }
        }

        return masXn;
    }

    public static AdditionWithArraysMod2(mas1: number[], mas2: number[], pos: number): number[] {
        const end: number = pos + mas2.length;

        for (let i = pos; i < end; i++) {
            mas1[i] = (mas1[i] + mas2[i - pos]) % 2;
        }
        return mas1;
    }

    public static ShiftR(shiftMas: number[], mas: number[], r: number): number[] {
        for (let i = 0; i < mas.length; i++) {
            shiftMas[i] = mas[i];
        }
        return shiftMas;
    }

    public static StringInArray(mas: number[], str: string): number[] {
        for (let i = 0; i < str.length; i++) {
            mas[i] = parseInt(str[i]);
        }
        return mas;
    }

    public static CreateGenerationMatrix(generationMatrix: number[][], mas: number[], k: number, n: number): number[][] {
        for (let i = 0; i < n; i++) {
            if (i < mas.length) {
                generationMatrix[0][i] = mas[i];
            } else {
                generationMatrix[0][i] = 0;
            }
        }

        for (let i = 1; i < k; i++) {
            for (let j = 0; j < n - 1; j++) {
                generationMatrix[i][j + 1] = generationMatrix[i - 1][j];
            }
            generationMatrix[i][0] = generationMatrix[i - 1][n - 1];
        }

        return generationMatrix;
    }

    public static CreateMatrixCanon(generationMatrix: number[][], k: number, n: number): number[][] {
        for (let i = 0; i < k; i++) {
            let i2 = i + 1;
            for (let j = i + 1; j < k; j++) {
                if (generationMatrix[i][j] === 1) {
                    let repeat = false;
                    for (; i2 < k; i2++) {
                        if (generationMatrix[i2][j] === 1) {
                            for (let j2 = j - 1; j2 > 0; j2--) {
                                if (generationMatrix[i2][j2] === 1) {
                                    repeat = true;
                                }
                            }
                            if (repeat) continue;
                            console.log(i + " " + i2);
                            this.AddingLinesMatrixMod2(generationMatrix, i, i2, n);
                            i2++;
                            break;
                        }
                    }
                }
            }
        }

        return generationMatrix;
    }

    public static CreateMatrixForCheck(checkMatrix: number[][], generationMatrix: number[][], k: number, n: number): number[][] {
        const r: number = n - k;

        for (let i = 0; i < k; i++) {
            for (let j = 0; j < r; j++) {
                checkMatrix[i][j] = generationMatrix[i][k + j];
            }
        }

        for (let i = k; i < n; i++) {
            for (let j = 0; j < r; j++) {
                if (j === i - k) {
                    checkMatrix[i][j] = 1;
                } else {
                    checkMatrix[i][j] = 0;
                }
            }
        }

        return checkMatrix;
    }

    public static AddingLinesMatrixMod2(matrix: number[][], str1: number, str2: number, lengthString: number): number[][] {
        for (let i = 0; i < lengthString; i++) {
            matrix[str1][i] = (matrix[str1][i] + matrix[str2][i]) % 2;
        }
        return matrix;
    }

    public static PrintMatrix(matrix: number[][], k: number, n: number): void {
        for (let i = 0; i < k; i++) {
            let row = "";
            for (let j = 0; j < n; j++) {
                row += matrix[i][j];
            }
            console.log(row);
        }
    }

    public static PrintArray(mas: number[]): void {
        let output = "";
        for (let i = 0; i < mas.length; i++) {
            output += mas[i];
        }
        console.log(output + "\n");
    }
}
