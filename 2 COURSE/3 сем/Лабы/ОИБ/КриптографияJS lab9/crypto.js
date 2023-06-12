//AES-CTR
//SHA-1

async function importKey() {
    return window.crypto.subtle.importKey(
        "jwk", //может быть "jwk" или "raw"
        {   //пример jwk ключа, "raw" должен быть ArrayBuffer
            kty: "oct",
            k: "Y0zt37HgOx-BY7SQjYVmrqhPkO44Ii2Jcb9yydUDPfE",
            alg: "A256GCM",//AES-CTR
            ext: true,
        },
        {   //это варианты алгоритма, которые вы планируете использовать
            name: "AES-GCM",
        },
        false, //является ли ключ извлекаемым (т.е. может быть использован в exportKey)
        ["encrypt", "decrypt"] //может быть "encrypt", "decrypt", "wrapKey", or "unwrapKey"
    )
}

async function generateKey() {
    return window.crypto.subtle.generateKey(
        {
            name: "AES-GCM",
            length: 256, //может быть 128, 192, 256
            hash: "SHA-1", //может быть "SHA-1", "SHA-256", "SHA-384", or "SHA-512"
        },
        true, //является ли ключ извлекаемым (т.е. может быть использован в exportKey)
        ["encrypt", "decrypt"] //может быть "encrypt", "decrypt", "wrapKey", or "unwrapKey"
    )
}





async function encrypt(data, key, iv) {
    return window.crypto.subtle.encrypt(
        {
            name: "AES-GCM",

            //Не используйте повторно векторы инициализации!
            //Всегда генерируйте новый iv при каждом шифровании!
            //Рекомендуется использовать длину 12 байт
            iv: iv,

            //Длина тега (необязательно)
            tagLength: 128, //can be 32, 64, 96, 104, 112, 120 or 128 (default)
        },
        key, //из generateKey или importKey выше
        data //ArrayBuffer данных, которые вы хотите зашифровать
    )
}

async function decrypt(data, key, iv) {
    return window.crypto.subtle.decrypt(
        {
            name: "AES-GCM",
            iv: iv, //Вектор инициализации, который вы использовали для шифрования.
            //additionalData: ArrayBuffer, //Дополнительные данные, которые вы использовали для шифрования (если есть)
            tagLength: 128, //Длина метки, которую вы использовали для шифрования (если есть)
        },
        key, //из generateKey или importKey выше
        data //ArrayBuffer данных
    )
}






async function fun() {
    var keys = await importKey()
    var iv = new Uint8Array([188, 185, 57, 146, 246, 194, 114, 34, 12, 80, 198, 77])
    var enc = new TextEncoder();
    var data = enc.encode("Халалеенко")
    var encryptedData = await encrypt(data, keys, iv)
    //document.write(encryptedData + '<br>');
    var decryptedData = await decrypt(encryptedData, keys, iv)
    //document.write(decryptedData + '<br>');
    var enc = new TextDecoder("utf-8");
    document.write(enc.decode(encryptedData) + '<br>');
    document.write(enc.decode(decryptedData) + '<br>');
}


fun()

