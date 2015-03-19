#ifndef FLAGS_H
#define FLAGS_H


////////////////////////////////////////////////////////////////////////////////
//  Flags  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template<typename Enum>
class Flags
{
    int i;
public:
    typedef Enum enum_type;
    inline Flags(const Flags &f) : i(f.i) {}
    inline Flags(Enum f) : i(f) {}
    inline Flags(unsigned int f) : i(f) {}
    inline Flags() : i(0) {}

    inline Flags &operator=(const Flags &f) { i = f.i; return *this; }
    inline Flags &operator&=(int mask) { i &= mask; return *this; }
    inline Flags &operator&=(unsigned int mask) { i &= mask; return *this; }
    inline Flags &operator|=(Flags f) { i |= f.i; return *this; }
    inline Flags &operator|=(Enum f) { i |= f; return *this; }
    inline Flags &operator^=(Flags f) { i ^= f.i; return *this; }
    inline Flags &operator^=(Enum f) { i ^= f; return *this; }

    inline operator int() const { return i; }

    inline Flags operator|(Flags f) const { return Flags(Enum(i | f.i)); }
    inline Flags operator|(Enum f) const { return Flags(Enum(i | f)); }
    inline Flags operator^(Flags f) const { return Flags(Enum(i ^ f.i)); }
    inline Flags operator^(Enum f) const { return Flags(Enum(i ^ f)); }
    inline Flags operator&(int mask) const { return Flags(Enum(i & mask)); }
    inline Flags operator&(unsigned int mask) const { return Flags(Enum(i & mask)); }
    inline Flags operator&(Enum f) const { return Flags(Enum(i & f)); }
    inline Flags operator~() const { return Flags(Enum(~i)); }

    inline bool operator!() const { return !i; }
    inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }

    // non funzia ..
    //    inline friend Flags operator | (Enum f1, Enum f2)
    //    { return Flags(f1) | f2; }

    //    inline friend Flags operator | (Enum f1, Flags f2)
    //    { return f2 | f1; }
};



#define DEFINE_OPERATORS_FOR_FLAGS(_flags) \
    inline Flags<_flags::enum_type> operator | (_flags::enum_type f1, _flags::enum_type f2) \
{ return Flags<_flags::enum_type>(f1) | f2; } \
    inline Flags<_flags::enum_type> operator | (_flags::enum_type f1, Flags<_flags::enum_type> f2) \
{ return f2 | f1; }




#endif // FLAGS_H

