#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include"ch2bit.h"
int main() {
	char toSend = 0x20;
	HANDLE hComm;
	char recibido;
	double frequency;
	long unsigned int n, written;
	double To;
	double nx , no;
	BOOL status, statusSent;
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
		printf("No(i)	Nx(i))     |	Period\n");
	}
	
	statusSent = WriteFile(hComm, &toSend, 1, &written, NULL);
	while(status) {
		To = 25e9;
		nx = (double) bits(recibido).a;
		no = (double) bits(recibido).b;
		frequency = (double) (nx/no)*To;
		printf("%.0f	%.0f	|  %.4f\n",no,nx,frequency);
		status = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
	}
	printf("no se logro\n");
	CloseHandle(hComm);			//Closing the Serial Port
	return 0;
}
