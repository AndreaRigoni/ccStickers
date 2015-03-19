#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>


#include "SerializeUtils.h" // container stream interaction //
#include "Threads.h"





////////////////////////////////////////////////////////////////////////////////
//  CsvDataFile  ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class CsvDataFile : public std::fstream
{
    typedef std::fstream BaseClass;
public:
    CsvDataFile() :
        m_comma(';')
    {}

    explicit CsvDataFile(const char *name, std::ios_base::openmode mode = std::ios_base::out, const char comma = ';') :
        BaseClass(name,mode),
        m_file_name(name),
        m_comma(comma)
    {}

    // hide fstream open //
    void open(const std::string &s, ios_base::openmode mode) {
        m_file_name = s;
        BaseClass::open(s.c_str(),mode);
    }

    // hide fstream open //
    void open(const char *s, ios_base::openmode mode) {
        m_file_name = s;
        BaseClass::open(s,mode);
    }

    const char Separator() const { return m_comma; }

    template < typename T >
    friend CsvDataFile &
    operator , (CsvDataFile &csv, const T &el) {
        csv << csv.Separator() << el;
        return csv;
    }

private:
    std::string m_file_name;
    char m_comma;
};













#endif // FILEUTILS_H
