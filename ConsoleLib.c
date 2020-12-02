/* -*- coding: utf-8 -*-
 *======================================================================
 * 版权    :  one-ccs 版权所有 (C) All rights reserved.
 * 文件名  :  ConsoleLib.c
 * 描述    :  实现 ConsoleLib.h 中定义的函数
 * 日期    :  2020-01-04
 * 作者    :  one-ccs
 * 邮箱    :  one-ccs@foxmail.com
 * 官网    :  www.one-ccs.club

 * 修改记录:
 *----------------------------------------------------------------------
 *  版本     日期          作者          修改内容
 *
 *====================================================================*/
#include "ConsoleLib.h"

void CL_SetTitle(const char *title) {
    /**
     *  设置控制台窗口标题
     */
    SetConsoleTitle(title);
}

void CL_SetColor(const int color) {
    /**
     *  0x(背景)(字体)
     *  SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );
     */
    HANDLE hStdOut;        // 标准输出(控制台) 句柄

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

BOOL CL_SetPosition(const int x, const int y) {
    /**
     *  设置光标 坐标
     */
    HANDLE hStdOut;        // 标准输出(控制台) 句柄

    COORD pos = {x, y};
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleCursorPosition(hStdOut, pos);
}

void CL_GetPosition(COORD * outCoord) {
    /**
     *  获得当前光标位置
     */
    HANDLE hStdOut;        // 标准输出(控制台) 句柄
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;		// 控制台窗口信息结构体

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);	// 获得控制台窗口信息
    outCoord -> X = consoleInfo.dwCursorPosition.X;
    outCoord -> Y = consoleInfo.dwCursorPosition.Y;
}

//void GetMousePosition(COORD * outCoord) {
//    // 获取鼠标 坐标
//    COORD pos = {x, y};
//    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hStdOut, pos);
//}

void CL_Filler(const int origin_x, const int origin_y, const int cols, const int lines, const char * filler) {
    /**
     * 从原点 (origin_x, origin_y) 开始，打印 cols 列 lines 行, 字符 filler
     */
    COORD oldPos;
    int i, j;

    // 获得当前鼠标坐标
    CL_GetPosition(&oldPos);
    for(i = 0; i < lines; i++) {
        /* 该函数填充的字符为控制台默认设置，且请注意最后一个参数的
        使用(如果实参为 NULL 执行后会死掉)，详细信息请看代码最后。*/
        //FillConsoleOutputCharacter(hStdOut, filler, cols, coord, NULL);
        CL_SetPosition(origin_x, origin_y + i);
        for(j = 0; j < cols; j++) {
            printf("%s", filler);
        }
    }
    // 还原鼠标坐标
    CL_SetPosition(oldPos.X, oldPos.Y);
}

BOOL CL_SetSize(const int cols, const int lines) {
	/**
	 * 设置控制台窗口大小
	 */

    HANDLE hStdOut;       								   // 标准输出(控制台) 句柄
    SMALL_RECT rc = {0, 0, cols - 1, lines - 1};;		   // 窗口大小属性
    short result = FALSE;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (SetConsoleWindowInfo(hStdOut, TRUE, &rc)) {
    	// printf("Successed of set console size!");
    	result = TRUE;
    }
    else {
    	// printf("Failed of set console size!");
    	char com[64];
    	if(sprintf(com, "mode con: cols=%d lines=%d", cols, lines)){
	    	system(com);
			result = TRUE;
	    }
    }

    return result;
}

BOOL CL_SetBufferSize(const int cols, const int lines) {
	/**
	 * 设置控制台缓冲区大小
	 */

    HANDLE hStdOut;
    COORD coord = {cols, lines};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleScreenBufferSize(hStdOut, coord);
}

BOOL __cdecl CL_ColorPrint(const int color, const char * format, ...) {
	/*
	 * 按指定颜色打印文本
	 */
	HANDLE hStdOut = NULL;
	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo; 			// 控制台信息
	WORD wDefaultColor = 0;											// 修改前字体颜色属性
	reva_list arglist;
	reva_start (arglist, format);
	short result = FALSE;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(GetConsoleScreenBufferInfo(hStdOut, &ConsoleScreenBufferInfo)) {
		wDefaultColor = ConsoleScreenBufferInfo.wAttributes;
	}

	if(hStdOut) {
		SetConsoleTextAttribute(hStdOut, color);
		printf(format, reva_arg (arglist, int));
	}
	else {
		result = FALSE;
	}
	if(wDefaultColor) {
		SetConsoleTextAttribute(hStdOut, wDefaultColor);
		result = TRUE;
	}

	return result;
}

BOOL CL_SetFullScreen() {
    /**
     * 设置窗口全屏显示
     */
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);
    //printf("cx:%d,cy:%d\n", cx, cy);
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);

    // 设置窗口信息 最大化 取消标题栏及边框
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    CL_SetSize(cx, cy);

    // 设置窗口位置及大小
    // return MoveWindow(hwnd, 100, 100, x + 300, y + 300, FALSE);
    return SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy - 42, SWP_SHOWWINDOW);
}

BOOL CL_PrintModePictrue(const int origin_x, const int origin_y, const MODEP arr[], const int width, const int height) {
    int raw, col, t, count = 0;

    for(raw = 0; raw < height; raw++) {
        CL_SetPosition(origin_x, origin_y + raw);
        for(col = 0; col < width / 8; col++) {
            for(t = 0x80; t > 0; t >>= 1) {
                if(arr[count] & t) {
                    printf("*");
                }
                else {
                    printf(" ");
                }
                //Sleep(10);
            }
            count++;
        }
        printf("\n");
    }

    return TRUE;
}

BOOL CL_AnalyzeCmd(Cmd cmd[], const WORD cmd_len, const STR str) {
	Area area[16] = {0}, cmd_area[8][2] = {0};
	WORD area_count = 0, key_count = 0, alpha = 0;
	WORD i;

    // 以空格分组
	for(i = 0; str[i]; i++) {
		if(str[i] != ' ') {
			alpha++;
			if(alpha == 1) {
				area[area_count++].start = i;
			}
			if(str[i+1] == 0) {
				// 满足则为字符串末尾 
                area[area_count-1].count = (i + 1) - area[area_count-1].start;
			}
		}
		else {
			if(alpha) {
				alpha = 0;
				area[area_count-1].count = i - area[area_count-1].start;
			}
		}
	}// 分组完毕
	
	//分析命令区域 (含命令标志，和值)
	for(i = 0; i < area_count; i++) {
		if(str[area[i].start] == '-' || str[area[i].start] == '/') {
			cmd_area[key_count][0].start = area[i].start;
			cmd_area[key_count][0].count = area[i].count;
			if((i + 1) < area_count && str[area[i+1].start] != '-' && str[area[i+1].start] != '/') {
				cmd_area[key_count][1].start = area[i+1].start;
				cmd_area[key_count][1].count = area[i+1].count;
				i++;
			}
			key_count++;
		}
	}// 命令区域 分析完毕 

    // 提取命令关键字 及 附加值
    for(i = 0; i < 8 && i < key_count; i++) {
    	STR str_t;
    	strcpy(str_t, str);
		// 提取关键字
        strncpy(cmd[i].key, (str_t + cmd_area[i][0].start), cmd_area[i][0].count);
        cmd[i].key[cmd_area[i][0].count] = '\0';
        // 提取值
		if(cmd_area[i][1].count > 0) {
			strncpy(cmd[i].value, (str_t + cmd_area[i][1].start), cmd_area[i][1].count);
        	cmd[i].value[cmd_area[i][1].count] = '\0';
		}
    }// 提取完毕

    return TRUE;
}
/**
 * FillConsoleOutputCharacter的函数声明是：
 *
 * BOOL WINAPI FillConsoleOutputCharacter(
 *   _In_   HANDLE hConsoleOutput,
 *   _In_   TCHAR cCharacter,
 *   _In_   DWORD nLength,
 *   _In_   COORD dwWriteCoord,
 *   _Out_  LPDWORD lpNumberOfCharsWritten
 * );
 *
 *     最后一个参数是存储返回结果的，表示写入屏幕缓存的实际字符数。然后
 * 类型是LPDWORD，是一个指向DWORD的长指针(这是16位剩余的产物)，实际就是
 * 一个DWORD的指针，DWORD表示32位，你可以直接声明DWORD变量，或者一个32
 * 位的变量(比如int)。希望这个解释对你有用。
 *
 * 参考链接：https://zhidao.baidu.com/question/134665660922620605.html
 */
