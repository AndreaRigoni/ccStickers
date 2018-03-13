
#include <iostream>
#include <vector>
#include <Math/StatisticUtils.h>

#include "Core/testing/testing-prototype.h"

int main(int argc, char *argv[])
{
    BEGIN_TESTING(MA);
    StatUtils::MA ma(5);
    std::vector<double> v(50);

    for (int i=0; i<v.size(); ++i) v[i]=0;
    v[10]=1;
    v[20]=1;
    v[22]=1;

    for(int i=0; i<v.size(); ++i) {
        ma.add(v[i]);
        if(i>9 && i<15) {
//            std::cout << "ma["<<i<<"]: " << ma.mean() << "\n";
            TEST1( AreSame(ma.mean(),0.2) );
        }
        if(i>=20 && i<=21) {
//            std::cout << "ma["<<i<<"]: " << ma.mean() << "\n";
            TEST1( AreSame(ma.mean(),0.2) );
        }
        if(i>=22 && i<=24) {
//            std::cout << "ma["<<i<<"]: " << ma.mean() << "\n";
            TEST1( AreSame(ma.mean(),0.4) );
        }
        if(i>=25 && i<=26) {
//            std::cout << "ma["<<i<<"]: " << ma.mean() << "\n";
            TEST1( AreSame(ma.mean(),0.2) );
        }
    }

    END_TESTING;
}
