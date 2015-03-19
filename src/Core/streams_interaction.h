#ifndef STREAMS_INTERACTION_H
#define STREAMS_INTERACTION_H


#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
//  Vector  ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace std {
template < typename T >
inline ostream &
operator << (ostream &o, const vector<T> &v) {
    typedef typename vector<T>::const_iterator iterator;
    for(iterator it = v.begin(); it < v.end(); ++it) {
        o << *it << " ";
    }
    return o;
}

template < typename T >
inline istream &
operator >> (istream &is, vector<T> &v) {
    T value;
    v.clear();
    while( !(is >> value).fail() )
        v.push_back(value);
    return is;
}
} // std



#endif // STREAMS_INTERACTION_H

