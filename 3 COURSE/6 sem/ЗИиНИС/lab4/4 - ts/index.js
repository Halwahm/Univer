// Определение размера резервных данных
function calculateRedundancyLength(dataLength) {
    var redundancyLength = Math.floor(Math.log2(dataLength) + 1.99);
    return redundancyLength;
}
// Генерация проверочной матрицы
function generateParityMatrix(dataLength) {
    var redundancyLength = calculateRedundancyLength(dataLength);
    var totalLength = dataLength + redundancyLength;
    var rDouble = redundancyLength - 1;
    var rPow = Math.pow(2, rDouble);
    var matrix = new Array(totalLength).fill(0).map(function () { return new Array(redundancyLength).fill(0); });
    var combinations = new Array(rPow).fill(0).map(function () { return new Array(redundancyLength).fill(0); });
    for (var i = 0; i < rPow; i++) {
        for (var j = 0; j < redundancyLength; j++) {
            combinations[i][j] = 0;
        }
    }
    for (var _i = 0, _a = Array.from({ length: redundancyLength - 2 }, function (_, i) { return i; }); _i < _a.length; _i++) {
        var segmentLength = _a[_i];
        if (segmentLength * redundancyLength > dataLength)
            break;
        for (var _b = 0, _c = Array.from({ length: segmentLength + 2 }, function (_, i) { return i; }); _b < _c.length; _b++) {
            var i = _c[_b];
            combinations[segmentLength * redundancyLength][i] = 1;
        }
        for (var _d = 0, _e = Array.from({ length: redundancyLength - 1 }, function (_, i) { return i + 1; }); _d < _e.length; _d++) {
            var segmentPosition = _e[_d];
            for (var _f = 0, _g = Array.from({ length: redundancyLength - 1 }, function (_, j) { return j; }); _f < _g.length; _f++) {
                var i = _g[_f];
                combinations[segmentLength * redundancyLength + segmentPosition][i + 1] = combinations[segmentLength * redundancyLength + segmentPosition - 1][i];
            }
            combinations[segmentLength * redundancyLength + segmentPosition][0] = combinations[segmentLength * redundancyLength + segmentPosition - 1][redundancyLength - 1];
        }
        if (segmentLength === redundancyLength - 3) {
            for (var _h = 0, _j = Array.from({ length: redundancyLength }, function (_, j) { return j; }); _h < _j.length; _h++) {
                var i = _j[_h];
                combinations[rPow - 1][i] = 1;
            }
        }
    }
    for (var _k = 0, _l = Array.from({ length: dataLength }, function (_, i) { return i; }); _k < _l.length; _k++) {
        var i = _l[_k];
        for (var _m = 0, _o = Array.from({ length: redundancyLength }, function (_, j) { return j; }); _m < _o.length; _m++) {
            var j = _o[_m];
            matrix[i][j] = combinations[i][j];
        }
    }
    for (var _p = 0, _q = Array.from({ length: redundancyLength }, function (_, i) { return i; }); _p < _q.length; _p++) {
        var i = _q[_p];
        matrix[i + dataLength][i] = 1;
    }
    return matrix;
}
// Коррекция ошибок
function correctErrors(data, parityMatrix, dataLength) {
    var redundancyLength = calculateRedundancyLength(dataLength);
    var totalLength = dataLength + redundancyLength;
    var originalParityBits = new Array(redundancyLength).fill(0);
    for (var _i = 0, _a = Array.from({ length: totalLength - dataLength }, function (_, i) { return i; }); _i < _a.length; _i++) {
        var i = _a[_i];
        originalParityBits[i] = data[i + dataLength];
    }
    data = calculateSyndrome(parityMatrix, data, dataLength);
    for (var _b = 0, _c = Array.from({ length: totalLength - dataLength }, function (_, i) { return i; }); _b < _c.length; _b++) {
        var i = _c[_b];
        if (originalParityBits[i] === data[i + dataLength]) {
            data[i + dataLength] = 0;
            if (Array.from({ length: totalLength - dataLength }, function (_, k) { return k; }).filter(function (k) { return originalParityBits[k] === data[k + dataLength]; }).length === redundancyLength) {
                for (var _d = 0, _e = Array.from({ length: totalLength - dataLength }, function (_, k) { return k; }); _d < _e.length; _d++) {
                    var k = _e[_d];
                    data[k + dataLength] = originalParityBits[k];
                }
                return data;
            }
        }
        else {
            data[i + dataLength] = 1;
        }
    }
    for (var _f = 0, _g = Array.from({ length: totalLength }, function (_, i) { return i; }); _f < _g.length; _f++) {
        var i = _g[_f];
        var count = 0;
        for (var _h = 0, _j = Array.from({ length: redundancyLength }, function (_, j) { return j; }); _h < _j.length; _h++) {
            var j = _j[_h];
            if (parityMatrix[i][j] === data[j + dataLength]) {
                count++;
            }
        }
        if (count === redundancyLength) {
            data[i] = (data[i] + 1) % 2;
        }
    }
    data = calculateSyndrome(parityMatrix, data, dataLength);
    return data;
}
// Расчет синдрома
function calculateSyndrome(parityMatrix, data, dataLength) {
    var redundancyLength = calculateRedundancyLength(dataLength);
    var totalLength = dataLength + redundancyLength;
    var syndrome = new Array(redundancyLength).fill(0);
    for (var _i = 0, _a = Array.from({ length: redundancyLength }, function (_, i) { return i; }); _i < _a.length; _i++) {
        var i = _a[_i];
        var l = 0;
        for (var _b = 0, _c = Array.from({ length: dataLength }, function (_, j) { return j; }); _b < _c.length; _b++) {
            var j = _c[_b];
            if (parityMatrix[j][i] === 1 && data[j] === 1) {
                l++;
            }
            else {
                syndrome[i] = 0;
            }
        }
        if (l % 2 === 1) {
            syndrome[i] = 1;
        }
        else {
            syndrome[i] = 0;
        }
    }
    for (var _d = 0, _e = Array.from({ length: redundancyLength }, function (_, i) { return i; }); _d < _e.length; _d++) {
        var i = _e[_d];
        data[i + dataLength] = syndrome[i];
    }
    return data;
}
// Преобразование строки в массив
function stringToArray(binaryString, dataLength) {
    var redundancyLength = calculateRedundancyLength(dataLength);
    var array = new Array(binaryString.length + redundancyLength).fill(0);
    for (var _i = 0, _a = Array.from({ length: binaryString.length }, function (_, i) { return i; }); _i < _a.length; _i++) {
        var i = _a[_i];
        if (binaryString[i] === '1') {
            array[i] = 1;
        }
        else {
            array[i] = 0;
        }
    }
    return array;
}
// Вывод двумерного массива (матрицы)
function outputArray(array, dataLength) {
    var totalLength = calculateRedundancyLength(dataLength) + dataLength;
    for (var _i = 0, array_1 = array; _i < array_1.length; _i++) {
        var row = array_1[_i];
        for (var _a = 0, row_1 = row; _a < row_1.length; _a++) {
            var element = row_1[_a];
            process.stdout.write(element.toString());
        }
        process.stdout.write("|"); // Разделитель между строками
        console.log(); // Переход на новую строку
    }
    console.log(); // Дополнительный переход на новую строку для красоты
}
// Основная логика программы
function main() {
    var input = "010101"; // Пример входных данных
    var dataLength = input.length;
    var binaryInput = input;
    console.log("Ваша строка в бинарном виде: " + binaryInput);
    var parityMatrix = generateParityMatrix(dataLength);
    console.log("\nПроверочная матрица:");
    outputArray(parityMatrix, dataLength);
    var data = stringToArray(binaryInput, dataLength);
    console.log("\nВходной массив:");
    outputArray(data, dataLength);
    console.log("\nМассив с ошибкой:");
    // Предположим, что в данных есть ошибка, и попробуем ее исправить
    data[3] = (data[3] + 1) % 2;
    outputArray(data, dataLength);
    console.log("\nМассив с вектором ошибки:");
    var correctedData = correctErrors(data, parityMatrix, dataLength);
    outputArray(correctedData, dataLength);
}
// Вызов основной логики программы
main();
