
#include <vector>
#include "Core/CommaInitializer.h"
#include "Core/streams_interaction.h"
#include "Core/Options.h"

#include "testing-prototype.h"





int main(int argc, char *argv[])
{

    float f = 0;
    std::vector<float> vv;

    std::string str = "default";

    vv << (float)555,23,68;

    Options opt;

    opt.AddOptions()
            ("effe", &f, "")
            ("vv",&vv,"test vector")
            ("string",&str,"test string")
            ;

    opt.Parse(argc,argv);


    std::cout << "f = " << f << "\n";
    std::cout << "vv = " << vv << "\n";
    std::cout << "str = " << str << "\n";

    return 0;
}


