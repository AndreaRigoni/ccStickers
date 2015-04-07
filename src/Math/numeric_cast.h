#ifndef NUMERIC_CAST_H
#define NUMERIC_CAST_H

#include <iostream> // remove

#include <math.h>
#include <limits>
#include <stdexcept>

#include <cmath>

#include "Core/type_traits.h"


////////////////////////////////////////////////////////////////////////////////
//  Numeric Limits  ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/// Numeric Limits for Floating types
template < typename T, typename EnableIf = void >
class numeric_limits : public std::numeric_limits<T>
{
public:
    typedef std::numeric_limits<T> BaseClass;
    static inline T highest() { return BaseClass::max(); }
    static inline T lowest() { return -BaseClass::max(); }
};

/// Numeric Limits for Integer types
template < typename T >
class numeric_limits<T, typename enable_if<
        std::numeric_limits<T>::is_integer>
        ::type > :
        public std::numeric_limits<T>
{
public:
    typedef std::numeric_limits<T> BaseClass;
    static inline T highest() { return BaseClass::max(); }
    static inline T lowest() { return BaseClass::min(); }
};






// YOU REALLY SHOULD PREFER BOOST CONVERSION //
//#include <boost/numeric/conversion/cast.hpp>


////////////////////////////////////////////////////////////////////////////////
//  numeric_cast  //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



// LIMITS VERSION //

namespace detail {

template < typename Target, typename Source >
struct numeric_cast_trait {
    typedef numeric_limits<Source> Slimits;
    typedef numeric_limits<Target> Tlimits;
    static const bool is_coercion = Slimits::digits > Tlimits::digits;
    static const bool is_u2s = !Slimits::is_signed && Tlimits::is_signed;
    static const bool is_s2u = Slimits::is_signed && !Tlimits::is_signed;
};



template < typename Target, typename Source, typename EnableIf = void >
struct numeric_cast_max_rule {
    static inline void apply(Source value) {
        if( value > static_cast<Source>( numeric_limits<Target>::highest() ) )
            throw ( std::overflow_error("scalar cast overflow"));
    }
};

template < typename Target, typename Source, typename EnableIf = void >
struct numeric_cast_min_rule {
    static inline void apply(Source value) {
        if( value < static_cast<Source>( numeric_limits<Target>::lowest() ) )
            throw ( std::overflow_error("scalar cast underflow"));
    }
};

template < typename Target, typename Source, typename EnableIf = void >
struct numeric_cast_precision_rule {
    typedef numeric_cast_trait<Target,Source> trait;
    static inline void apply(Source value) {
        if( trait::is_coercion ) {
            if( value > (Source)(1<<numeric_limits<Target>::digits-1) )
                throw(std::range_error("scalar loss of precision for digit overflow") );
            if( trait::Slimits::is_signed && value < -static_cast<Source>(1<<numeric_limits<Target>::digits-1) )
                throw(std::range_error("scalar loss of precision for digit underflow") );
        }
        if(value != static_cast<Source>(static_cast<Target>(value)) )
            throw(std::range_error("scalar loss of precision") );
    }
};


////////////////////////////////////////////////////////////////////////////////
//  NumericCastImpl  ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template <typename Target, typename Source, class Enable = void >
struct NumericCastImpl {
    static Target numeric_cast(Source value ) {}
};

// Integer -> Integer
template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        numeric_limits<Source>::is_integer &&
        numeric_limits<Target>::is_integer &&
        numeric_cast_trait<Target,Source>::is_coercion
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        if( numeric_cast_trait<Target,Source>::is_u2s )
            numeric_cast_max_rule<Target,Source>::apply(value);
        else
            numeric_cast_min_rule<Target,Source>::apply(value);
            numeric_cast_max_rule<Target,Source>::apply(value);
        return static_cast<Target>(value);
    }
};

template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        numeric_limits<Source>::is_integer &&
        numeric_limits<Target>::is_integer &&
        !numeric_cast_trait<Target,Source>::is_coercion
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        if( numeric_cast_trait<Target,Source>::is_s2u )
            numeric_cast_min_rule<Target,Source>::apply(value);
        return static_cast<Target>(value);
    }
};

// Integer -> Float
template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        numeric_limits<Source>::is_integer &&
        !numeric_limits<Target>::is_integer &&
        numeric_cast_trait<Target,Source>::is_coercion
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        numeric_cast_precision_rule<Target,Source>::apply(value);
        return static_cast<Target>(value);
    }
};

template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        numeric_limits<Source>::is_integer &&
        !numeric_limits<Target>::is_integer &&
        !numeric_cast_trait<Target,Source>::is_coercion
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        return static_cast<Target>(value);
    }
};

// Float -> Integer
template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        !numeric_limits<Source>::is_integer &&
        numeric_limits<Target>::is_integer
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        numeric_cast_min_rule<Target,Source>::apply(value);
        numeric_cast_max_rule<Target,Source>::apply(value);
        numeric_cast_precision_rule<Target,Source>::apply(value);
        return static_cast<Target>(value);

    }
};


// Float -> Float
template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        !numeric_limits<Source>::is_integer &&
        !numeric_limits<Target>::is_integer &&
        numeric_cast_trait<Target,Source>::is_coercion
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        numeric_cast_min_rule<Target,Source>::apply(value);
        numeric_cast_max_rule<Target,Source>::apply(value);
        numeric_cast_precision_rule<Target,Source>::apply(value);
        return static_cast<Target>(value);
    }
};

template < typename Target, typename Source >
struct NumericCastImpl < Target, Source,
        typename enable_if<
        !numeric_limits<Source>::is_integer &&
        !numeric_limits<Target>::is_integer &&
        !numeric_cast_trait<Target,Source>::is_coercion
        >
        ::type >
{
    static Target numeric_cast(Source value ) {
        return static_cast<Target>(value);
    }
};


} // detail



template <typename Target, typename Source>
inline Target numeric_cast(Source value) {
        return detail::NumericCastImpl<Target,Source>::numeric_cast(value);
}


#endif // NUMERIC_CAST_H

