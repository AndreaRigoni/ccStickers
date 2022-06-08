#include <string>
#include <iostream>
#include <sstream>



#include "H5Cpp.h"

#include "Core/foreach.h"
#include "Math/ScalarArray.h"


namespace detail {

class H5Path {

    typedef H5Path ThisClass;

public:

    H5Path(std::string path) : _path(path), _ss(path) {}

    size_t len() { 
        size_t len = 0;
        std::string level;
        while( std::getline(_ss, level, '/') ) ++len;
        return len;
    }

    // access as string //
    operator std::string() const { return this->_path; }
    operator const std::string &() const { return this->_path; }

    friend std::ostream &
    operator << (std::ostream &o, const ThisClass &self) {
        return o << static_cast<const std::string &>(self);
    }
    

private:
    std::string _path;
    std::stringstream _ss;

};

} // detail


//   _   _ ____   //
//  | | | | ___|  //
//  | |_| |___ \  //
//  |  _  |___) | //
//  |_| |_|____/  //
//                //



class H5TreeIO {
    

public:

    explicit H5TreeIO(std::string filename) :
        _file(NULL),
        _default_compression_level(6),
        _default_dataset_plist(NULL)
    {

        // Turn off the auto-printing when failure occurs so that we can
        // handle the errors appropriately
        H5::Exception::dontPrint();

        // Create file instance
        this->_file = new H5::H5File(filename, H5F_ACC_TRUNC);

        // Modify dataset creation property to enable chunking
        _default_dataset_plist = new H5::DSetCreatPropList;

        // Set ZLIB (DEFLATE) Compression using level 6.
        // To use SZIP compression comment out this line.
        _default_dataset_plist->setDeflate(6);

    }

    H5::DataSet& get(const detail::H5Path &path) const {
        
  
        std::string group_name = static_cast<std::string>(path);
        try         {
            H5::Group group = this->_file->openGroup (group_name.c_str());
        } catch (...) {
            H5::Group group = this->_file->createGroup(group_name.c_str());
        }
        H5::Group group = this->_file->openGroup  (group_name.c_str()); // for debugging
        
        // H5::DataSet dataset
    }



private:

    H5::H5File *_file;
    size_t _default_compression_level;
    H5::DSetCreatPropList *_default_dataset_plist;
    
};





