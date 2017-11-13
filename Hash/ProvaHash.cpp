#include<iostream>
#include<iomanip>
#include<bitset>
#include<fstream>
#include<sstream>

using namespace std;

unsigned long hashstring(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main (int argc,unsigned char* argv[])
  {
    //Un long occupa 8 byte, quindi per assicurare l'iniettività bisogna che il bitset 8x8 = 64 bit.(?)
    cout <<endl<< bitset<128>(hashstring(argv[1]))<<endl;
    return 0;
  }
