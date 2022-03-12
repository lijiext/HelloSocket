#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<Windows.h>
#include<WinSock2.h>
#include<stdio.h>
// windows ƽ̨ʹ��ָ���Ŀ�
// #pragma comment(lib, "ws2_32.lib")

int main() {
	WORD ver = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(ver, &data);
	//---------------------------------
	// 1. �½� socket
	SOCKET _sock =  socket(AF_INET,SOCK_STREAM,0);
	// 2. ���ӷ�����
	if (INVALID_SOCKET == _sock)
	{
		printf("�ͻ��ˣ���Ч�� socket, ��������ʧ��\n");
	}
	else 
	{
		printf("�ͻ��ˣ����� scoket �ɹ�\n");
	}
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(8888); // �ֽ��� �޷���
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // ʹ�ñ�����ַ
	int ret = connect(_sock,(sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("�ͻ��ˣ�connect ʧ��\n");
	}
	else {
		printf("�ͻ��ˣ�connect �ɹ�\n");
	}
	// 3. recv ����
	char recvBuf[256] = {};
	int nlen = recv(_sock,recvBuf, 256, 0);
	if (nlen > 0)
	{
		printf("�ͻ��ˣ����յ����ݣ�%s\n", recvBuf);
	}
	// 4. close socket
	closesocket(_sock);
	//---------------------------------
	WSACleanup();
	getchar();
	return 0;
}