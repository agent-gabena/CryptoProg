#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <stdexcept>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
using namespace CryptoPP;
std::string MD(std::string entry)
{
    Weak::MD5 hash;
    std::string digest;
    StringSource(entry, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest)))); 
    return digest;
}
std::string read_file(std::string way){
    std::ifstream file(way);
    std::string line;
    std::string entry;
    if (file.peek() == EOF){
        throw  std::runtime_error("File is empty.");
    }
    while (std::getline(file, line))
        {
            entry += line;
        }
        file.close();
    return entry;
}
int main() {
    std::string text;
    std::string result;
    try
    {
        text = read_file("test.txt");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    result = MD(text);
    std::cout << result << std::endl;
    return 0; 
}
