#include<stdlib.h>
#include<stdio.h>

typedef unsigned int unit;
unit BinaryToGray(unit num);
unit GrayToBinary(unit num);
int main() {
	unit a;
	unit number = 0;
	scanf("%d", &a);
	number = BinaryToGray(a);
	printf("%i\n",number);
	number = GrayToBinary(number);
	printf("%i\n",number);

}

unit GrayToBinary(unit num){
	unit mask = num;
	while(mask){
		mask >>=1;
		num	^= mask;
	}
	return num;
}
unit BinaryToGray(unit num){
	return num ^ (num >> 1);

}
