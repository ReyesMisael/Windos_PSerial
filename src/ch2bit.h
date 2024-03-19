#ifndef CH2BIT_H
#define CH2BIT_H
#include<bitset>
struct PairBits {
	std::bitset<32> a;
	std::bitset<32> b;
};
typedef struct PairBits PairBits;
PairBits bits(char recibir);

#endif
