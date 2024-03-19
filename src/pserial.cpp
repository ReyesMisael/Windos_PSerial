#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include"ch2bit.h"
int main() {
	HANDLE hComm;
	int no;
	int nx;
	char recibido;
	long unsigned int n;
	unsigned int a = ~0;
	BOOL status;
	printf("%u\n", a);
	hComm = CreateFileA("\\\\.\\COM4",
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
	if(hComm == INVALID_HANDLE_VALUE)
		printf("Error in opening serial port\n");
	else {
		printf("opening serial port successful\n");
	}

	status = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
	while(status) {
		printf("%x\n", recibido);
		status = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
		bits(recibido);
	}
	printf("no se logro\n");
	CloseHandle(hComm);//Closing the Serial Port
	return 0;
}
