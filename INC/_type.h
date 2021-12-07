/****************************************************************************************
 파 일 명 : _type.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :   
 가    정 : 
 저 자 명 : Jo Churl-hee
 변 경 자 : 
 변경내용 : (목적)
 변경일시 : 99-05-03 4:33오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 : 
 출력정의 : 
 관련모듈 : 
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 : 
*****************************************************************************************/

#ifndef _TYPE_H_
#define	_TYPE_H_

#include <stddef.h>
//#ifdef _WIN32
//#include <WINDEF.h>
//#else

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 형 선언 
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
