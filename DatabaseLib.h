#ifndef DATABASELIB_H_INCLUDED
#define DATABASELIB_H_INCLUDED

/* -*- coding: utf-8 -*-
 *======================================================================
 * 版权    :  one-ccs 版权所有 (C) All rights reserved.
 * 文件名  :  DatabaseLib.h
 * 描述    :  C语言数据库库文件
 * 日期    :  2020-06-13
 * 作者    :  one-ccs
 * 邮箱    :  one-ccs@foxmail.com
 * 官网    :  www.one-ccs.club

 * 修改记录:
 *----------------------------------------------------------------------
 *  版本     日期          作者          修改内容
 *
 *====================================================================*/
typedef struct _table {
    // 数据库表_结构体

    char *TableName;
    char *Field[];
}Table;

int __cdecl CreateTable (const char *TableName, char *Field[], ...);

#endif // DATABASELIB_H_INCLUDED
