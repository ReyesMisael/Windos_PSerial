#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<Winbase.h>
#include"ch2bit.h"
void PrintCommState(DCB dcb){				//Provide us a actual serial port configiration
	printf("\n Baudrate = %d, ByteSize = %d, Parity = %d, StopBits = %d \n",
			dcb.BaudRate,
			dcb.ByteSize,
			dcb.Parity,
			dcb.StopBits);
}

int main() {
	char toSend = 0x20;				//Test char by FPGA 
	HANDLE hComm;
	DCB serialParams;
	DWORD bytessend;
	char recibido;
	double frequency;
	long unsigned int n, written;
	double To;
	double nx, no;
	BOOL statusReceive, statusSend, fsuccess;
	hComm = CreateFileA("\\\\.\\COM4",
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

	memset(&serialParams,0,sizeof(DCB));		//clear DCB 	
	serialParams.DCBlength = sizeof(DCB);

	fsuccess = GetCommState(hComm, &serialParams);
	
	if (!fsuccess){
		printf("SetCommState failed with error %d.\n", GetLastError());
		return (3);

	}
	
 	PrintCommState(serialParams);

 	serialParams.BaudRate = CBR_115200;
	serialParams.ByteSize = 8;
	serialParams.Parity = NOPARITY;
	serialParams.StopBits = ONESTOPBIT;

	fsuccess = SetCommState(hComm, &serialParams);

	if (!fsuccess){
		printf("SetCommState failed with error %d.\n", GetLastError());
		return (2);

	}
	
	PrintCommState(serialParams);
	
	statusSend = WriteFile(hComm, &toSend, 1, &bytessend, NULL);
	
	statusReceive = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
	if(hComm == INVALID_HANDLE_VALUE) {

		printf("Error in opening serial port\n");
		return (1);
	}
	else {
		printf("opening serial port successful\n");
		printf("No(i)	Nx(i))     |	Period\n");
	}
	
	statusSend = WriteFile(hComm, &toSend, 1, &written, NULL);
	while(statusReceive && statusSend) {
		To = 25e9;
		nx = (double) bits(recibido).a;
		no = (double) bits(recibido).b;
		frequency = (double) (nx/no)*To;
		printf("%.0f	%.0f	|  %.4f\n",no,nx,frequency);
		statusReceive = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
	}
	printf("no se logro\n");
	CloseHandle(hComm);			//Closing the Serial Port
	return (0);
}
