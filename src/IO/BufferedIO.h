
#ifndef BUFFERED_IO_H
#define BUFFERED_IO_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>


#include "Core/foreach.h"

//
//
// BUFFER
//
//


namespace detail {

template < typename T >
class Buffer : public std::vector<T> {
    
    typedef std::vector<T> BaseClass;

public:
    Buffer() : BaseClass() {}
    Buffer(size_t size) : BaseClass(size) {}

    virtual void spool() { /* BaseClass::clear(); */ }

    // write if \n or \r is inserted
    Buffer & operator << (const char c) {
        if (c != '\n' || c != '\r') return *this << c;
        else this->spool();
        return *this;
    }

    // write if std::endl is inserted
    void operator << ( std::ostream& (*var)(std::ostream&) ) {
        this->spool();
    }

};

} // detail

// insertion overload
template < typename T1, typename T2 >
static inline detail::Buffer<T1>& operator << (detail::Buffer<T1>& b, const T2& data) {
    b.push_back(data);
    return b;
}    

// extract to ostream //
template < typename T >
static inline std::ostream& operator << (std::ostream &o, const detail::Buffer<T> buffer) {
    // foreach(T el, buffer) { o << el; } // TODO: fix this
    for (size_t i=0; i<buffer.size(); ++i) o << buffer[i] << ' ';
    return o;
}


class folded_container {
public:
    folded_container(const char *filename) {
        mkdir_p(filename);
    }
private:
    static void mkdir_p(const char *filename);
};



template < typename _FileFormat >
class folded_ofstream : public std::basic_ofstream<_FileFormat>,
                        private folded_container {

    typedef folded_ofstream ThisClass;
    typedef std::basic_ofstream<_FileFormat> BaseClass;

public:
    folded_ofstream(const char *filename, const char separator = ' ') :
        _separator(separator) {
            folded_container(filename);
            BaseClass(filename, std::ios_base::out);
        }

    ~folded_ofstream() { if(this->is_open()) close(); }
    
    void close() {
        *this << std::flush;
        BaseClass::close();
    }

    // template < typename T >
    // ThisClass& operator << (const T& data) {
    //     return *this;
    // }

private:
    char _separator;

};





class Subfolders {

public:
    Subfolders(const char *name) {}

    // Write file data once
    template < typename T >
    int write_once(const char *file_path, const T& t);


private:
    static void mkdir_p(const char *path, bool wipe_last = 0);

};


template < typename T >
int Subfolders::write_once (const char *file_path, const T& t)  {
    try {
        // create path
        mkdir_p(file_path, 1);
        // write file
        std::ofstream myfileOUT(file_path, std::ofstream::out);
        myfileOUT << t << "\n";  }
    catch (std::exception &e) {
        std::cerr << "ERROR writing output file\n" << e.what() << "\n";
        return 1;
    }
    return 0;
}


















#endif // BUFFERED_IO_H