
#include "Options.h"

////////////////////////////////////////////////////////////////////////////////
//  Options  ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



void Options::Parse(int argc, char *argv[])
{
    for(int i=1; i<argc; ++i) {
        detail::value_semantic *val = NULL;
        if( isNameTag(argv[i]) ) {
            val = findValueByName(argv[i]+2);
            std::string arg;
            while( ++i < argc && !isCharTag(argv[i]) && !isNameTag(argv[i]) ) {
                arg += argv[i];
                arg += " ";
            }
            --i;
            if(val) val->parse(arg.substr(0,arg.length()-1));
        }
        else if( isCharTag(argv[i])) {
            val = findValueByChar(argv[i]+1);
            std::string arg;
            while( ++i < argc && !isCharTag(argv[i]) && !isNameTag(argv[i]) ) {
                arg += argv[i];
                arg += " ";
            }
            --i;
            if(val) val->parse(arg.substr(0,arg.length()-1));
        }

        if(val && val->m_name == "help") {
            this->PrintSelf(std::cout);
            exit(0);
        }
    }
}


void Options::PrintSelf(std::ostream &o) const
{
    o << "\n" << m_usage << "\n\n";
    foreach (const detail::value_semantic *val, m_values) {
        if(val->m_ch)
            o << "-" << val->m_ch << " ";
        o << "--" << val->m_name
          << " (" << val->toString() << ") \t" << val->m_description;
        o << "\n";
    }
    o << "\n";
}

