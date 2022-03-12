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
	//---------------------------------
	// 1. 新建 socket
	SOCKET _sock =  socket(AF_INET,SOCK_STREAM,0);
	// 2. 连接服务器
	if (INVALID_SOCKET == _sock)
	{
		printf("客户端：无效的 socket, 建立连接失败\n");
	}
	else 
	{
		printf("客户端：建立 scoket 成功\n");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(8888); // 字节序 无符号
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // 使用本机地址
	int ret = connect(_sock,(sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("客户端：connect 失败\n");
	}
	else {
		printf("客户端：connect 成功\n");
	}
	// 3. recv 接受
	char recvBuf[256] = {};
	int nlen = recv(_sock,recvBuf, 256, 0);
	if (nlen > 0)
	{
		printf("客户端：接收到数据：%s\n", recvBuf);
	}
	// 4. close socket
	closesocket(_sock);
	//---------------------------------
	WSACleanup();
	getchar();
	return 0;
}