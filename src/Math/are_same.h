#ifndef ARE_SAME_H
#define ARE_SAME_H

////////////////////////////////////////////////////////////////////////////////
//  are_same  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template < typename T >
bool are_same(T a, T b) {
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
}


// THIS COMES FROM EPSILON DOCUMENTATION //
// not tested //
template<class T>
typename enable_if<!std::numeric_limits<T>::is_integer, bool>::type
are_same(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
    // unless the result is subnormal
           || std::abs(x-y) < std::numeric_limits<T>::min();
}

#endif // ARE_SAME_H

