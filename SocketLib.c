/* -*- coding: utf-8 -*-
 *======================================================================
 * 版权    :  one-ccs 版权所有 (C) All rights reserved.
 * 文件名  :  SocketLib.h
 * 描述    :  实现 SocketLib.h 中定义的函数
 * 日期    :  2020-07-02
 * 作者    :  one-ccs
 * 邮箱    :  one-ccs@foxmail.com
 * 官网    :  www.one-ccs.club

 * 修改记录:
 *----------------------------------------------------------------------
 *  版本     日期          作者          修改内容
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

	//初始化winsock版本2.2
    if((Ret = WSAStartup(wVersion, &wsaData)) != 0)
    {
        //如果winsock没有加载，调用WSAStartup()函数将会返回一个SOCKET_ERROR的错误代码
        printf("WSAStartup failed with error %d\n", Ret);
        return FALSE;
    }

    // 创建套接字
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 初始化 接口
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port= htons(Port);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 绑定 套接字与接口
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
	
	// 开启监听 
	listen(server, 5);
	
	// 等待连接 
	NewConnection = accept(server, (SOCKADDR *)&ClientAddr, &ClientAddrLen);

    return NewConnection;
}

BOOL SL_CreateClient(SOCKET *client, const IP ip, const int Port) {
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 2);
    SOCKADDR_IN Addr;
    int Port_t = Port;
    int Ret;

	//初始化winsock版本2.2
    if((Ret = WSAStartup(wVersion, &wsaData)) != 0)
    {
        //如果winsock没有加载，调用WSAStartup()函数将会返回一个SOCKET_ERROR的错误代码
        printf("WSAStartup failed with error %d\n", Ret);
        return FALSE;
    }

    // 创建套接字
    *client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 初始化 接口
	Addr.sin_family = AF_INET;
	Addr.sin_port= htons(Port_t);
	Addr.sin_addr.s_addr = inet_addr(ip);

	// 建立连接
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
	send(*client, "客户端已连接.", 13, 0);

    return TRUE;
}

BOOL SL_GetLocalIp(IP ip) {
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	int Ret;

	//初始化winsock版本2.2
    if((Ret = WSAStartup(wVersion, &wsaData)) != 0)
    {
        //如果winsock没有加载，调用WSAStartup()函数将会返回一个SOCKET_ERROR的错误代码
        printf("WSAStartup failed with error %d\n", Ret);
        return FALSE;
    }

	struct hostent *phostinfo = gethostbyname("");
	char *p = inet_ntoa (* ((struct in_addr *)(*phostinfo->h_addr_list)));
	strncpy(ip, p, 15);
	ip[15] = '\0';

	if(WSACleanup() == SOCKET_ERROR)
    {
		//WSACleanup()函数可以释放所有由winsock分配的资源，并取消这个应用程序挂起的winsock调用
        printf("WSACleanup failed with error %d\n", WSAGetLastError());
    }

	return TRUE;
}
