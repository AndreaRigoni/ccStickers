#ifndef SCALARARRAY_H
#define SCALARARRAY_H

////////////////////////////////////////////////////////////////////////////////
//  ScalarArray  ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>

#include "Core/CommaInitializer.h"


template < typename _Scalar, unsigned int _Dim >
class ScalarArray
{
    typedef ScalarArray<_Scalar,_Dim> ThisClass;

public:

    typedef _Scalar ScalarType;

    ScalarArray() {
        //        std::fill( m_data, m_data + sizeof(m_data), 0 );
        for(unsigned int i = 0; i<_Dim; ++i)
            m_data[i] = 0;
    }

    ScalarArray(_Scalar x, _Scalar y = 0, _Scalar z = 0) {
        _Scalar *args[3] = {&x,&y,&z};
        for(unsigned int i = 0; i<_Dim; ++i)
            m_data[i] = *args[i];
    }

    typedef CommaInitializer< ThisClass , _Scalar >  CommaInit;

    inline CommaInit operator << (_Scalar scalar) {
        return CommaInit(this, scalar);
    }

    _Scalar & operator() (const size_t i) { assert(i<_Dim); return m_data[i]; }
    const _Scalar & operator() (const size_t i) const { assert(i<_Dim); return m_data[i]; }

    template < typename _Other >
    ScalarArray<_Other,_Dim> cast() {
        ScalarArray<_Other,_Dim> cast_out;
        for(unsigned int i = 0; i<_Dim; ++i)
            cast_out.m_data[i] = static_cast<_Other>(this->m_data[i]);
        return cast_out;
    }

    template < typename _Other >
    inline operator ScalarArray<_Other,_Dim> () {
        return this->cast<_Other>();
    }

    inline friend bool operator < (const ThisClass &t1, const ThisClass &t2) {
        return t1(0) < t2(0);
    }

    inline friend bool operator == (const ThisClass &t1, const ThisClass &t2) {
        bool out = 1;
        for(unsigned int i = 0; i<_Dim; ++i) {
            out &= t1.m_data[i] == t2.m_data[i];
        }
        return out;
    }

    friend std::ostream &
    operator << (std::ostream &o, const ThisClass &pt) {
        for(unsigned int i=0; i<_Dim-1; ++i) o << pt(i) << ",";
        return o << pt(_Dim-1);
    }

    friend std::istream &
    operator >> (std::istream &is, ThisClass &v) {
        char sep; // any separator //
        for(unsigned int i=0; i<_Dim-1; ++i) is >> v(i) >> sep;
        is >> v(_Dim-1);
        return is;
    }

private:
    friend class CommaInitializer< ScalarArray<_Scalar,_Dim> , _Scalar >;
    template <typename _Other, unsigned int _OtherDim> friend class ScalarArray;

    void resize(int i) {}

    _Scalar m_data[_Dim];
};


typedef ScalarArray<float,2> Vector2f;
typedef ScalarArray<float,3> Vector3f;
typedef ScalarArray<float,4> Vector4f;

typedef ScalarArray<double,2> Vector2d;
typedef ScalarArray<double,3> Vector3d;
typedef ScalarArray<double,4> Vector4d;

typedef ScalarArray<int,2> Vector2i;
typedef ScalarArray<int,3> Vector3i;
typedef ScalarArray<int,4> Vector4i;

typedef Vector3d Point2D;



#endif // SCALARARRAY_H

