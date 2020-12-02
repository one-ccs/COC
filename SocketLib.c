/* -*- coding: utf-8 -*-
 *======================================================================
 * ��Ȩ    :  one-ccs ��Ȩ���� (C) All rights reserved.
 * �ļ���  :  SocketLib.h
 * ����    :  ʵ�� SocketLib.h �ж���ĺ���
 * ����    :  2020-07-02
 * ����    :  one-ccs
 * ����    :  one-ccs@foxmail.com
 * ����    :  www.one-ccs.club

 * �޸ļ�¼:
 *----------------------------------------------------------------------
 *  �汾     ����          ����          �޸�����
 *
 *====================================================================*/
#include "SocketLib.h"

SOCKET SL_CreateListener(SOCKET server, const int Port) {
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 2);
	SOCKET NewConnection;
	SOCKADDR_IN ServerAddr;
	SOCKADDR_IN ClientAddr;
	int ClientAddrLen = sizeof(ClientAddr);
	int Port_t = Port;
    int Ret;

	//��ʼ��winsock�汾2.2
    if((Ret = WSAStartup(wVersion, &wsaData)) != 0)
    {
        //���winsockû�м��أ�����WSAStartup()�������᷵��һ��SOCKET_ERROR�Ĵ������
        printf("WSAStartup failed with error %d\n", Ret);
        return FALSE;
    }

    // �����׽���
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // ��ʼ�� �ӿ�
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port= htons(Port);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// �� �׽�����ӿ�
	while(Ret = bind(server, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) != 0) {
		if(Ret == WSAEADDRINUSE) {
			ServerAddr.sin_port= htons(++Port_t);
		}
		else if(Ret == WSAEFAULT) {
			return FALSE;
		}
		
		if(Port_t == Port + 9) {
			return FALSE;
		}
	}
	
	// �������� 
	listen(server, 5);
	
	// �ȴ����� 
	NewConnection = accept(server, (SOCKADDR *)&ClientAddr, &ClientAddrLen);

    return NewConnection;
}

BOOL SL_CreateClient(SOCKET *client, const IP ip, const int Port) {
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 2);
    SOCKADDR_IN Addr;
    int Port_t = Port;
    int Ret;

	//��ʼ��winsock�汾2.2
    if((Ret = WSAStartup(wVersion, &wsaData)) != 0)
    {
        //���winsockû�м��أ�����WSAStartup()�������᷵��һ��SOCKET_ERROR�Ĵ������
        printf("WSAStartup failed with error %d\n", Ret);
        return FALSE;
    }

    // �����׽���
    *client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // ��ʼ�� �ӿ�
	Addr.sin_family = AF_INET;
	Addr.sin_port= htons(Port_t);
	Addr.sin_addr.s_addr = inet_addr(ip);

	// ��������
	while(Ret = connect(*client, (SOCKADDR *)&Addr, sizeof(Addr)) != 0) {
		if(Ret == WSAECONNREFUSED) {
			Addr.sin_port= htons(++Port_t);
		}
		else if(Ret == WSAETIMEDOUT) {
			return FALSE;
		}
		
		if(Port_t == Port + 9) {
			return FALSE;
		}
	}
	send(*client, "�ͻ���������.", 13, 0);

    return TRUE;
}

BOOL SL_GetLocalIp(IP ip) {
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	int Ret;

	//��ʼ��winsock�汾2.2
    if((Ret = WSAStartup(wVersion, &wsaData)) != 0)
    {
        //���winsockû�м��أ�����WSAStartup()�������᷵��һ��SOCKET_ERROR�Ĵ������
        printf("WSAStartup failed with error %d\n", Ret);
        return FALSE;
    }

	struct hostent *phostinfo = gethostbyname("");
	char *p = inet_ntoa (* ((struct in_addr *)(*phostinfo->h_addr_list)));
	strncpy(ip, p, 15);
	ip[15] = '\0';

	if(WSACleanup() == SOCKET_ERROR)
    {
		//WSACleanup()���������ͷ�������winsock�������Դ����ȡ�����Ӧ�ó�������winsock����
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
    }

	return TRUE;
}
