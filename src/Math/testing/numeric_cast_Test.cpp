#include "Math/numeric_cast.h"
#include "Core/testing/testing-prototype.h"


#include <typeinfo>
#include <iostream>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>


#include "Core/MplSequenceCombiner.h"

using namespace ccs;

namespace {
struct PrintTypeId {
    template <class T>
    void operator()(T) const
    { std::cout << typeid(T).name() << "  "; }
};

struct PrintSeq {
    template < typename T >
    void operator()(T) {
        mpl::for_each<T>( PrintTypeId() );
        std::cout << "\n";
    }
};
}



template < typename Pair >
class SequenceCast {
public:
    typedef typename mpl::at<Pair,mpl::int_<0> >::type Source;
    typedef typename mpl::at<Pair,mpl::int_<1> >::type Target;

    static Target cast(Source val) { return numeric_cast<Target>(val); }
};


struct print_numeric_cast {

    template < typename Pair >
    void operator () (Pair) {
        typedef typename mpl::at<Pair,mpl::int_<0> >::type Source;
        typedef typename mpl::at<Pair,mpl::int_<1> >::type Target;
        std::cout << "numeric_cast: " << typeid(Source).name() << " -> " << typeid(Target).name() << "\n";
        print_limits<Source,Target>();
        std::cout << "\n";
    }

    template < typename Source, typename Target >
    bool print_limits() {
        std::string what;
        bool ret = true;

        try {
            ret &= numeric_limits<Target>::max() ==
                    numeric_cast<Target>(numeric_limits<Source>::max());
            what = "Ok";
        }
        catch (std::runtime_error e) {
            ret &= false;
            what = e.what();
        }
        std::cout << "max: " << what << "\n";

        try {
            ret &= numeric_limits<Target>::lowest() ==
                    numeric_cast<Target>(numeric_limits<Source>::lowest());
            what = "Ok";
        }
        catch (std::runtime_error e) {
            ret &= false;
            what = e.what();
        }
        std::cout << "min: " << what << "\n";

        try {
            ret &= ((Target)1) ==
                    numeric_cast<Target>((Source)1);
            what = "Ok";
        }
        catch (std::runtime_error e) {
            ret &= false;
            what = e.what();
        }
        std::cout << "one: " << what << "\n";

        try {
            ret &= numeric_limits<Target>::epsilon() ==
                    numeric_cast<Target>(numeric_limits<Source>::epsilon());
            what = "Ok";
        }
        catch (std::runtime_error e) {
            ret &= false;
            what = e.what();
        }
        std::cout << "eps: " << what << "\n";

        if(numeric_limits<Source>::has_quiet_NaN) {
            try {
                ret &= numeric_limits<Target>::quiet_NaN() ==
                        numeric_cast<Target>(numeric_limits<Source>::quiet_NaN());
                what = "Ok";
            }
            catch (std::runtime_error e) {
                ret &= false;
                what = e.what();
            }
            std::cout << "nan: " << what << "\n";
        }

        return ret;
    }

};



typedef mpl::vector<float, unsigned int> types;
typedef mpl::combine_view< boost::mpl::vector<types, types> > type_pair;


int main(int argc, char *argv[])
{
    BEGIN_TESTING(numeric_cast);

    std::cout << "Using these typeid: ";
    mpl::for_each<types> ( PrintTypeId() );
    std::cout << "\n";

    std::cout << " ---------- TEST ---------------- \n";
    mpl::for_each<type_pair>( print_numeric_cast() );

    // FInIRE

    END_TESTING;
}
