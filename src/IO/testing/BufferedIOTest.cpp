#include <vector>
#include <cmath>

#include "IO/BufferedIO.h"


int main(void) {

    // Subfolders test("test");
    // test.write_file_once("prova/1/2/3/4/prova.txt", 123);

    detail::Buffer<float> v;
    v << 1.2 << 3.4 << 4.5 << 6 << 7.8 << 10 << std::endl;
    std::cout << " --> " << v << '\n';

    {    
        folded_ofstream<char> ofst("1/2/3/4/out.txt");
        ofst << 1.2 << " abs" << std::flush ;
        ofst.close();
    }
    {
        folded_ofstream<float> ofst("1/2/3/4/out2.txt");
        ofst << 1.2 << NAN << std::flush ;
        ofst.close();
    }   

    return 0;
}