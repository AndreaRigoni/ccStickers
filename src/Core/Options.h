#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <cstring>

#include <iostream>
#include <sstream>
#include <vector>


#include <stdlib.h> // exit //

#include <Core/foreach.h>
#include <Core/unique_ptr.h>


////////////////////////////////////////////////////////////////////////////////
//  Options  ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace detail {
class value_semantic {
public:
    value_semantic(const char *name,
                   const char ch = 0,
                   const char *desc = "") :
        m_name(name),
        m_ch(ch),
        m_description(desc)
    {}

    virtual ~value_semantic() {}

    virtual void parse( std::string str) {}

    virtual std::string toString() const { return ""; }

    const std::string m_name;
    const char  m_ch;
    std::string m_description;
};

template <typename T>
class value_type : public value_semantic {
    T *m_ptr;
public:
    value_type(const char *name,
               T *ptr = NULL,
               const char ch = 0,
               const char *desc = "") :
        value_semantic(name,ch,desc), m_ptr(ptr) {}

    void parse(std::string str) {
        std::stringstream ss(str);
        ss >> *m_ptr;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << *m_ptr;
        return ss.str();
    }
};

template <>
class value_type<std::string> : public value_semantic {
    std::string *m_ptr;
public:
    value_type(const char *name,
               std::string *ptr = NULL,
               const char ch = 0,
               const char *desc = "") :
        value_semantic(name,ch,desc), m_ptr(ptr) {}

    void parse(std::string str) { *m_ptr = str; }
    std::string toString() const { return *m_ptr; }
};
} // detail


class Options {

    typedef unique_ptr< detail::value_semantic > Value;

public:

    class OptionInit {
        Options *m_init;
    public:
        OptionInit(Options &options) : m_init(&options) {}

        OptionInit &
        operator()(const char *name) {
            m_init->addValue( new detail::value_semantic(name) );
            return *this;
        }

        OptionInit &
        operator()(const char *name, const char *desc) {
            m_init->addValue( new detail::value_semantic(name,0,desc) );
            return *this;
        }

        template <typename T>
        OptionInit &
        operator()(const char* name, T * value, const char* description = "") {
            m_init->addValue( new detail::value_type<T>(name,value,0,description) );
            return *this;
        }
    };

    Options(const char *usage = "") : m_usage(usage) {
        this->AddOptions()("help","print this help");
    }

    void SetUsage(std::string usage) { m_usage = usage; }

    OptionInit AddOptions() { return OptionInit(*this); }

    void Parse(int argc, char *argv[]);

    void PrintSelf(std::ostream &o) const;

    friend std::ostream &
    operator << (std::ostream &o, const Options &opt) {
        opt.PrintSelf(o);
        return o;
    }

private:

    static bool isCharTag(const char *str) {
        return std::strlen(str)>2
                && str[0] == '-'
                && std::isalpha(str[1]); }

    static bool isNameTag(const char *str) {
        return std::strlen(str)>3
                && std::strncmp(str,"--",2) == 0
                && std::isalpha(str[2]);
    }

    detail::value_semantic *findValueByName(const char *name) {
        foreach (detail::value_semantic *val, m_values) {
            if(val->m_name == name) return val;
        }
        return NULL;
    }

    detail::value_semantic *findValueByChar(const char *ch) {
        foreach (detail::value_semantic *val, m_values) {
            if(val->m_ch == ch[0]) return val;
        }
        return NULL;
    }

    void addValue(detail::value_semantic *val) {
        m_values.push_back(val);
    }

    std::vector< Value > m_values;
    std::string          m_usage;
};


#endif // OPTIONS_H

