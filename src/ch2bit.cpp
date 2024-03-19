#include<iostream>
#include<utility>
#include<functional>
#include"ch2bit.h"
using namespace std;

PairBits bits(char recibir) {
        unsigned int size = 4;
	
        bitset<32> x(0xf0);                     //To obtain MSB
        bitset<32> y(0x0f);                     //TO obtain LSB
        bitset<32> Pair(recibir);              	//Convert char reciven to bits
        bitset<32> a(Pair & x);                 //Obtain fisrt part
        bitset<32> b(Pair & y);                 //Obain second part
	a = a >> size;				//Avoid unnecesary bits

        cout << "MSB--->" << a << endl;
        cout << "LSB--->" << b << endl;
	return {a, b};
}
