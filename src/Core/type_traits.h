#ifndef TYPETRAITS_H
#define TYPETRAITS_H

#include "Core/macros.h"

////////////////////////////////////////////////////////////////////////////////
//  TYPE TRAITS  ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  CV QUALIFIERS MATHCING  ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace detail {

#define MDSIPTEST_TT_AUX_CV_TRAITS_IMPL_PARAM(X) X *
template <typename T> struct cv_traits_imp {};

template <typename T>
struct cv_traits_imp<T*>
{
    MDSIPTEST_STATIC_CONSTANT(bool, is_const    = false);
    MDSIPTEST_STATIC_CONSTANT(bool, is_volatile = false);
    typedef T unqualified_type;
};

template <typename T>
struct cv_traits_imp<MDSIPTEST_TT_AUX_CV_TRAITS_IMPL_PARAM(const T)>
{
    MDSIPTEST_STATIC_CONSTANT(bool, is_const    = true);
    MDSIPTEST_STATIC_CONSTANT(bool, is_volatile = false);
    typedef T unqualified_type;
};

template <typename T>
struct cv_traits_imp<MDSIPTEST_TT_AUX_CV_TRAITS_IMPL_PARAM(volatile T)>
{
    MDSIPTEST_STATIC_CONSTANT(bool, is_const    = false);
    MDSIPTEST_STATIC_CONSTANT(bool, is_volatile = true);
    typedef T unqualified_type;
};

template <typename T>
struct cv_traits_imp<MDSIPTEST_TT_AUX_CV_TRAITS_IMPL_PARAM(const volatile T)>
{
    MDSIPTEST_STATIC_CONSTANT(bool, is_const    = true);
    MDSIPTEST_STATIC_CONSTANT(bool, is_volatile = true);
    typedef T unqualified_type;
};
#undef MDSIPTEST_TT_AUX_CV_TRAITS_IMPL_PARAM

} // detail


////////////////////////////////////////////////////////////////////////////////
//  IS CONST  //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace detail {
template <class T>
struct is_const_rvalue_filter
{
    static const bool value =
            detail::cv_traits_imp<T*>::is_const;
};

template <class T>
struct is_const_rvalue_filter<T*>
{
    static const bool value =
            detail::cv_traits_imp<T*>::is_const;
};

template <class T>
struct is_const_rvalue_filter<T&>
{ static const bool value = false; };

template <class T>
struct is_const_rvalue_filter<const T&>
{ static const bool value = true; };

} // detail

template < typename T >
struct is_const : detail::is_const_rvalue_filter<T> {};



////////////////////////////////////////////////////////////////////////////////
//  ENABLE IF  /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <bool B, class T = void>
struct enable_if {
    typedef T type;
};

template <class T>
struct enable_if<false, T> {};







#endif // TYPETRAITS_H

