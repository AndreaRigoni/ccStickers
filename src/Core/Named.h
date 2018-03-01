#ifndef NAMED_H
#define NAMED_H

#include <string>

////////////////////////////////////////////////////////////////////////////////
//  Named  /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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

    void SetName(std::string name) {
        m_name = trim(name);
    }

    const std::string & GetName() const { return m_name; }

    template < class Archive >
    friend void serialize(Archive &ar, Named &n) {
        ar & n.m_name;
    }

private:
    std::string m_name;

    inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
    {
        s.erase(0, s.find_first_not_of(t));
        return s;
    }

    // trim from right
    inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
    {
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }

    // trim from left & right
    inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
    {
        return ltrim(rtrim(s, t), t);
    }
};

#endif // NAMED_H

