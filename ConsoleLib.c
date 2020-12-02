/* -*- coding: utf-8 -*-
 *======================================================================
 * ��Ȩ    :  one-ccs ��Ȩ���� (C) All rights reserved.
 * �ļ���  :  ConsoleLib.c
 * ����    :  ʵ�� ConsoleLib.h �ж���ĺ���
 * ����    :  2020-01-04
 * ����    :  one-ccs
 * ����    :  one-ccs@foxmail.com
 * ����    :  www.one-ccs.club

 * �޸ļ�¼:
 *----------------------------------------------------------------------
 *  �汾     ����          ����          �޸�����
 *
 *====================================================================*/
#include "ConsoleLib.h"

void CL_SetTitle(const char *title) {
    /**
     *  ���ÿ���̨���ڱ���
     */
    SetConsoleTitle(title);
}

void CL_SetColor(const int color) {
    /**
     *  0x(����)(����)
     *  SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );
     */
    HANDLE hStdOut;        // ��׼���(����̨) ���

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

BOOL CL_SetPosition(const int x, const int y) {
    /**
     *  ���ù�� ����
     */
    HANDLE hStdOut;        // ��׼���(����̨) ���

    COORD pos = {x, y};
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleCursorPosition(hStdOut, pos);
}

void CL_GetPosition(COORD * outCoord) {
    /**
     *  ��õ�ǰ���λ��
     */
    HANDLE hStdOut;        // ��׼���(����̨) ���
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;		// ����̨������Ϣ�ṹ��

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);	// ��ÿ���̨������Ϣ
    outCoord -> X = consoleInfo.dwCursorPosition.X;
    outCoord -> Y = consoleInfo.dwCursorPosition.Y;
}

//void GetMousePosition(COORD * outCoord) {
//    // ��ȡ��� ����
//    COORD pos = {x, y};
//    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hStdOut, pos);
//}

void CL_Filler(const int origin_x, const int origin_y, const int cols, const int lines, const char * filler) {
    /**
     * ��ԭ�� (origin_x, origin_y) ��ʼ����ӡ cols �� lines ��, �ַ� filler
     */
    COORD oldPos;
    int i, j;

    // ��õ�ǰ�������
    CL_GetPosition(&oldPos);
    for(i = 0; i < lines; i++) {
        /* �ú��������ַ�Ϊ����̨Ĭ�����ã�����ע�����һ��������
        ʹ��(���ʵ��Ϊ NULL ִ�к������)����ϸ��Ϣ�뿴�������*/
        //FillConsoleOutputCharacter(hStdOut, filler, cols, coord, NULL);
        CL_SetPosition(origin_x, origin_y + i);
        for(j = 0; j < cols; j++) {
            printf("%s", filler);
        }
    }
    // ��ԭ�������
    CL_SetPosition(oldPos.X, oldPos.Y);
}

BOOL CL_SetSize(const int cols, const int lines) {
	/**
	 * ���ÿ���̨���ڴ�С
	 */

    HANDLE hStdOut;       								   // ��׼���(����̨) ���
    SMALL_RECT rc = {0, 0, cols - 1, lines - 1};;		   // ���ڴ�С����
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
	 * ���ÿ���̨��������С
	 */

    HANDLE hStdOut;
    COORD coord = {cols, lines};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleScreenBufferSize(hStdOut, coord);
}

BOOL __cdecl CL_ColorPrint(const int color, const char * format, ...) {
	/*
	 * ��ָ����ɫ��ӡ�ı�
	 */
	HANDLE hStdOut = NULL;
	CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBufferInfo; 			// ����̨��Ϣ
	WORD wDefaultColor = 0;											// �޸�ǰ������ɫ����
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
     * ���ô���ȫ����ʾ
     */
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);
    //printf("cx:%d,cy:%d\n", cx, cy);
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);

    // ���ô�����Ϣ ��� ȡ�����������߿�
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    CL_SetSize(cx, cy);

    // ���ô���λ�ü���С
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

    // �Կո����
	for(i = 0; str[i]; i++) {
		if(str[i] != ' ') {
			alpha++;
			if(alpha == 1) {
				area[area_count++].start = i;
			}
			if(str[i+1] == 0) {
				// ������Ϊ�ַ���ĩβ 
                area[area_count-1].count = (i + 1) - area[area_count-1].start;
			}
		}
		else {
			if(alpha) {
				alpha = 0;
				area[area_count-1].count = i - area[area_count-1].start;
			}
		}
	}// �������
	
	//������������ (�������־����ֵ)
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
	}// �������� ������� 

    // ��ȡ����ؼ��� �� ����ֵ
    for(i = 0; i < 8 && i < key_count; i++) {
    	STR str_t;
    	strcpy(str_t, str);
		// ��ȡ�ؼ���
        strncpy(cmd[i].key, (str_t + cmd_area[i][0].start), cmd_area[i][0].count);
        cmd[i].key[cmd_area[i][0].count] = '\0';
        // ��ȡֵ
		if(cmd_area[i][1].count > 0) {
			strncpy(cmd[i].value, (str_t + cmd_area[i][1].start), cmd_area[i][1].count);
        	cmd[i].value[cmd_area[i][1].count] = '\0';
		}
    }// ��ȡ���

    return TRUE;
}
/**
 * FillConsoleOutputCharacter�ĺ��������ǣ�
 *
 * BOOL WINAPI FillConsoleOutputCharacter(
 *   _In_   HANDLE hConsoleOutput,
 *   _In_   TCHAR cCharacter,
 *   _In_   DWORD nLength,
 *   _In_   COORD dwWriteCoord,
 *   _Out_  LPDWORD lpNumberOfCharsWritten
 * );
 *
 *     ���һ�������Ǵ洢���ؽ���ģ���ʾд����Ļ�����ʵ���ַ�����Ȼ��
 * ������LPDWORD����һ��ָ��DWORD�ĳ�ָ��(����16λʣ��Ĳ���)��ʵ�ʾ���
 * һ��DWORD��ָ�룬DWORD��ʾ32λ�������ֱ������DWORD����������һ��32
 * λ�ı���(����int)��ϣ��������Ͷ������á�
 *
 * �ο����ӣ�https://zhidao.baidu.com/question/134665660922620605.html
 */
