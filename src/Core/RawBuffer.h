#ifndef RAWBUFFER_H
#define RAWBUFFER_H

#include <stddef.h>
#include <deque>

////////////////////////////////////////////////////////////////////////////////
//  Raw Buffer  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef unsigned char byte_t;

// WARNING: keep endianes in mind, this works only within the same machine //
struct RawBuffer {

    template < typename T >
    friend RawBuffer & operator << (RawBuffer &r, const T &data) {
        const byte_t *pos = (byte_t *)&data;
        const byte_t *end = (byte_t *)&data + sizeof(data);
        while(pos < end) {
            r.m_data.push_back(*pos++);
        }
        return r;
    }

    template < typename T >
    friend RawBuffer & operator >> (RawBuffer &r, T &data) {
        byte_t *pos = (byte_t *)&data;
        byte_t *end = (byte_t *)&data + sizeof(data);
        while(pos < end) {
            *pos++ = r.m_data.front();
            r.m_data.pop_front();
        }
        return r;
    }

    size_t size() const { return m_data.size(); }

    std::deque<byte_t> m_data;
};


#endif // RAWBUFFER_H

