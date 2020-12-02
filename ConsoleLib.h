#ifndef CONSOLELIB_H_INCLUDED
#define CONSOLELIB_H_INCLUDED

/* -*- coding: utf-8 -*-
 *======================================================================
 * ��Ȩ    :  one-ccs ��Ȩ���� (C) All rights reserved.
 * �ļ���  :  ConsoleLib.h
 * ����    :  ����̨�ĳ��ò���������������ɫ�������ȣ�
 * ����    :  2020-01-04
 * ����    :  one-ccs
 * ����    :  one-ccs@foxmail.com
 * ����    :  www.one-ccs.club

 * �޸ļ�¼:
 *----------------------------------------------------------------------
 *  �汾     ����          ����          �޸�����
 *
 *====================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>

#define COLOR_DARK_BLACK   0X00
#define COLOR_DARK_BLUE    0X01
#define COLOR_COBALT_BLUE  0X03
#define COLOR_GREEN        0X02
#define COLOR_RED          0X04
#define COLOR_DARK_PURPLE  0X05
#define COLOR_YELLOW       0X06
#define COLOR_GRAY         0X07
#define COLOR_DARK_GRAY    0X08
#define COLOR_LAKEBLUE     0X09
#define COLOR_LIGHT_GREEN  0X0A
#define COLOR_LIGHT_BLUE   0X0B
#define COLOR_LIGHT_RED    0X0C
#define COLOR_PURPLE       0X0D
#define COLOR_LIGHT_YELLOW 0X0E
#define COLOR_WHILE        0X0F

#define MODEP char

//#ifndef WIN32
#define reva_list char*                                                         // ����ָ��
#define reva_start(ap, arg) (ap = (va_list)&arg + sizeof(arg))                  // ָ��ɱ�����ĵ�һ��������ַ
#define reva_arg(ap, type) (*(type*)((ap += sizeof(type)) - sizeof(type)))      // ָ��ɱ��������һ��������ַ
#define reva_end(ap) (ap = (va_list)0)                                          // ָ��� ��ֹҰָ��
//#else
//#include <windows.h>
//#endif // WIN32

typedef char STR[255];

typedef struct _cmd {
    STR key;
    STR value;
}Cmd;

typedef struct _Area{
	WORD start;
	WORD count;
}Area;

/* ���ÿ���̨���� */
void CL_SetTitle(const char *title);

/* �������ֱ���ɫ��ǰ��ɫ
 * 0 = ����    4 = ��ɫ    8 = ���    C = ǳ��
 * 1 = ����    5 = ����    9 = ����    D = ��ɫ
 * 2 = ��ɫ    6 = ����    A = ����    E = ǳ��
 * 3 = ����    7 = �Ұ�    B = ǳ��    F = ����*/
void CL_SetColor(const int color);

/* ���ù��λ�� */
BOOL CL_SetPosition(const int x, const int y);

/* ��ù��λ�� */
void CL_GetPosition(COORD * outCoord);

/* ������λ�� */
void CL_GetMousePosition(COORD * outCoord);

/* ��ָ���ַ����ָ���������� */
void CL_Filler(const int origin_x, const int origin_y, const int cols, const int lines, const char * filler);

/* ���ÿ���̨���ڴ�С */
BOOL CL_SetSize(const int cols, const int lines);

/* ���ÿ���̨��������С */
BOOL CL_SetBufferSize(const int cols, const int lines);

/* ��ָ����ɫ��ӡ�ı� */
BOOL __cdecl CL_ColorPrint(const int color, const char * format, ...);

/* ���ô���ȫ����ʾ */
BOOL CL_SetFullScreen();

/* ��ָ��ԭ�������ӡ ȡģ��ͼ�� */
BOOL CL_PrintModePictrue(const int origin_x, const int origin_y, const MODEP arr[], const int width, const int height);

/* �����ַ����е�����ؼ��� */
BOOL CL_AnalyzeCmd(Cmd cmd[], const WORD cmd_len, const STR str);

#endif // CONSOLELIB_H_INCLUDED
