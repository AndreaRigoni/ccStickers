
#include <iostream>




class PointImpl2 {
    float m_x,m_y;
public:    
    float & x() { return m_x; }
    const float & x() const { return m_x; }    
    float & y() { return m_y; }
    const float & y() const { return m_y; }
        
};


class PointImpl1 {
    double data[2];
public:
    const double GetX() const { return data[0]; }
    const double GetY() const { return data[1]; }    
    void SetX(const double x) { data[0] = x; }
    void SetY(const double y) { data[1] = y; }    
};


//struct PointImpl1 {
//    float x,y;
//};


class IPoint {
    
    template < typename T >
    static float s_GetX(void * ob) { return reinterpret_cast<T*>(ob)->GetX(); }
    
    template < typename T >
    static float s_GetY(void * ob) { return reinterpret_cast<T*>(ob)->GetY(); }
    
    float (* m_GetX)(void *);
    float (* m_GetY)(void *);
    void * m_ob;

public:
    template < typename T >
    IPoint(T &t) :
        m_ob(&t),
        m_GetX( s_GetX<T>(m_ob) ),
        m_GetY( s_GetY<T>(m_ob) )
    {}
    
//    float GetX() { return m_GetX(); }
//    float GetY() { return m_GetY(); }
};


    



int main(int argc, char *argv[])
{
    
    return 0;
}
