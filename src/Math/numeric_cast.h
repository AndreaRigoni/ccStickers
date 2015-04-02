#ifndef NUMERIC_CAST_H
#define NUMERIC_CAST_H



#include <math.h>
#include <limits>
#include <stdexcept>

#include <cmath>







template < typename T >
bool are_same(T a, T b) {
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
}


// THIS COMES FROM EPSILON DOCUMENTATION //
template<class T>
//typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
bool are_same(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) < std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
    // unless the result is subnormal
           || std::abs(x-y) < std::numeric_limits<T>::min();
}




// YOU SHOULD PREFER BOOST CONVERSION //
// #include <boost/numeric/conversion/cast.hpp>



// LIMITS VERSION //

namespace detail {
template < typename Target >
inline Target numeric_cast(float value) {
    typedef float Source;
    static const bool is_coercion = std::numeric_limits<Source>::digits > std::numeric_limits<Target>::digits;

    if(!std::numeric_limits<Target>::has_quiet_NaN && isnan(value) )
        throw( std::range_error("nan exception") );

    if(is_coercion && value != static_cast<Source>(static_cast<Target>(value)) ) {
        throw(std::range_error("scalar loss of precision") );
    }
    else if ( value < static_cast<Source>(std::numeric_limits<Target>::min()) )
        throw ( std::underflow_error("scalar cast underflow") );
    else if( value > static_cast<Source>(std::numeric_limits<Target>::max()) )
        throw ( std::overflow_error("scalar cast overflow"));

    return static_cast<Target>(value);
}

template < typename Target >
inline Target numeric_cast(double value) {
    typedef double Source;
    static const bool is_coercion = std::numeric_limits<Source>::digits > std::numeric_limits<Target>::digits;

    if(!std::numeric_limits<Target>::has_quiet_NaN && isnan(value) )
        throw( std::range_error("nan exception") );

    if(is_coercion && value != static_cast<Source>(static_cast<Target>(value)) ) {
        throw(std::range_error("scalar loss of precision") );
    }
    else if ( value < static_cast<Source>(std::numeric_limits<Target>::min()) )
        throw ( std::underflow_error("scalar cast underflow") );
    else if( value > static_cast<Source>(std::numeric_limits<Target>::max()) )
        throw ( std::overflow_error("scalar cast overflow"));

    return static_cast<Target>(value);
}

template <typename Target, typename Source>
inline Target numeric_cast(Source value) {

    static const bool is_coercion = std::numeric_limits<Source>::digits > std::numeric_limits<Target>::digits;
    static const bool u2s = !std::numeric_limits<Source>::is_signed && std::numeric_limits<Target>::is_signed;
    static const bool s2u = std::numeric_limits<Source>::is_signed && !std::numeric_limits<Target>::is_signed;

    if( is_coercion && !u2s ) {
        if ( value < static_cast<Source>(std::numeric_limits<Target>::min()) )
            throw ( std::underflow_error("scalar cast underflow") );
        else if( value > static_cast<Source>(std::numeric_limits<Target>::max()) )
            throw ( std::overflow_error("scalar cast overflow"));
    }
    else if( is_coercion && u2s ) {
        if( value > static_cast<Source>(std::numeric_limits<Target>::max()) )
            throw ( std::overflow_error("scalar cast overflow"));
    }
    else if( !is_coercion && s2u ) {
        if ( value < 0 )
            throw ( std::underflow_error("scalar cast underflow") );
    }
    return static_cast<Target>(value);
}
} // detail




template <typename Target, typename Source>
inline Target numeric_cast(Source value) {
    return detail::numeric_cast(value);
}


#endif // NUMERIC_CAST_H

