/***
* I refered the below youtube link.
* https://www.youtube.com/watch?v=WDn-htpBlnU&list=PLZo2FfoMkJeEogzRXEJeTb3xpA2RAzwCZ&index=7
***/

#include <iostream>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	WSADATA wsaDATA;
	WORD ver = MAKEWORD(2,2);
	int wsOK = WSAStartup(ver, &wsaDATA);
	if(wsOK != 0){
		cerr << "Could not initialize winsock" << endl;
		return -1;
	}
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == INVALID_SOCKET) {
		cerr << "Can not create listening socket" << endl;
		return -1;
	}
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	
	listen(listening, SOMAXCONN);
	
	sockaddr_in client;
	int clientSize = sizeof(client);
	
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);
	
	if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0){
		cout << host <<" connected on port " << service << endl;
	} else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " conneceted on port " << ntohs(client.sin_port) << endl;
	}
	
	char buf[4096];
	while(true) {
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == INVALID_SOCKET) {
			cerr << "Error in recv(), Quitting.. " << endl;
			return -2;
		} else if(bytesReceived == 0) {
			cout << "Client Disconnected" << endl;
			break;
		} else {
			cout << string(buf, 0, bytesReceived) << endl;
			send(clientSocket, buf, bytesReceived + 1, 0);
		}
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
