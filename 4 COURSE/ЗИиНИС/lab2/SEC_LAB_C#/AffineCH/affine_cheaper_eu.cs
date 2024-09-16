namespace SEC_LAB_C_.AffineCH
{
    public class affine_cheaper_eu
    {
        public static string AFFINE_ENCRYPTED(string input_msg, int key_a, int key_b)
        {
            string encrypted_output_msg = "";
            foreach (char c in input_msg)
            {
                if (char.IsLetter(c))
                {
                    int shiftedChar = (key_a * (char.ToLower(c) - 96) + key_b) % 26 + 96;
                    encrypted_output_msg += char.IsUpper(c) ? char.ToUpper((char)shiftedChar) : (char)shiftedChar;
                }
                else
                {
                    encrypted_output_msg += c;
                }
            }
            return encrypted_output_msg;
        }

        public static string AFFINE_DECRYPTED(string input_encrypted_msg, int key_a, int key_b)
        {
            string decrypted_output_msg = "";
            int aInv = 0;

            for (int i = 1; i < 26; i++)
            {
                if (key_a * i % 26 == 1)
                {
                    aInv = i;
                    break;
                }
            }
            foreach (char c in input_encrypted_msg)
            {
                if (char.IsLetter(c))
                {
                    int shiftedChar = aInv * (char.ToLower(c) - 96 - key_b + 26) % 26 + 96;
                    decrypted_output_msg += char.IsUpper(c) ? char.ToUpper((char)shiftedChar) : (char)shiftedChar;
                }
                else
                {
                    decrypted_output_msg += c;
                }
            }

            return decrypted_output_msg;
        }


    }

}
