#include <typeinfo>
#include <iostream>

#include "Core/MplSequenceCombiner.h"
#include "testing-prototype.h"

#include <boost/mpl/for_each.hpp>

namespace mpl = boost::mpl;

struct A {};
struct B {};
struct C {};
struct D {};
struct E {};
struct F {};
struct G {};
struct H {};
struct I {};

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

int main() {
    BEGIN_TESTING( Mpl Sequence Combiner Test);

    typedef mpl::vector<A,B,C>   seq1;
    typedef mpl::vector<D,E,F>   seq2;
    typedef mpl::vector<G,H,I>   seq3;

    typedef ccs::mpl::combine_view< mpl::vector<seq1,seq2,seq3> > cv;
    ccs::mpl::for_each< cv >( PrintSeq() );

    END_TESTING;
}
