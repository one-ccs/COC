#ifndef DATABASELIB_H_INCLUDED
#define DATABASELIB_H_INCLUDED

/* -*- coding: utf-8 -*-
 *======================================================================
 * ��Ȩ    :  one-ccs ��Ȩ���� (C) All rights reserved.
 * �ļ���  :  DatabaseLib.h
 * ����    :  C�������ݿ���ļ�
 * ����    :  2020-06-13
 * ����    :  one-ccs
 * ����    :  one-ccs@foxmail.com
 * ����    :  www.one-ccs.club

 * �޸ļ�¼:
 *----------------------------------------------------------------------
 *  �汾     ����          ����          �޸�����
 *
 *====================================================================*/
typedef struct _table {
    // ���ݿ��_�ṹ��

    char *TableName;
    char *Field[];
}Table;

int __cdecl CreateTable (const char *TableName, char *Field[], ...);

#endif // DATABASELIB_H_INCLUDED
