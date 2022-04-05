
#ifndef BUFFERED_IO_H
#define BUFFERED_IO_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

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
    explicit Buffer(size_t size) : BaseClass(size) {}

    virtual void spool() { /* BaseClass::clear(); */ }

    // write if \n or \r is inserted
    Buffer & operator << (const char c) {
        if (c != '\n' && c != '\r') return *this << c;
        else this->spool();
        return *this;
    }

    // write if std::endl is inserted
    void operator << ( std::ostream& (*)(std::ostream&) ) {
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


namespace detail {
void mkdir_p(const char *filename, bool wipe_last);
}






class folded_fstream : public std::basic_fstream<char> {

    typedef folded_fstream ThisClass;
    typedef std::basic_fstream<char> BaseClass;

public:

    explicit folded_fstream(const char *filename, 
                             std::ios_base::openmode __mode = BaseClass::trunc | BaseClass::in | BaseClass::out )
        {
            detail::mkdir_p(filename, true);
            BaseClass::close();
            this->open(filename, __mode);
        }

    ~folded_fstream() { if(this->is_open()) close(); }
    
    void close() {
        *this << std::flush;
        BaseClass::close();
    }

    // template < typename T >
    // ThisClass& operator << (const T& data) {
    //     return *this;
    // }


};



class TextBufferIO {

    typedef folded_fstream __Buffer;

    typedef std::map< std::string, __Buffer* > __Map;

public:

    typedef __Buffer Buffer;

    explicit TextBufferIO(std::string prefix = "") : _map(), _prefix(prefix) {}
    
    ~TextBufferIO() { this->close(); }

    inline Buffer& operator () (const char *path) { return at(path); }

    Buffer& at(const char *file_path) { 
        std::string path = this->_path(file_path);
        __Map::iterator it = _map.find(path);
        if(it == _map.end()) {
            _map[path] = new Buffer(path.c_str());
            return *_map.at(path);
        }
        else return *it->second;
    }

    void close() {
        for (auto &el: _map) {
            el.second->close();
            delete el.second;
        }
        _map.clear();     
    }

private:
    __Map _map;
    std::string _prefix;

    inline std::string _path(const char *path) { return _prefix+std::string(path); }

};














#endif // BUFFERED_IO_H