#include "Math/numeric_cast.h"
#include "Core/testing/testing-prototype.h"


#include <typeinfo>
#include <iostream>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>


namespace mpl = boost::mpl;


struct print_typename {
    template <typename T>
    void operator()(T &t) {
        std::cout << typeid(T).name() << "\n";
    }
};




typedef boost::mpl::vector< char, int > types;

int main(int argc, char *argv[])
{

    mpl::for_each< types >( print_typename() );
    return 0;
}
