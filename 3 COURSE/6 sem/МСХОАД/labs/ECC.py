import time
from hashlib import sha256
from ecdsa import SigningKey, VerifyingKey, SECP256k1

# Генерация ключей
def generate_keys():
    private_key = SigningKey.generate(curve=SECP256k1)
    public_key = private_key.verifying_key
    return private_key, public_key

# Шифрование сообщения
def encrypt(message, private_key):
    # Хеширование сообщения
    hash_message = sha256(message.encode()).digest()
    print("Hash of the message:", hash_message.hex())
    # Подпись хеша сообщения
    signature = private_key.sign(hash_message)
    print("Signature:", signature.hex())
    return signature, hash_message

# Дешифрование сообщения
def decrypt(signature, hash_message, public_key):
    try:
        public_key.verify(signature, hash_message)
        return True
    except:
        return False

# Пример использования
if __name__ == "__main__":
    # Генерация ключей
    private_key, public_key = generate_keys()
    print("Private Key:", private_key.to_string().hex())
    print("Public Key:", public_key.to_string().hex())

    # Сообщение для шифрования
    message = "This is the text to be encrypted and decrypted using ECC."
    print("Original Message:", message)

    # Шифрование
    start_encrypt = time.time()
    signature, hash_message = encrypt(message, private_key)
    end_encrypt = time.time()
    encrypt_time = end_encrypt - start_encrypt
    print("Encryption time:", encrypt_time, "seconds")

    # Дешифрование
    start_decrypt = time.time()
    is_valid = decrypt(signature, hash_message, public_key)
    end_decrypt = time.time()
    decrypt_time = end_decrypt - start_decrypt

    if is_valid:
        print("Signature is valid")
    else:
        print("Signature is invalid")
    print("Decryption time:", decrypt_time, "seconds")
