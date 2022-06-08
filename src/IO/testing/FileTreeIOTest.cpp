#include <vector>
#include <cmath>
#include <sstream>

#include "IO/FileTreeIO.h"

#include "Core/foreach.h"
#include "Core/testing/testing-prototype.h"

#include "Math/ScalarArray.h"

int main(void) {

    BEGIN_TESTING(test_buffer_io)

    FileTreeIO buffer;
    
    {   // TEXT IO BUFFER // 
        
        auto &b = buffer("1/2/3/prova.txt");
        b << "prova prova2 123  555.2368" << std::endl;
    
        b.seekp(0);

        std::string prova, prova2;
        b >> prova >> prova2;

        TEST1( prova == std::string("prova") );
        TEST1( prova2 == std::string("prova2") );

        // integer
        int number;
        b >> number;
        TEST1( number == 123 );

        // float
        double ghostbuster_phone;
        b >> ghostbuster_phone;
        TEST1( ghostbuster_phone == 555.2368 ); 

    }

    {   // TEXT IO BUFFER - reading structured data // 

        auto &b = buffer("1/2/prova_base.txt");
        b <<    "int_array "   <<  " 1 2 3 4 5 6 \n "
                 "double_array "  " 7.0 8.1 9.2 10.3 11.4 12.5 ";

        b.seekp(0);

        // std::vectors
        std::string label1, label2;
        std::vector<int> v1;
        std::vector<double> v2;
        b >> label1;
        b >> v1;
        b >> label2;
        b >> v2;

        TEST1( label1 == std::string("int_array") );
        for (int i=0; i < v1.size(); ++i) TEST1( v1[i] == i+1 );
        TEST1( label2 == std::string("double_array") );
        for (int i=0; i < v2.size(); ++i) TEST1( v2[i] == i+7 + i*1E-1 );
        
    }   

    {   // TEXT IO BUFFER - reading to scalar arrays //

        auto &b = buffer("1/2/prova_scalar_array.txt");
        b << "1 2 3" << std::endl
          << "4 5 6 7" << std::endl
          << "8 9 10 11" << std::endl
          << "1.2 3.4 5.6" << std::endl
          ;

        b.seekp(0);

        Vector3i V1, v1;
        Vector4i V2, v2;
        Vector4i V3, v3;
        Vector3f V4, v4;

        v1 << 1,2,3;
        v2 << 4,5,6,7;
        v3 << 8,9,10,11;
        v4 << 1.2, 3.4, 5.6;

        b >> V1;
        b >> V2;
        b >> V3;
        b >> V4;

        TEST1( V1 == v1 );
        TEST1( V2 == v2 );
        TEST1( V3 == v3 );
        TEST1( V4 == v4 );
        
    }




    END_TESTING;
}