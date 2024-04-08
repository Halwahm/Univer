"use strict";
var __spreadArray = (this && this.__spreadArray) || function (to, from, pack) {
    if (pack || arguments.length === 2) for (var i = 0, l = from.length, ar; i < l; i++) {
        if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
};
Object.defineProperty(exports, "__esModule", { value: true });
var Operations = /** @class */ (function () {
    function Operations() {
    }
    Operations.SearchingMistake = function (masXn, masXr, checkMatrix, r) {
        var n = masXn.length;
        var k = n - r;
        var masXnSecond = __spreadArray([], masXn, true);
        console.log("\nДеление");
        this.SearchRes(masXnSecond, masXr);
        console.log("\nОстаток:");
        this.PrintArray(masXnSecond);
        for (var i = 0; i < n; i++) {
            var coincidence = 0;
            for (var j = 0; j < r; j++) {
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
    };
    Operations.SearchRes = function (masXn, masXr) {
        var end = masXn.length - masXr.length + 1;
        for (var i = 0; i < end; i++) {
            if (masXn[i] === 1) {
                this.AdditionWithArraysMod2(masXn, masXr, i);
                this.PrintArray(masXn);
            }
        }
        return masXn;
    };
    Operations.AdditionWithArraysMod2 = function (mas1, mas2, pos) {
        var end = pos + mas2.length;
        for (var i = pos; i < end; i++) {
            mas1[i] = (mas1[i] + mas2[i - pos]) % 2;
        }
        return mas1;
    };
    Operations.ShiftR = function (shiftMas, mas, r) {
        for (var i = 0; i < mas.length; i++) {
            shiftMas[i] = mas[i];
        }
        return shiftMas;
    };
    Operations.StringInArray = function (mas, str) {
        for (var i = 0; i < str.length; i++) {
            mas[i] = parseInt(str[i]);
        }
        return mas;
    };
    Operations.CreateGenerationMatrix = function (generationMatrix, mas, k, n) {
        for (var i = 0; i < n; i++) {
            if (i < mas.length) {
                generationMatrix[0][i] = mas[i];
            }
            else {
                generationMatrix[0][i] = 0;
            }
        }
        for (var i = 1; i < k; i++) {
            for (var j = 0; j < n - 1; j++) {
                generationMatrix[i][j + 1] = generationMatrix[i - 1][j];
            }
            generationMatrix[i][0] = generationMatrix[i - 1][n - 1];
        }
        return generationMatrix;
    };
    Operations.CreateMatrixCanon = function (generationMatrix, k, n) {
        for (var i = 0; i < k; i++) {
            var i2 = i + 1;
            for (var j = i + 1; j < k; j++) {
                if (generationMatrix[i][j] === 1) {
                    var repeat = false;
                    for (; i2 < k; i2++) {
                        if (generationMatrix[i2][j] === 1) {
                            for (var j2 = j - 1; j2 > 0; j2--) {
                                if (generationMatrix[i2][j2] === 1) {
                                    repeat = true;
                                }
                            }
                            if (repeat)
                                continue;
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
    };
    Operations.CreateMatrixForCheck = function (checkMatrix, generationMatrix, k, n) {
        var r = n - k;
        for (var i = 0; i < k; i++) {
            for (var j = 0; j < r; j++) {
                checkMatrix[i][j] = generationMatrix[i][k + j];
            }
        }
        for (var i = k; i < n; i++) {
            for (var j = 0; j < r; j++) {
                if (j === i - k) {
                    checkMatrix[i][j] = 1;
                }
                else {
                    checkMatrix[i][j] = 0;
                }
            }
        }
        return checkMatrix;
    };
    Operations.AddingLinesMatrixMod2 = function (matrix, str1, str2, lengthString) {
        for (var i = 0; i < lengthString; i++) {
            matrix[str1][i] = (matrix[str1][i] + matrix[str2][i]) % 2;
        }
        return matrix;
    };
    Operations.PrintMatrix = function (matrix, k, n) {
        for (var i = 0; i < k; i++) {
            var row = "";
            for (var j = 0; j < n; j++) {
                row += matrix[i][j];
            }
            console.log(row);
        }
    };
    Operations.PrintArray = function (mas) {
        var output = "";
        for (var i = 0; i < mas.length; i++) {
            output += mas[i];
        }
        console.log(output + "\n");
    };
    return Operations;
}());
exports.default = Operations;
