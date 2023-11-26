#include <crypto++/cryptlib.h>

#include <crypto++/base64.h>
#include <crypto++/hex.h>
#include <crypto++/rsa.h>
#include <crypto++/aes.h>
#include <crypto++/files.h>
#include <crypto++/randpool.h>
#include <crypto++/validate.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/seckey.h>
#include<string>

#include <iostream>

int main (int argc, char* argv[])
{
    using namespace CryptoPP;
    
    if (argc != 5) {
        fprintf(stdout, "Usage   : %s <plaintext file> <encrypt file> <key> <encrypt, decrypt>\n", argv[0]);
        fprintf(stdout, "Example : %s my_text_msg.txt my_encrypt_msg.txt 0123456789012345 1,2 \nДлинна ключа должна быть в пределах [16;32] и кратна 8 \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    std::string k = argv[3];
    unsigned char *key = (unsigned char *)k.c_str(); 
    unsigned char *iv =  (unsigned char *)"0123456789012345";              
    size_t key_size = strlen((const char*)key);

    if (*(argv[4]) == '1'){
        CBC_Mode<AES>::Encryption encryptor(key, key_size, iv);
        FileSource(argv[1], true, new StreamTransformationFilter(encryptor, new FileSink(argv[2])));
    }
    if (*(argv[4]) == '2'){
        CBC_Mode<AES>::Decryption decryptor(key, key_size, iv);
        FileSource(argv[1], true, new StreamTransformationFilter(decryptor, new FileSink(argv[2])));
    }

    return 0;
}