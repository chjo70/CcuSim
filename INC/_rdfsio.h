/****************************************************************************************
 파 일 명 : _rdfsio.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :  수신방탐처리기 인터페이스 메시지 및 자료 구조 정의 
 가    정 : 
 저 자 명 : CWLEE
 변 경 자 : 조철희, 99-05-13 8:05오후
 변경내용 : (목적)
 변 경 일 :  98. 7. 14.
            `98.8.24 RSA <-> RXDF I/F
		    `98. 8. 27	gRdfCnfSet[3] 추가, gScanThtLvl 추가 
		    `98. 9. 1   _spNoRDF 3 추가, STR_RDF_RUN->init[3] 추가 
		    `98. 9. 3   _spDelayPort 추가, Message & RDF_CNF의 명칭 변경  
		    `98. 9. 7   send 4-Byte, receive 12-Byte for checksum from 3/8 Byte 변경 
		   				gRdfCnfCur[3] 추가, RDF_SBIT 추가 
		    `98. 9. 8   STR_RDF_RCV의 dfwd -> domni로 변경, gRdfCnfCur[3] 삭제 
			`98. 9. 9   Bit Value of Command Data, Mrdf_RBit 정의 수정 
			`98. 9. 15	SYS_RDF_RUN 의 initCmuRdf 추가 
            `98. 9. 17  SYS_RDF_RUN 의 initCmuRdf[3] 변경, _spBdOne 추가
 입력정의 : 
 출력정의 : 
 관련모듈 : 
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 : 
*****************************************************************************************/

#ifndef _RSFSIO_H_
#define _RSFSIO_H_

#ifdef M68K
#ifdef _VXWORKS_
#else
#include <compiler.h>
#include <sys/types.h>
#include <ifx/ifxvisi.h>
#endif

#endif

#define     Port0       0                   // RXDF Band 1
#define     Port1       1                   // RXDF Band 2
#define     Port2       2                   // RXDF Band 3

/////////////////////////////////////////////////////////////////////////////////////////
// 레이더 징표분석기 외부 수신방탐장치 메시지 정의 : RSA -> RXDF, 동일 OPCODE 사용함.
//	
// 
// in association with System
#define Mrdf_Reset			0x11	/* Tx Data 0 */

// in association with Bit
#define Mrdf_IBit			0x21	/* Tx Data 0 */
#define Mrdf_UBit			0x22	/* Tx Data 1 */
#define Mrdf_SBit			0x23	/* Tx Data 0 */
#define Mrdf_CBit			0x24	/* Tx Data 0 */

// in association with Set up RXDF
#define Mrdf_BandEnable		0x31	/* Tx Data 1 */
#define Mrdf_NotchFilter	0x32	/* Tx Data 2 */
#define Mrdf_FmopThreshold	0x33	/* Tx Data 1 */
#define Mrdf_PMOPThreshold	0x34	/* Tx Data 1 */
#define Mrdf_DCA			0x35	/* Tx Data 1 */
#define Mrdf_RxThreshold	0x36	/* Tx Data 1 */
#define Mrdf_RxAntOffset	0x37	/* Tx Data 1 */
#define Mrdf_EABlankingAttn	0x38	/* Tx Data 1 */
#define Mrdf_RxThresholdCW	0x3a	/* Tx Data 1 */
#define Mrdf_DV				0x3b	/* Tx Data 1 */

/////////////////////////////////////////////////////////////////////////////////////////
// 레이더 징표분석기 외부 수신방탐장치 메시지 정의 : RXDF -> RSA, 동일 OPCODE 사용함.
// 
#define Mrdf_Echo			0x11		/* Rx Data 1 */
#define Mrdf_Error			0x12		/* Rx Data 1 */

#define Erdf_IBit			Mrdf_IBit	/* Rx Data 1 */
#define Erdf_UBit			Mrdf_UBit	/* Rx Data 6 */
#define Erdf_SBit			Mrdf_SBit	/* Rx Data 2 */
#define Erdf_CBit			Mrdf_CBit	/* Rx Data 2 */

/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 외부 메시지 송신 데이터 정의 : RSA -> RXDF
// 
/* Bit Value of Command Data, Mrdf_RBit 4 */
#define RdfCmdRBit_Omni		0x01
#define RdfCmdRBit_Left		0x02
#define RdfCmdRBit_Right	0x04
#define RdfCmdRBit_Share	0x08	// `98.9.9
#define RdfCmdRBit_Ctrl		0x10	// `98.9.9
#define RdfCmdRBit_All		0xFF

/* Bit Value of Command Data, Mrdf_SBit 5 */
#define RdfCmdSBit_RFwd		0xF1
#define RdfCmdSBit_RAft		0xF2
#define RdfCmdSBit_LAft		0xF3
#define RdfCmdSBit_LFwd		0xF4
#define RdfCmdSBit_Norm		0x00

/* Bit value of Command Data, Mrdf_BandEn 11 */
#define RdfCmdRdDis_Norm	0x00
#define RdfCmdRdDis_Stop	0xFF

/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 외부 메시지 수신 데이터 정의 : RXDF -> RSA
// 
/* Bit Value of norm or error for Mrdf_ResetI 1 */
#define RdfRdReset_Norm		0
#define RdfRdReset_Error	1

/* Bitmap Value of norm or error for Mrdf_Status 2 */
#define RdfRdStatus_RUN  	1
#define RdfRdStatus_DONE 	0

/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 밴드 정의	`98.8.25
// 
#define _spBand1		1
#define _spBand2		2
#define _spBand3		3
#define _spBdAll		4
#define _spBand4		5	// SIO's port4 

#define _spNoRDF		3	// Added for setting pRdfRun->rCoLiveRdf on PRC_CheckSysInit `98.9.1 

#define _spBdOne        1   // Added for answer One Band `98.9.17

/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 통신 제어 파라메터 정의	`98.9.3
// 
#define _spDelayPort	20	// Added for setting Change Port Time Delay `98.9.3 


/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 외부 메시지 송신 구조 : RSA -> RXDF
// 데이터 4 바이트 사용 <- from 2 Byte for Checksum 	`98.9.7, `99.05.17
//
typedef union { 
    WORD08 sndB[4];
    struct {
        WORD32 opcode   : 8;
        WORD32 data     : 24;	// dummy
    } hd;	// 데이터 0 바이트 경우
    struct {
        WORD32        	: 8;
        WORD32 data08 	: 8;
        WORD32        	: 16;	// dummy
    } d1;	// 데이터 1 바이트 경우
    struct {
        WORD32        	: 8;
        WORD32 data16 	: 16;
        WORD32        	: 8;
    } d2;	// 데이터 2 바이트 경우
} STR_RDF_SND;

/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 외부 메시지 수신 구조 : RXDF -> RSA
// 데이터 12 바이트 사용 <- from 4 Byte for Checksum 	`98.9.7
//
typedef union { 
	UINT   rcvW;
    WORD08 rcvB[4];
    struct {
        WORD32 opcode   : 8;
        WORD32 data     : 24; 	// dummy 
		WORD32 			: 24;
    } hd;	
    struct {
        WORD32          : 8;
        WORD32 data08   : 8;
        WORD32 			:16;
//      WORD32          : 24; 	// dummy 
    } d1;	// 데이터 1 바이트 경우, I-BIT
    struct {
        WORD32          : 8;
        WORD32 data16   : 16;
        WORD32          : 8; 	// dummy 
//      WORD32          : 8; 	// dummy 
//      WORD32          : 8; 	// dummy 
//      WORD32          : 8; 	// dummy 
    } d2;	// 데이터 2 바이트 경우, C-BIT, S-RBIT
    struct {
        WORD32          : 8;
        WORD32 data24   : 24;
//      WORD32 			: 8;
//      WORD32 			: 8;
//      WORD32 			: 8;
    } d3;	// 데이터 2 바이트 경우, C-BIT, S-RBIT
} STR_RDF_RCV;

/////////////////////////////////////////////////////////////////////////////////////////
// 수신방탐장치 외부 메시지 수신 BIT-MAP 구조 : RXDF -> RSA
// 
/* Bitmap of Rx Mrdf_Status( 2 ) */
typedef union {
	int	w32;
	struct {
		int      : 29;
		int SBit : 1;
		int RBit : 1;
		int IBit : 1;
	} bits;
} RDF_STATUS;

/* Bitmap of Rx Mrdf_IBit( 3 ) */
typedef union {
	int w32;
	struct {
		int       : 27;
		int bSp   : 1;	/* 신호처리장치 */
		int bTsd  : 1;	/* 시험신호분배장치 */
		int bSdfu : 1;	/* 우현방향탐지장치 */
		int bPdfu : 1;	/* 좌현방향탐지장치 */
		int bOru  : 1;	/* 전방향수신장치 */
	} bits;
} RDF_IBIT;	

typedef RXDF_SBIT	RDF_SBIT;

/* Bitmap of Mrdf_CBit( 6 )*/
typedef union {
	int w32;
	struct {
		int		: 21;	// dummy
		int d10	: 1;	/* 신호처리장치 출력상태 */
		int d9	: 1;	/* 신호처리장치 입력상태 */
		int d8	: 1;	/* 방향탐지장치(우현) 자체점검용 스위치 상태 */
		int d7	: 1;	/* 방향탐지장치(우현) 습도 */
		int d6	: 1;	/* 방향탐지장치(우현) 온도 */
		int d5	: 1;	/* 방향탐지장치(좌현) 자체점검용 스위치 상태 */
		int d4	: 1;	/* 방향탐지장치(좌현) 습도 */
		int d3	: 1;	/* 방향탐지장치(좌현) 온도 */
		int d2	: 1;	/* 전방향수신장치 자체점검용 스위치 상태 */
		int d1	: 1;	/* 전방향수신장치 습도 */
		int d0	: 1;	/* 전방향수신장치 온도 */
	} bits;
} RDF_CBIT;

/* Bitmap of Mrdf_UBit( 6 )*/
typedef RXDF_UBIT	RDF_UBIT;

/* RDF CNF Setting 데이터 */
typedef struct
{
	int		mResetI;	// Reset Init 결과 정상:0,비정상:1 echo of Mrdf_Reset `98.9.7
	int		mLvlThr;	// 0x00 ~ 0xFF
	int		mCWLvlThr;	// for CW Control

	int		mFmpThr;	// 0x00 ~ 0xFF
	int		mPmpThr;	// 0x00 ~ 0xFF

	int		mAntOffLeft;	// 0x00 ~ 0xFF
	int		mAntOffRght;	// 0x00 ~ 0xFF

	int		mBlkAnt;	// 0x00 ~ 0xFF
	int		mNotFlt;	// 0x000 ~ 0xFFF
	int		mPinAtt;	// 0x00 ~ 0xFF
	int		mBandEn;	// Banden/dis En:0x00,Dis:0xFF
	int		mEcho;		// Echo message from any messages, `99.05.17
	int		mError;		// Error message of command message, `99.05.17

	int		mDV;
	int		mAOA;
} RDF_CNF;			// `98.8.25

/* RXDF 종합 데이터 */
typedef struct {
	RDF_STATUS	stat[3];	// B1, B2, B3
	RDF_IBIT	ibit[3];
	RDF_UBIT	ubit[3]; 
	RDF_SBIT	sbit[3];	// `98.9.7
	RDF_CBIT	cbit[3];
	RDF_CNF		xcnf[3];
    UINT		initCmuRdf[3];  // [3]<- 1 `98.9.17, Set from TSK_SysInit at rCoEchoRdf error `98.9.15
	UINT		rCoLiveRdf;		// Set from PRC_CheckSysInit at Msys_Init
	UINT		rCoEchoRdf;		// use to count for B1, B2 & B3 
	UINT		rCoEcho;

	BOOL		rTmOutFlag;		// use to Flag for Time-out Interrupt
	BOOL		rIgTmOutFlag1;
	BOOL		rIgTmOutFlag2;
	UINT		rMode[3];			// RXDF status

	UINT		fAlive[3];
} STR_RDF_RUN;		// `98.8.25

typedef struct {
    int         head;
    int         tail;
    STR_RDF_RCV rcv[_spMaxQueueSize];        // AET data of MaetNew
} STR_QUEUE_SIO ;

/////////////////////////////////////////////////////////////////////////////////////////
//
// Function definition
// BOOL QueueSIOIsFull( STR_QUEUE_SIO *pQueue );
// int QueueSIOAdd( STR_QUEUE_SIO *pQueue );
// int QueueSIODelete( STR_QUEUE_SIO *pQueue );
// BOOL QueueSIOIsEmpty( STR_QUEUE_SIO *pQueue );
// void QueueSIOCreate( STR_QUEUE_SIO *pQueue );

UINT SIO_CheckRxdfMsgSeqValid(STR_TSK_MSG tskMsg, STR_RDF_RCV *pRcvMsg );
UINT SIO_AnalRdfMsg(int noBand, STR_RDF_RCV *pRcvMsg);
UINT GetMode( UINT band );
void SetRxdfMode( UINT band, UINT val );
UINT GetRxdfMode( UINT band );
 
/////////////////////////////////////////////////////////////////////////////////////////
// 
// 
#ifdef _MAIN_
STR_RDF_RUN		gRdfRun;	/* CM내 RXDF 동작 및 BIT 구조체 포인터 변수 */	// `98.8.25

RDF_CNF          gRdfCnfSet[_spBand3];      // Set value to RXDF `98.8.27
 
int             gnoEfgSio;

#else

extern STR_RDF_RUN		gRdfRun;		/* CM내 RXDF 동작 및 BIT 구조체 포인터 변수 */	// `98.8.25

extern RDF_CNF   		gRdfCnfSet[_spBand3];      // Set value to RXDF `98.8.27
 
extern int      		gnoEfgSio;

#endif

#endif
