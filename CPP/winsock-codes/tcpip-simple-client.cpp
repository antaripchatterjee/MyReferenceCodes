/***
* I refered the below youtube link.
* https://www.youtube.com/watch?v=0Zr_0Jy8mWE&list=PLZo2FfoMkJeEogzRXEJeTb3xpA2RAzwCZ&index=8
***/

#include <iostream>
#include <string>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
	string IPAddress = "127.0.0.1";
	int port = 54000;
	
	WSADATA wsaData;
	WORD ver = MAKEWORD(2,2);
	int wsOK = WSAStartup(ver, &wsaData);
	if(wsOK != 0) {
		cerr << "Can not start winsock, Error #" << wsOK << endl;
		return -1;
	}
	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET) {
		cerr << "Can not create socket, Error #" << WSAGetLastError() << endl;
		return -1;
	}
	
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, IPAddress.c_str(), &hint.sin_addr);
	
	int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if(connRes == SOCKET_ERROR) {
		cerr << "Can not connect to server, Error #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return -1;
	}
	
	char buf[4096];
	string input;
	do {
		cout << "CLIENT> ";
		getline(cin, input);
		
		if(input.size() > 0){
			int sendRes = send(sock, input.c_str(), input.size() + 1, 0);
			if(sendRes != SOCKET_ERROR) {
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if(bytesReceived > 0){
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
	} while(input.size() > 0);
	
	closesocket(sock);
	WSACleanup();
	return 0;
}