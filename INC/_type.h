/****************************************************************************************
 �� �� �� : _type.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ��    �� :   
 ��    �� : 
 �� �� �� : Jo Churl-hee
 �� �� �� : 
 ���泻�� : (����)
 �����Ͻ� : 99-05-03 4:33����
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 �Է����� : 
 ������� : 
 ���ø�� : 
 �ڷᱸ�� : (��������)
 ����ó��/���ͼ���:
 ������ �Ͻ� : 
*****************************************************************************************/

#ifndef _TYPE_H_
#define	_TYPE_H_

#include <stddef.h>
//#ifdef _WIN32
//#include <WINDEF.h>
//#else

/////////////////////////////////////////////////////////////////////////////////////////
//  ���̴� ¡ǥ�м���� �� ���� 
//

#define	TASK	void

#define TRUE 1
#define FALSE 0

#define USHRT	unsigned short
#define USHORT	unsigned short
#define	UINT	unsigned int
#define	DINT	int
#define ULONG	unsigned long
#define UCHAR	unsigned char
#define CHAR	char

#define	BOOL	int

//#ifndef BOOL_DEF
//typedef int bool;
//#endif

#define WORD32	unsigned int
#define WORD16	unsigned short
#define WORD08	unsigned char

#ifdef _WIN32
#define	RET_OK		1

#endif


//#endif

#endif	// #ifndef _TYPE_H_
