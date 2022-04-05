#include <vector>
#include <cmath>
#include <sstream>

#include "IO/BufferedIO.h"


int main(void) {

    // Subfolders test("test");
    // test.write_file_once("prova/1/2/3/4/prova.txt", 123);

    TextBufferIO buffer;

    auto &b = buffer("1/2/3/prova.txt");
    b << "prova prova2" << std::endl;
 
    b.seekp(0);

    std::string prova, prova2;
    b >> prova >> prova2;

    std::cout << prova << std::endl;
    std::cout << prova2 << std::endl;


    return 0;
}