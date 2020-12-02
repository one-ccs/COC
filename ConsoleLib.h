#ifndef CONSOLELIB_H_INCLUDED
#define CONSOLELIB_H_INCLUDED

/* -*- coding: utf-8 -*-
 *======================================================================
 * 版权    :  one-ccs 版权所有 (C) All rights reserved.
 * 文件名  :  ConsoleLib.h
 * 描述    :  控制台的常用操作（更改文字颜色、清屏等）
 * 日期    :  2020-01-04
 * 作者    :  one-ccs
 * 邮箱    :  one-ccs@foxmail.com
 * 官网    :  www.one-ccs.club

 * 修改记录:
 *----------------------------------------------------------------------
 *  版本     日期          作者          修改内容
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
#define reva_list char*                                                         // 参数指针
#define reva_start(ap, arg) (ap = (va_list)&arg + sizeof(arg))                  // 指向可变参数的第一个参数地址
#define reva_arg(ap, type) (*(type*)((ap += sizeof(type)) - sizeof(type)))      // 指向可变参数的下一个参数地址
#define reva_end(ap) (ap = (va_list)0)                                          // 指向空 防止野指针
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

/* 设置控制台标题 */
void CL_SetTitle(const char *title);

/* 设置文字背景色和前景色
 * 0 = 纯黑    4 = 红色    8 = 深灰    C = 浅红
 * 1 = 深蓝    5 = 深紫    9 = 湖蓝    D = 紫色
 * 2 = 绿色    6 = 土黄    A = 鲜绿    E = 浅黄
 * 3 = 钴蓝    7 = 灰白    B = 浅蓝    F = 纯白*/
void CL_SetColor(const int color);

/* 设置光标位置 */
BOOL CL_SetPosition(const int x, const int y);

/* 获得光标位置 */
void CL_GetPosition(COORD * outCoord);

/* 获得鼠标位置 */
void CL_GetMousePosition(COORD * outCoord);

/* 用指定字符填充指定矩形区域 */
void CL_Filler(const int origin_x, const int origin_y, const int cols, const int lines, const char * filler);

/* 设置控制台窗口大小 */
BOOL CL_SetSize(const int cols, const int lines);

/* 设置控制台缓冲区大小 */
BOOL CL_SetBufferSize(const int cols, const int lines);

/* 按指定颜色打印文本 */
BOOL __cdecl CL_ColorPrint(const int color, const char * format, ...);

/* 设置窗口全屏显示 */
BOOL CL_SetFullScreen();

/* 在指定原点坐标打印 取模的图像 */
BOOL CL_PrintModePictrue(const int origin_x, const int origin_y, const MODEP arr[], const int width, const int height);

/* 分析字符串中的命令关键字 */
BOOL CL_AnalyzeCmd(Cmd cmd[], const WORD cmd_len, const STR str);

#endif // CONSOLELIB_H_INCLUDED
