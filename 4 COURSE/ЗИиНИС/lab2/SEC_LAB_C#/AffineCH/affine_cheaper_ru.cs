namespace SEC_LAB_C_.AffineCH
{
    public class affine_cheaper_ru
    {
        public static string AFFINE_ENCRYPTED(string input_msg, int key_a, int key_b)
        {
            string outputencr_msg = "";
            foreach (char c in input_msg)
            {
                if (char.IsLetter(c))
                {
                    int shiftedChar = (key_a * (char.ToLower(c) - 1071) + key_b) % 33 + 1071;
                    outputencr_msg += char.IsUpper(c) ? char.ToUpper((char)shiftedChar) : (char)shiftedChar;
                }
                else
                {
                    outputencr_msg += c;
                }
            }
            return outputencr_msg;
        }

        public static string AFFINE_DECRYPTED(string inputencr_msg, int key_a, int key_b)
        {
            string outputdecr_msg = "";
            int aInv = 0;

            for (int i = 1; i < 33; i++)
            {
                if (key_a * i % 33 == 1)
                {
                    aInv = i;
                    break;
                }
            }
            foreach (char c in inputencr_msg)
            {
                if (char.IsLetter(c))
                {
                    int shiftedChar = aInv * (char.ToLower(c) - 1071 - key_b + 33) % 33 + 1071;
                    outputdecr_msg += char.IsUpper(c) ? char.ToUpper((char)shiftedChar) : (char)shiftedChar;
                }
                else
                {
                    outputdecr_msg += c;
                }
            }

            return outputdecr_msg;
        }

    }

}
