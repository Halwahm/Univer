using System.Text;

namespace SEC_LAB_C_.VizinerCH
{
    public class viziner_encr
    {
        public static string Encrypt(string plaintext, string key)
        {
            StringBuilder ciphertext = new StringBuilder();

            for (int i = 0; i < plaintext.Length; i++)
            {
                char plainChar = plaintext[i];
                char keyChar = key[i % key.Length];
                if (!char.IsLetter(plainChar))
                {
                    ciphertext.Append(plainChar);
                    continue;
                }
                bool isUpper = char.IsUpper(plainChar);
                int offset = isUpper ? 1040 : 1072; // Offset for uppercase and lowercase letters in Russian alphabet
                char encryptedChar = (char)((plainChar - offset + keyChar - 1071) % 32 + offset);
                ciphertext.Append(isUpper ? char.ToUpper(encryptedChar) : char.ToLower(encryptedChar));
            }

            return ciphertext.ToString();
        }

        public static string Decrypt(string ciphertext, string key)
        {
            StringBuilder plaintext = new StringBuilder();


            for (int i = 0; i < ciphertext.Length; i++)
            {
                char cipherChar = ciphertext[i];
                char keyChar = key[i % key.Length];
                if (!char.IsLetter(cipherChar))
                {
                    plaintext.Append(cipherChar);
                    continue;
                }
                char decryptedChar = (char)((cipherChar - keyChar + 32) % 32 + 1071);
                plaintext.Append(decryptedChar);
            }

            return plaintext.ToString();
        }
    }
}
