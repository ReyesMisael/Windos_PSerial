#include<iostream>
#include<utility>
#include<functional>
#include"ch2bit.h"
using namespace std;
PairBits bits(char data) {
        unsigned int size = 4;
        unsigned int x = 0xf0;                     //To obtain MSB
        unsigned int y = 0x0f;                     //TO obtain LSB
       	
	unsigned int a;
	unsigned int b;
	a = data & x;
	b = data & y;
	a = a >> size;				//Avoid unnecesary bits
        //cout << "MSB--->" << a << endl;
        //cout << "LSB--->" << b << endl;
	return {a, b};
}
