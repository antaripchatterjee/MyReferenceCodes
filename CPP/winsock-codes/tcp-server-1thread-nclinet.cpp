/***
* I refered the below youtube link.
* https://www.youtube.com/watch?v=dquxuXeZXgo
***/

#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <sstream>

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
	
	fd_set master;
	FD_ZERO(master);
	
	FD_SET(listening, &master);
	
	while(true) {
		fd_set master_copy = master;
		int socketCount = select(0, &master_copy, nullptr, nullptr, nullptr);
		
		for(int i=0; i < socketCount; i++) {
			SOCKET sock = master_copy.fd_array[i];
			if(sock == listening) {
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);
				
				FD_SET(client, &master);
				string welcomeMsg = "Welcome to the chat server\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			} else {
				// Accept a new message
				char buf[4096];
				ZeroMemory(buf, 4096);
				int bytesIn = recv(sock, buf, 4096, 0);
				if(bytesIn <= 0) {
					closesocket(sock);
					FD_CLR(sock, &master);
				} else {
					for(int i = 0; i < master.fd_count; i++) {
						SOCKET outSock = master.fd_array[i];
						if(outSock != listening && outSock != sock) {
							ostringstream os;
							os << "SOCKET #" << sock << ": "<<
								buf << "\r\n";
							string strOut = ss.str();
							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}
	WSACleanup();
	return 0;
}