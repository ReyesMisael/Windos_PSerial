#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<Winbase.h>
void PrintCommState(DCB dcb){
	printf("\n baudrate = %d, ByteSize = %d, Parity = %d, StopBits = %d \n",
		dcb.BaudRate,
		dcb.ByteSize,
		dcb.Parity,
		dcb.StopBits);
}

int main() {
	char toSend = 'L';
	HANDLE hComm;
	DCB serialParams;
	DWORD bytessent;
	char recibido;
	long unsigned int n, written;
	BOOL statusReceive, statusSent, fsuccess; 

	hComm = CreateFileA("\\\\.\\COM4",
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
	
	memset(&serialParams,0, sizeof(DCB));	
	serialParams.DCBlength = sizeof(DCB);

	fsuccess = GetCommState(hComm,&serialParams);

	if (!fsuccess){
		printf("SetCommState failed with error %d.\n",GetLastError());
		return (3);
	}
	
	PrintCommState(serialParams);

	serialParams.BaudRate = CBR_115200;
	serialParams.ByteSize = 8;
	serialParams.Parity = NOPARITY;
	serialParams.StopBits = ONESTOPBIT;

	fsuccess = SetCommState(hComm,&serialParams);
	if (!fsuccess){
		printf("SetCommState failed with error %d.\n",GetLastError());
		return (2);
	}
	fsuccess = GetCommState(hComm,&serialParams);
	if (!fsuccess){
		printf("SetCommState failed with error %d.\n",GetLastError());
		return (3);
	}
	PrintCommState(serialParams);

	statusSent = WriteFile(hComm, &toSend, 1, &bytessent, NULL);
	
	statusReceive = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
	if(hComm == INVALID_HANDLE_VALUE){
		printf("Error in opening serial port\n");
		return (1);
	}
	else {
		printf("opening serial port successful\n");
	}

	while(statusReceive && statusSent) {
		statusSent = WriteFile(hComm, &toSend, 1, &bytessent, NULL);
		statusReceive = ReadFile(hComm, &recibido, sizeof(char), &n, NULL);
		printf("%x\n", (int) recibido);
	}
	printf("no se logro\n");
	CloseHandle(hComm);			//Closing the Serial Port
	return 0;
}
