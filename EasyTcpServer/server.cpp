#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>
// windows 平台使用指定的库
// #pragma comment(lib, "ws2_32.lib")

int main() {
	WORD ver = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(ver, &data);
	char msgBuffer[] = "Hello World!";
	//-----------------------//
	// 1. 
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 2. 
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(8888);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY; // inet_addr("127.0.0.1")
	
	// 3. 
	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		printf("ERROR 绑定失败\n");
	}
	else {
		printf("绑定成功\n");
	}
	listen(_sock,5);

	// 4. 
	sockaddr_in clientAdd = {};
	int addLen = sizeof(clientAdd);
	SOCKET _clientSock = INVALID_SOCKET;
	while (true)
	{
		_clientSock = accept(_sock, (sockaddr*)&clientAdd, &addLen);
		if (INVALID_SOCKET == _clientSock)
		{
			printf("无效客户端\n");
		}
		printf("new client: %s", inet_ntoa(clientAdd.sin_addr));
		// 5. 

		send(_clientSock, msgBuffer, strlen(msgBuffer) + 1, 0);
	}
	

	// 6. 
	closesocket(_sock);
	//-----------------------//
	WSACleanup();
	return 0;
}