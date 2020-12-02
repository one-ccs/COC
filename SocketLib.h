#ifndef SOCKETLIB_H_INCLUDED
#define SOCKETLIB_H_INCLUDED

/* -*- coding: utf-8 -*-
 *======================================================================
 * 版权    :  one-ccs 版权所有 (C) All rights reserved.
 * 文件名  :  SocketLib.h
 * 描述    :  C语言套接字库文件
 * 日期    :  2020-07-02
 * 作者    :  one-ccs
 * 邮箱    :  one-ccs@foxmail.com
 * 官网    :  www.one-ccs.club

 * 修改记录:
 *----------------------------------------------------------------------
 *  版本     日期          作者          修改内容
 *
 *====================================================================*/
#include <stdio.h>
#include <winsock2.h>

typedef char IP[16];

SOCKET SL_CreateListener(SOCKET server, const int Port);
BOOL SL_CreateClient(SOCKET *client, const IP ip, const int Port);
BOOL SL_GetLocalIp(IP ip);

#endif // SOCKETLIB_H_INCLUDED
