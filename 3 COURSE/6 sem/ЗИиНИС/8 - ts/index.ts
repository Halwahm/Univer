class Program {
    static createMatrixByString(message: string): string[] {
        const messageMatrix: string[] = [];

        for (let i = 0; i < message.length; i++) {
            messageMatrix[i] = message;
            message = message.substring(1) + message[0];
        }

        return messageMatrix;
    }

    static showMatrix(matrix: string[]): void {
        for (const row of matrix) {
            console.log(row);
        }
        console.log();
    }

    static getLastMatrixColumn(matrix: string[]): string {
        let lastColumn = "";
        for (const row of matrix) {
            lastColumn += row[row.length - 1];
        }
        return lastColumn;
    }

    static getInitMessagePlace(initMessage: string, matrix: string[]): number {
        for (let i = 0; i < matrix.length; i++) {
            if (matrix[i] === initMessage) {
                return i;
            }
        }
        return -1;
    }

    static addMessageToMatrixFromLeft(message: string, matrix: string[]): string[] {
        for (let i = 0; i < matrix.length; i++) {
            matrix[i] = message[i] + matrix[i];
        }
        return matrix;
    }

    static sortMatrix(matrix: string[]): string[] {
        return matrix.sort();
    }

    static createDecodingMatrix(message: string): string[] {
        const messageMatrix: string[] = new Array(message.length);
    
        for (let i = 0; i < message.length; i++) {
            messageMatrix[i] = message;
            message = message.substring(1) + message[0];
    
            for (let j = 0; j < messageMatrix.length; j++) {
                messageMatrix[j] = message[j] + messageMatrix[j];
            }
    
            messageMatrix.sort();
        }
        return messageMatrix;
    }
    

    static main(): void {
        const initialMessageBytes = "сор";
        const bytes = Buffer.from(initialMessageBytes, 'utf-8');
        let str = "";
        for (const byte of bytes) {
            str += byte.toString(2);
        }
        str = "100010000011000011111010001000000";
        console.log("Битовая последовательность 'сор' в ASCII: " + str);
        console.log();

        const initMessages = ["андрей", "халалеенко", "сорокадневный", str];

        for (const initMessage of initMessages) {
            const startTime = process.hrtime.bigint();

            console.log("Сообщение до сжатия: " + initMessage);
            console.log();

            // Encoding
            const W1 = this.createMatrixByString(initMessage);
            console.log("W1");
            this.showMatrix(W1);

            const W2 = this.sortMatrix([...W1]);
            console.log("W2");
            this.showMatrix(W2);

            const encodedMessage = this.getLastMatrixColumn(W2) + (this.getInitMessagePlace(initMessage, W2));
            console.log("Сжатое сообщение: " + this.getLastMatrixColumn(W2));
            console.log("Позиция сообщения в матрице: " + (this.getInitMessagePlace(initMessage, W2) + 1));

            // Decoding
            let W2Dec: string[] = [];
            const gettedMessage = encodedMessage.substring(0, encodedMessage.length - (encodedMessage.length - initMessage.length));
            console.log("Сообщение для распаковки: " + gettedMessage);
            console.log();

            W2Dec = this.createDecodingMatrix(gettedMessage);
            console.log("W2Р");
            this.showMatrix(W2Dec);

            const numberOfInitialMessage = parseInt(encodedMessage.substring(initMessage.length, (encodedMessage.length - initMessage.length)));
            console.log("Сообщение после распаковки:  " + W2Dec[numberOfInitialMessage]);

            const endTime = process.hrtime.bigint();
            console.log("Время выполнения =  " + (endTime - startTime) + " наносекунд");
            console.log("-----------------------------------------------------");
        }
    }
}

Program.main();
