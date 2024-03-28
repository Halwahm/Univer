import * as fs from 'fs';

export enum Alphabets {
    Latin,
    Cyrillic,
    Binary,
    Base64
}

export function entropyOfAlphabet(Alphabet: Alphabets, errorProbability: number = 0): number {
    let alphabet = "";
    let path = "";
    if (Alphabet === Alphabets.Latin) {
        alphabet = "qwertyuiopasdfghjklzxcvbnm";
        path = "latin.txt";
    } else if (Alphabet === Alphabets.Cyrillic) {
        path = "cyrillic.txt";
        alphabet = "йцукенгшщзхъфывапролджэячсмитьбю";
    } else if (Alphabet === Alphabets.Binary) {
        path = "binary.bin";
        alphabet = "01";
    } else if (Alphabet === Alphabets.Base64) {
        path = "base64.txt";
        alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    }

    const numberOfOccurrences: { [key: string]: number } = {};
    alphabet.split('').forEach(ch => numberOfOccurrences[ch] = 0);

    const text: string = fs.readFileSync(path, 'utf-8').toLowerCase();
    const cleanText = text.split('').filter(ch => alphabet.includes(ch)).join('');
    
    for (const ch of cleanText) {
        numberOfOccurrences[ch]++;
    }

    let answer = 0;
    for (const ch of alphabet) {
        if (numberOfOccurrences[ch] !== 0) {
            const P = numberOfOccurrences[ch] / text.length * (1 - errorProbability);
            answer += P * Math.log2(P);
        }
    }

    return -answer;
}
