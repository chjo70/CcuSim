/****************************************************************************************
 파 일 명 : define.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :   
 가    정 : 
 저 자 명 : 조 철 희
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

#include "../hw_def.h"
#include "hw_str.h"

#include "_macro.h"
#include "_define.h"
#include "_type.h"
#include "_pdw.h"

#include "_aetipl.h"

#include "_struct.h"			// compile for CC, will return line

#include "_sysmsg.h"
#include "_system.h"
#include "_syserr.h"

#define _spBand1		1
#define _spBand2		2
#define _spBand3		3

#ifndef DEFINE_H_
#define	DEFINE_H_

#define	SERVER_IP				"127.0.0.1"
#define	RSA_IP					SERVER_IP
#define	PMC_IP					"150.150.48.230"

//#define	_spCcuTcpPort		6000
//#define	_spJsmTcpPort		6000
#define	_spCcuTcpPort		13050 // 13030
#define	_spJsmTcpPort		13050

//##ModelId=3C96D396017D
typedef struct {
	unsigned char test1;
	unsigned char test2;
	
} STR_TST_RESULT ;


#ifdef _MAIN_
FREQ_RESOL 			gFreqRes[4] = { {    0,     0, 0     } ,
			   	       				{    0,  2560, 0.625 } ,   /* LOW  FREQUENCY */
			           				{ 1280,  6400, 1.25  } ,   /* MID  FREQUENCY */
           		  	    			{ 5866, 18740, 1.5   } } ; /* HIGH FREQUENCY */

#else
extern FREQ_RESOL 			gFreqRes[4];
#endif

void MakeLanMsg( STR_LAN_MSG *pLanMsg, char *buff );

#endif
