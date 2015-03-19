#ifndef CORE_AUTODELETE_H
#define CORE_AUTODELETE_H


////////////////////////////////////////////////////////////////////////////////
//  AutoDelete  ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template < class T >
class AutoDelete
{
public:
    AutoDelete(const T *ptr) : m_ptr(ptr) {}

    ~AutoDelete() {
        delete m_ptr;
    }

private:
    const T *m_ptr;
};




#endif // AUTODELETE_H

