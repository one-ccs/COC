#ifndef SOCKETLIB_H_INCLUDED
#define SOCKETLIB_H_INCLUDED

/* -*- coding: utf-8 -*-
 *======================================================================
 * ��Ȩ    :  one-ccs ��Ȩ���� (C) All rights reserved.
 * �ļ���  :  SocketLib.h
 * ����    :  C�����׽��ֿ��ļ�
 * ����    :  2020-07-02
 * ����    :  one-ccs
 * ����    :  one-ccs@foxmail.com
 * ����    :  www.one-ccs.club

 * �޸ļ�¼:
 *----------------------------------------------------------------------
 *  �汾     ����          ����          �޸�����
 *
 *====================================================================*/
#include <stdio.h>
#include <winsock2.h>

typedef char IP[16];

SOCKET SL_CreateListener(SOCKET server, const int Port);
BOOL SL_CreateClient(SOCKET *client, const IP ip, const int Port);
BOOL SL_GetLocalIp(IP ip);

#endif // SOCKETLIB_H_INCLUDED
