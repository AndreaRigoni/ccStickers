#ifndef FOREACH_H
#define FOREACH_H

#include "type_traits.h"

////////////////////////////////////////////////////////////////////////////////
//  FOREACH EXPANSION  /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename T, bool IsConst = true >
class ForeachOnContainer {
public:
    inline ForeachOnContainer(const T & t) :
        m_cnt(t),
        brk(0),
        itr(m_cnt.begin()),
        end(m_cnt.end())
    { }
    const T & m_cnt; int brk;
    typename T::const_iterator itr,end;
};

template <typename T >
class ForeachOnContainer<T,false> {
public:
    inline ForeachOnContainer(T & t) :
        m_cnt(t),
        brk(0),
        itr(m_cnt.begin()),
        end(m_cnt.end())
    { }
    T & m_cnt; int brk;
    typename T::iterator itr,end;
};
} // detail



// WARNING: GCC ONLY //
#define _FOREACH_EXPANSION(variable, container)                          \
for (detail::ForeachOnContainer<__typeof__(container), is_const<__typeof__(container)>::value > _cnt(container); \
     !_cnt.brk && _cnt.itr != _cnt.end;                                  \
     __extension__  ({ ++_cnt.brk; ++_cnt.itr; })  )                \
    for (variable = *_cnt.itr;; __extension__ ({--_cnt.brk; break;}))

// foreach define //
# ifdef foreach
#  undef foreach
   COMPILE_WARNING( overloading foreach definition );
# else
#  define foreach _FOREACH_EXPANSION
# endif



#endif // FOREACH_H

