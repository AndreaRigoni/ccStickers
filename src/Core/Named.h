#ifndef NAMED_H
#define NAMED_H

#include <string>

////////////////////////////////////////////////////////////////////////////////
//  Named  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Named
{
public:
    Named(const char *name = "") :
        m_name(name)
    {}

    std::string & operator()() { return m_name; }

    const std::string & operator()() const { return m_name; }

    void SetName(std::string name) { m_name = name; }

    std::string GetName() const { return m_name; }

    template < class Archive >
    friend void serialize(Archive &ar, Named &n) {
        ar & n.m_name;
    }

private:
    std::string m_name;
};


#endif // NAMED_H

