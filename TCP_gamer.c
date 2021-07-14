#include <WinSock2.h>
#include <WS2tcpip.h>
#include <ws2def.h>
#include <stdio.h>
#include <limits.h>
#include "Queue_list.h"

#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"


#pragma comment(lib,"Ws2_32.lib")
void LienTucLangNghe(SOCKET*, struct Queue* );

int main(int argc, char* argv[]) {
	//Tao winsock va socket thi tuong tu nhu server
	//Buoc 0:
	char diaChiIP[100];
	char soPort[10];

	printf("Nhap vao dia chi IP: \n");
	gets_s(diaChiIP, 100);

	printf("Nhap vao so Port: \n");
	gets_s(soPort, 10);


	//Buoc 1: Khoi tao winsock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock khong hoat dong");
		return 0;
	}

	//Buoc 2: khoi tao socket
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		printf("ERROR %d: khong the khoi tao server socket", WSAGetLastError());
		return 0;
	}

	//(optional) dat gio time-out
	int tv = 10000;
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));

	//Buoc 3: Specify server address
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	/*serverAddr.sin_port = htons(SERVER_PORT);*/
	serverAddr.sin_port = htons(atoi(soPort));
	/*inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);*/
	inet_pton(AF_INET, diaChiIP, &serverAddr.sin_addr);

	//Buoc 4: Yeu cau ket noi toi server
	if (connect(client, (SOCKADDR*)&serverAddr, sizeof(serverAddr))) {
		printf("ERROR %d: khong the ket noi den server", WSAGetLastError());
		return 0;
	}

	printf("Da ket noi den server!\n");
	struct Queue* queue = createQueue(1000);

	//Buoc 5: Giao tiep voi server
	char buff[2048];
	int ret, messageLen;
	while (1) {
		//send message
		printf("Gui den server: ");
		gets_s(buff, 2048);
		messageLen = strlen(buff);

		if (messageLen == 0) break;
		//Do cu gui bao nhieu byte thi nhan ve bay nhieu?! => Van de co the la o server
		ret = send(client, buff, messageLen, 0);
		if (ret == SOCKET_ERROR)
			printf("ERROR %d: khong the gui data", WSAGetLastError());

		//Nhan echo message

		/*ret = recv(client, buff, 2048, 0);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT)
				printf("Time-out!");
			else printf("ERROR %d: khong the nhan duoc data", WSAGetLastError());
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			printf("Nhan tu server: %s\n", buff);
		}*/
		LienTucLangNghe(client, queue);
	}

	//Buoc 6: Close socket
	closesocket(client);

	//Buoc 7: Terminate Winsock
	WSACleanup();

	return 0;
}

void LienTucLangNghe(SOCKET* s,  struct Queue* queue) {
	int ret;
	char buff[2048];
	while (1) {
		ret = recv(s, buff, strlen(buff), 0);
		if (ret == SOCKET_ERROR) {
			/*if (WSAGetLastError() == WSAETIMEDOUT)
				printf("Time-out!");*/
			/*else */
			printf("ERROR %d: khong the nhan duoc data", WSAGetLastError());
			return 0;
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			printf("Nhan tu server: %s\n", buff);
			enqueue(queue, buff);
		}
	}
}