#ifndef CORE_INITIALIZERS_H
#define CORE_INITIALIZERS_H

#include <stddef.h> // size_t //
#include <vector>


////////////////////////////////////////////////////////////////////////////////
//  Comma Init  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Comma Initializer template ...
// ContentT should provide operator[] and resize() methods.
// TODO: Waiting for Static interface mpl check

template < typename ContainerT, typename ContentT >
struct CommaInitializer
{
    typedef ContentT&(ContainerT::* OpType)(const size_t);

    inline explicit CommaInitializer(ContainerT *container,
                                     ContentT s,
                                     OpType op = &ContainerT::operator() )
        : container(container),
          operation(op)
    {
        this->index = 0;
        container->resize(1);
        (container->*operation)(0) = s;
    }

    inline CommaInitializer & operator, (ContentT s) {
        this->index++;
        container->resize(index + 1);
        (container->*operation)(this->index) = s;
        return *this;
    }

    ContainerT *container;
    OpType      operation;
    unsigned int index;
};



// Comma Initializer template for fixed array...
// ContentT should provide operator[] method.
// TODO: Waiting for Static interface mpl check

template < typename ContainerT, typename ContentT >
struct CommaInitializerFixed
{
    typedef ContentT&(ContainerT::* OpType)(const size_t);

    inline explicit CommaInitializerFixed(ContainerT *container,
                                          ContentT s,
                                          OpType op = &ContainerT::operator[] )
        : container(container),
          operation(op)
    {
        this->index = 0;
        (container->*operation)(0) = s;
    }

    inline CommaInitializerFixed & operator, (ContentT s) {
        this->index++;
        (container->*operation)(this->index) = s;
        return *this;
    }

    ContainerT *container;
    OpType      operation;
    unsigned int index;
};


////////////////////////////////////////////////////////////////////////////////
//  COMMA INIT FOR STD CONTAINERS  /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace std {
template < typename _T >
inline CommaInitializer< std::vector<_T>, _T > operator << (std::vector<_T> &cnt, _T scalar ) {
    return CommaInitializer< std::vector<_T>, _T>(&cnt,scalar,&std::vector<_T>::operator []);
}
} // std

















#endif // INITIALIZERS_H

