using System.Security.Cryptography;
using System.Text;

class RSACSPSample
{

    static void Main()
    {
        try
        {
            UnicodeEncoding ByteConverter = new UnicodeEncoding();

            byte[] dataToEncrypt = ByteConverter.GetBytes("Andry Halaleenko");
            byte[] encryptedData;
            byte[] decryptedData;

            using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
            {
                encryptedData = RSAEncrypt(dataToEncrypt, RSA.ExportParameters(false), false);
                decryptedData = RSADecrypt(encryptedData, RSA.ExportParameters(true), false);

                using (var writter = new StreamWriter("file.txt"))
                {
                    writter.WriteLine("RSA");
                    writter.WriteLine("encrypted text: {0}", ByteConverter.GetString(encryptedData));
                    writter.WriteLine("Decrypted text: {0}", ByteConverter.GetString(decryptedData));
                    writter.WriteLine(RSA.ExportParameters(false));
                }

                Console.WriteLine("encrypted text: {0}", ByteConverter.GetString(encryptedData));
                Console.WriteLine("Decrypted text: {0}", ByteConverter.GetString(decryptedData));
            }
            byte[] hashValue = new byte[256];

            using (MD5 md = MD5.Create())
            {
                hashValue = md.ComputeHash(File.ReadAllBytes("C:\\Загрузки\\ConsoleApp2\\ConsoleApp2\\bin\\Debug\\net6.0\\md5.txt"));
                File.WriteAllBytes("C:\\Загрузки\\ConsoleApp2\\ConsoleApp2\\bin\\Debug\\net6.0\\md5.txt", hashValue);

            }

        }
        catch (ArgumentNullException)
        {
            Console.WriteLine("Encryption failed.");
        }
    }

    public static byte[] RSAEncrypt(byte[] DataToEncrypt, RSAParameters RSAKeyInfo, bool DoOAEPPadding)
    {
        try
        {
            byte[] encryptedData;
            using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
            {
                RSA.ImportParameters(RSAKeyInfo);

                encryptedData = RSA.Encrypt(DataToEncrypt, DoOAEPPadding);
            }
            return encryptedData;
        }

        catch (CryptographicException e)
        {
            Console.WriteLine(e.Message);

            return null;
        }
    }

    public static byte[] RSADecrypt(byte[] DataToDecrypt, RSAParameters RSAKeyInfo, bool DoOAEPPadding)
    {
        try
        {
            byte[] decryptedData;
            using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
            {
                RSA.ImportParameters(RSAKeyInfo);
 
                decryptedData = RSA.Decrypt(DataToDecrypt, DoOAEPPadding);
            }
            return decryptedData;
        }

        catch (CryptographicException e)
        {
            Console.WriteLine(e.ToString());

            return null;
        }
    }
}