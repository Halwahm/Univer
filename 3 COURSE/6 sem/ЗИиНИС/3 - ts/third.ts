import * as fs from 'fs';
import { Alphabets, entropyOfAlphabet } from './second';

export function toBase64(path: string): string {
    const text: string = fs.readFileSync(path, 'utf-8');
    return Buffer.from(text, 'utf-8').toString('base64');
}

export function createBase64Doc(): void {
    fs.writeFileSync('base64.txt', Buffer.from(toBase64('latin.txt'), 'base64'));
}

export function createReport(): string {
    const base64ES = entropyOfAlphabet(Alphabets.Base64);
    const latinES = entropyOfAlphabet(Alphabets.Latin);
    const base64EC = Math.log2("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/".length);
    const latinEC = Math.log2("qwertyuiopasdfghjklzxcvbnm".length);

    let report = "";
    report += "Base64 entropy (Shennon): " + base64ES + "\n";
    report += "Latin entropy (Shennon): " + latinES + "\n";
    report += "Base64 entropy (Chartly): " + base64EC + "\n";
    report += "Latin entropy (Chartly): " + latinEC + "\n";
    report += "Redundancy of base64: " + ((base64EC - base64ES) / base64EC * 100) + "%\n";
    report += "Redundancy of latin: " + ((latinEC - latinES) / latinEC * 100) + "%\n";
    return report;
}

export function XOR(buf1: Uint8Array, buf2: Uint8Array): Uint8Array {
    if (buf1.length !== buf2.length) {
        throw new Error("Buffers must be of equal length");
    }

    const ans = new Uint8Array(buf1.length);
    for (let i = 0; i < buf1.length; i++) {
        ans[i] = buf1[i] ^ buf2[i];
    }
    return ans;
}
