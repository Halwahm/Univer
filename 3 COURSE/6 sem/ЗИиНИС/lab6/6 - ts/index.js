"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var operations_1 = require("./operations");
var Program = /** @class */ (function () {
    function Program() {
    }
    Program.Main = function () {
        var Xk = "10010111000110101110000100";
        var Xr = "100101";
        var k = Xk.length;
        var n = 31;
        var r = 5;
        var error;
        var masXk = new Array(k);
        operations_1.default.StringInArray(masXk, Xk);
        var masXr = new Array(Xr.length);
        operations_1.default.StringInArray(masXr, Xr);
        console.log("\t\t\u0412\u0445\u043E\u0434\u043D\u0430\u044F \u0441\u0442\u0440\u043E\u043A\u0430 xk: ".concat(Xk));
        console.log("\t\t\u041F\u043E\u0440\u043E\u0436\u0434\u0430\u044E\u0449\u0438\u0439 \u043F\u043E\u043B\u0438\u043D\u043E\u043C xr \u0432 \u0434\u0432\u043E\u0438\u0447\u043D\u043E\u043C \u0432\u0438\u0434\u0435: ".concat(Xr));
        console.log("\t\t\t k = ".concat(k, ", r = ").concat(r, ", n = ").concat(n));
        console.log("--------------------------------------------------------------------------------");
        var generationMatrix = Array.from({ length: k }, function () { return Array(n).fill(0); });
        operations_1.default.CreateGenerationMatrix(generationMatrix, masXr, k, n);
        console.log("\n\t\t\t\tПорождающая матрица\n");
        operations_1.default.PrintMatrix(generationMatrix, k, n);
        operations_1.default.CreateMatrixCanon(generationMatrix, k, n);
        console.log("--------------------------------------------------------------------------------");
        console.log("\n\t\t\t\tКаноническая матрица\n");
        operations_1.default.PrintMatrix(generationMatrix, k, n);
        var checkMatrix = Array.from({ length: n }, function () { return Array(r).fill(0); });
        operations_1.default.CreateMatrixForCheck(checkMatrix, generationMatrix, k, n);
        console.log("--------------------------------------------------------------------------------");
        console.log("\n\t\t\t\tПроверочная матрица канонической формы\n");
        operations_1.default.PrintMatrix(checkMatrix, n, r);
        // Task 1.2
        var masXn = new Array(n);
        operations_1.default.ShiftR(masXn, masXk, r);
        console.log("--------------------------------------------------------------------------------");
        // Task 2
        console.log("\n\t\t\t\t\tДеление\n");
        operations_1.default.SearchRes(masXn, masXr);
        console.log("Остаток:");
        operations_1.default.PrintArray(masXn);
        console.log("--------------------------------------------------------------------------------");
        console.log("\n\t\t\t\tИтоговая строка\n");
        operations_1.default.ShiftR(masXn, masXk, r);
        operations_1.default.PrintArray(masXn);
        console.log("--------------------------------------------------------------------------------");
        try {
            console.log("Введите место первой ошибки");
            error = 1;
            // error = parseInt(prompt() || "0") - 1;
            if (masXn[error] === 1)
                masXn[error] = 0;
            else
                masXn[error] = 1;
        }
        catch (_a) { }
        console.log("Ошибочная строка:");
        operations_1.default.PrintArray(masXn);
        operations_1.default.SearchingMistake(masXn, masXr, checkMatrix, r);
        console.log("--------------------------------------------------------------------------------");
        try {
            console.log("Место первой ошибки: ");
            error = 2;
            //error = parseInt(prompt() || "0") - 1;
            if (masXn[error] === 1)
                masXn[error] = 0;
            else
                masXn[error] = 1;
            console.log("Место второй ошибки: ");
            error = 3;
            //error = parseInt(prompt() || "0") - 1;
            if (masXn[error] === 1)
                masXn[error] = 0;
            else
                masXn[error] = 1;
        }
        catch (_b) { }
        console.log("Ошибочная строка:");
        operations_1.default.PrintArray(masXn);
        operations_1.default.SearchingMistake(masXn, masXr, checkMatrix, r);
    };
    return Program;
}());
Program.Main();
