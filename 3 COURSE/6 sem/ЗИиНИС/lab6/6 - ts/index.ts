import Operations from './operations';

class Program {
    static Main(): void {
        const Xk: string = "10010111000110101110000100";
        const Xr: string = "100101";
 
        const k: number = Xk.length;
        const n: number = 31;
        const r: number = 5;

        let error: number;

        const masXk: number[] = new Array<number>(k);
        Operations.StringInArray(masXk, Xk);

        const masXr: number[] = new Array<number>(Xr.length);
        Operations.StringInArray(masXr, Xr);

        console.log(`\t\tВходная строка xk: ${Xk}`);
        console.log(`\t\tПорождающий полином xr в двоичном виде: ${Xr}`);
        console.log(`\t\t\t k = ${k}, r = ${r}, n = ${n}`);
        console.log("--------------------------------------------------------------------------------");

        const generationMatrix: number[][] = Array.from({ length: k }, () => Array(n).fill(0));
        Operations.CreateGenerationMatrix(generationMatrix, masXr, k, n);

        console.log("\n\t\t\t\tПорождающая матрица\n");
        Operations.PrintMatrix(generationMatrix, k, n);

        Operations.CreateMatrixCanon(generationMatrix, k, n);
        console.log("--------------------------------------------------------------------------------");

        console.log("\n\t\t\t\tКаноническая матрица\n");
        Operations.PrintMatrix(generationMatrix, k, n);

        const checkMatrix: number[][] = Array.from({ length: n }, () => Array(r).fill(0));
        Operations.CreateMatrixForCheck(checkMatrix, generationMatrix, k, n);
        console.log("--------------------------------------------------------------------------------");

        console.log("\n\t\t\t\tПроверочная матрица канонической формы\n");
        Operations.PrintMatrix(checkMatrix, n, r);

        // Task 1.2

        const masXn: number[] = new Array(n);
        Operations.ShiftR(masXn, masXk, r);

        console.log("--------------------------------------------------------------------------------");

        // Task 2
        console.log("\n\t\t\t\t\tДеление\n");
        Operations.SearchRes(masXn, masXr);

        console.log("Остаток:");
        Operations.PrintArray(masXn);

        console.log("--------------------------------------------------------------------------------");
        console.log("\n\t\t\t\tИтоговая строка\n");
        Operations.ShiftR(masXn, masXk, r);
        Operations.PrintArray(masXn);

        console.log("--------------------------------------------------------------------------------");
        try {
            console.log("Введите место первой ошибки");
            error = parseInt(prompt() || "0") - 1;
            if (masXn[error] === 1) masXn[error] = 0;
            else masXn[error] = 1;
        } catch { }

        console.log("Ошибочная строка:");
        Operations.PrintArray(masXn);

        Operations.SearchingMistake(masXn, masXr, checkMatrix, r);

        console.log("--------------------------------------------------------------------------------");
        try {
            console.log("Место первой ошибки: ");
            error = parseInt(prompt() || "0") - 1;
            if (masXn[error] === 1)
                masXn[error] = 0;
            else masXn[error] = 1;

            console.log("Место второй ошибки: ");
            error = parseInt(prompt() || "0") - 1;
            if (masXn[error] === 1)
                masXn[error] = 0;
            else masXn[error] = 1;
        } catch { }

        console.log("Ошибочная строка:");
        Operations.PrintArray(masXn);

        Operations.SearchingMistake(masXn, masXr, checkMatrix, r);
    }
}

Program.Main();
