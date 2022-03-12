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
	// 1. 创建 socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// 2. 定义 socket 数据
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET; // 协议族
	_sin.sin_port = htons(8888); // 端口
	_sin.sin_addr.S_un.S_addr = INADDR_ANY; // inet_addr("127.0.0.1") // 绑定的网卡地址
	
	// 3. 绑定 scoket 和端口
	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)
	{
		printf("服务端：端口和 socket 绑定失败\n");
	}
	else {
		printf("服务端：socket 绑定成功\n");
	}
	listen(_sock,5); // 监听

	// 4. 尝试接受客户端 socket
	sockaddr_in clientAdd = {};
	int addLen = sizeof(clientAdd);
	SOCKET _clientSock = INVALID_SOCKET;
	while (true)
	{
		_clientSock = accept(_sock, (sockaddr*)&clientAdd, &addLen);
		if (INVALID_SOCKET == _clientSock)
		{
			printf("服务端：无效的客户端 scoket\n");
		}
		printf("服务端：新客户端连接: %s\n", inet_ntoa(clientAdd.sin_addr));
		// 5. 向客户端发送信息
		send(_clientSock, msgBuffer, strlen(msgBuffer) + 1, 0);
	}
	// 6. 关闭服务端 socket
	closesocket(_sock);
	//-----------------------//
	WSACleanup();
	return 0;
}