
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
            std::stringstream arg;
            while( ++i < argc && !isCharTag(argv[i]) && !isNameTag(argv[i]) )
                arg << argv[i] << " ";
            --i;
            if(val) val->parse(arg.str());
        }
        else if( isCharTag(argv[i])) {
            val = findValueByChar(argv[i]+1);
            std::stringstream arg;
            while( ++i < argc && !isCharTag(argv[i]) && !isNameTag(argv[i]) )
                arg << argv[i] << " ";
            --i;
            if(val) val->parse(arg.str());
        }

        if(val && val->m_name == "help") {
            this->PrintSelf(std::cout);
            exit(0);
        }
    }
}


void Options::PrintSelf(std::ostream &o)
{
    o << "\n" << m_usage << "\n\n";
    foreach (detail::value_semantic *val, m_values) {
        if(val->m_ch)
            o << "-" << val->m_ch << " ";
        o << "--" << val->m_name
          << " (" << val->toString() << ") \t" << val->m_description;
        o << "\n";
    }
    o << "\n";
}

