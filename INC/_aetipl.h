/****************************************************************************************
 파 일 명 : _aetipl.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :   
 가    정 : 
 저 자 명 : Jo Churl-hee
 변 경 자 : 
 변경내용 : (목적)
 변경일시 : 99-04-06 1:52오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 : 
 출력정의 : 
 관련모듈 : 
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 : 
*****************************************************************************************/

#ifndef _AETIPL_H_
#define	_AETIPL_H_

#include <time.h>
#include <sys/types.h>

#define		Unknown		0
#define		UNKNOWN		Unknown

///////////////////////       AET DEFINES      /////////////////////////////////////////////

#include "_type.h"
#include "_define.h"

#include "../BSP/hw_str.h"

//##ModelId=42757D4B02A1
enum { BAND1=0, BAND2, BAND3, TOTAL_BAND };

// 신호 형태 정의값
//##ModelId=42757D4B02BF
enum { PULSE=1, CW, DOPPLER, HIGHPRF } ;
//##ModelId=42757D4B02DD
enum { _FIXED=1, _RANDOM_AGILE, _PATTERN_AGILE, _HOPPING, _CHIRP_UP, _CHIRP_DN, _PMOP, MaxFRQ } ;
//##ModelId=42757D4B02FB
enum { _STABLE=1, _STAGGER, _JITTER, _PATTERN, _DWELL, 
			 _PATTERN_STABLE, _PATTERN_STAGGER, _PATTERN_DWELL, _REFSTABLE, _STAGGER_DWELL, MaxPRI } ; // Id...
//##ModelId=42757D4B0319
enum { SINE=1, SAW_INC, SAW_DEC, MaxFPAT } ;		// same with PRI pattern type

/////////////////////////////////////////////////////////////////////////////////////////
// 안테나 스캔 형태 정의값
//##ModelId=42757D4B0337
enum { CIRCULAR=1, UNI_DIRECTIONAL, BI_DIRECTIONAL, CONICAL, STEADY, UFO, DetType } ;
//##ModelId=42757D4B0355
enum { NO_PROCESS=0, SELF_SUCCESS, SELF_FAIL, REQ_SUCCESS, REQ_FAIL, All_Sucess=1, All_Fail=6 } ;

/////////////////////////////////////////////////////////////////////////////////////////
// 기본 AET 구조
// 

#define     _spMaxSwtLev            16			// 주파수, PRI Stagger 단 개수
#define     _spMaxCoSysAmbi         5			// IPL의 Ambiguity 개수

/////////////////////////////////////////////////////////////////////////////////////////
//  LowHigh, MinMax 구조체
//
//##ModelId=43D4818D01EB
typedef struct {
	int		low;
	int		hgh;
} STR_LOWHIGH;
 
//##ModelId=43D4818D021D
typedef struct {
  int		low;
  int		hgh;
	int		band;
} STR_LHBAND;
 
//##ModelId=43D4818D0245
typedef struct {
	int mean;
	int min;
  int max;
} STR_MINMAX;

/* AET용 주파수 구조체 */
//##ModelId=43D4818D0277
typedef	struct
{
	int 	band;
	int 	type;
	int		mean;
	int 	min;
	int 	max;
	int 	patType;
	int		swtLev;
	int		swtVal[_spMaxSwtLev];
	int		patPrd;
} STR_FRQ;
	
/* AET용 PRI 구조체 */
//##ModelId=43D4818D029F
typedef	struct
{
	int 	type;
	int		mean;
	int 	min;
	int 	max;
	int 	patType;
	int 	jtrPer;
	int		swtLev;
	int		swtVal[_spMaxSwtLev];
	int		patPrd;
} STR_PRI;

/* AET용 SCAN 구조체 */
//##ModelId=43D4818D02C7
typedef	struct
{
	int		stat;
  int 	type;
	int 	prd;
} STR_AS;

/* AET용 SEEN TIME 구조체 */
//##ModelId=43D4818D02EF
typedef	struct
{
	time_t 	frst;
	time_t	last;
} STR_SEEN_TIME;

/* AET용 식별 구조체 */
//##ModelId=43D4818D0321
typedef struct
{
	int	coAmbi;
	UINT	noIPL[_spMaxCoSysAmbi];
} STR_SYSID;

/* AET */
//##ModelId=43D4818D0349
typedef struct {
	int 			noEMT;      // Emitter no.
	int				sigType;    // 1:PULSE, 2:CW, 3:DOPPLER, 4:HIGHPRF
	STR_FRQ			frq;        // 주파수 1:FIXED, 2:RANDOM_AGILE, 3:PATTERN_AGILE, 4:HOPPING, 5:CHIRP_UP, 6:CHIRP_DN, 7:PMOP
	STR_PRI			pri;        // PRI    1:STABLE, 2:STAGGER, 3:JITTER, 4:PATTERN, 5:DWELL
	STR_MINMAX		pw;         // 펄스폭
	STR_MINMAX		pa;			// moved the upper line on asp.
	STR_AS 			as;         // 안테나 스캔
	int aoa;        // 방향
	STR_SEEN_TIME	seen;       // 시간
	UINT 			priLev;     // 위협 레벨
	STR_SYSID		id;         // 식별 결과
	UINT			autoWarn;   // 
	UCHAR			elintNo[8]; // 
	UCHAR			name[20];
	UINT 			cat;
} STR_AET;

//##ModelId=43D4818D0371
typedef struct {
	UINT			coEMT;		// count of emitter
	UINT			inEMT[16];	// index of emitter
} STR_REF;

/////////////////////////////////////////////////////////////////////////////////////////
//   셀별 추적 정보  및 에미터 할당 정보
//
//##ModelId=43D4818D0399
typedef struct {
  BOOL valid;              // Is this channel valid or invcalid ?, only use gKsfInfo

  UINT noEMT;              // Emitter #
  UINT stAnal;             // Status of Analysis
  UINT priority;
  UINT noCh;               /* 할당된 추적기 번호 */
  UINT noFLT;
  UINT noPrc;
	UINT fAnal;				// Scan Lock-on,Coni/Cir.

	UINT coOvAET;				// counter of overlapped AET
  UINT inOvAET[_spOverlapCoEMT];

  UINT coAET;
  UINT ioAET[_spOverlapCoEMT];

  UINT coPrvPDW;           /* 이전 펄스 수집 요구 갯수 */
  UINT coCurPDW;           /* 현재 펄스 수집 요구 갯수 */
  UINT tmPrvTout;          /* 이전 펄스 수집 한계 시간 */
  UINT tmCurTout;          /* 현재 펄스 수집 한계 시간 */

  CELL_WORDS  	winCellword;		// in Cell_Word
 
  time_t t_update;   // Present time of update track filter
  time_t t_track;    // Duration time of tracking...
  time_t t_sleep;    // Duration time in track fail ...
  time_t t_prdTrack; // Track Sucess period
  time_t t_prdSleep; // Track Fail period

	// Track's Anal flag
	UINT fPrecStag;	// enum KSP_ANAL { PrecStag=0, PrecFrqPat, PrecPriPat } ;
	UINT fPrecFrqPat;
	UINT fPrecPriPat;

	//
	UINT coPrecStag;	
	UINT coPrecFrqPat;
	UINT coPrecPriPat;

	// Scan collecting step
	UINT fScStep;
	UINT paMin;

	//
	// Common var. 
  UINT CoTry;				// Total Track try #
  UINT CoFail;			// Total Track fail #
  UINT coTry;				// Track try #
  UINT coFail;			// Track fail #

  UINT noCol;				// collection pulse #
  UINT noExt;				// extration pulse #

	BOOL bEndCol;			// 수집 완료 플레그
} STR_CHINFTAB;

//##ModelId=43D4818D03CB
typedef struct {
	UINT			coMg;		// count of merge
	UINT			coHisto;
	UINT			frqHisto[5];
	UINT			priHisto[5];
} STR_MERGE;

//##ModelId=43D4818E001F
typedef struct {
    UINT			coAmbi;
    UINT			noIPL[_spMaxCoRsaAmbi];
} STR_RSAID;

//##ModelId=43D4818E0052
typedef struct {
	UINT			noCol;		// collection pulse #
	UINT			noExt;		// collection pulse # for Track

	UINT            stat;		// PDW's stat
	
	STR_LOWHIGH     aoa;

	UINT idxEmitter;				// m_Emitter의 인덱스

	UINT mark;							// 에미터 삭제 유무 플레그

//	STR_RANGE		merge;		// Range of Aet for AET Merge
//	STR_RANGE		filter;		// Window Cell(Track, Scan)
} STR_EXT ;

// in common memory, structure of extended aet 2
//##ModelId=43D4818E007A
typedef struct {
	UINT			noSerial;	// random variable
	UINT			noCol;		// collection pulse #

	STR_LOWHIGH		pulse;		// pulse # on process the KSP
	STR_REF			ref;		// reflect wave info.
	STR_CHINFTAB	ksp;		// track info.
	STR_CHINFTAB	sap;		// scan info.
	STR_MERGE		mg;			// merge info.
	STR_EXT			ext;		// paet info.
	STR_RSAID		id;
} STR_COMAET ;

// Emitter Merge Comparative History Info
//##ModelId=43D4818E00A2
typedef union {
	UCHAR w08;
	struct {
		UINT	 ft : 1;		// freq. type comparative result flag
		UINT	 pt : 1;		// pri type comparative result flag
		UINT	 st : 1;		// scan type comparative result flag
		UINT	 fm : 1;		// freq. margin comparative flag
		UINT	 pm : 1;		// pri margin comparative flag
		UINT	 sm : 1;		// scan margin compartive flag
		UINT	 am : 1;		// direction margin comparative flag
		UINT	 wm : 1;		// pulse-width margin comparative flag
	} mg ;

} STR_MG_HIST ;

//##ModelId=43D4818E00C0
typedef struct {
	UINT			frqType;	// When change the freq. type,
	UINT			priType;	// When change the pri type,
								// Stable & Stable's IPL type -> dwell
	UINT			frqVal;		// Stable becomes the New switch level
	UINT			priVal;		// Stable becomes the New switch level

	UINT			frqLev;		// Stable becomes the New switch level
	UINT			priLev;		// Stable becomes the New switch level
} STR_MG_STAT ;

//##ModelId=43D4818E00E8
typedef struct {
	UINT			coPulse;
	UINT			outTime;
	UINT			paMin;
} STR_LOST ;

// in local memory, structure of extended aet 1
//##ModelId=43D4818E0110
typedef struct {
	UINT stat;		// PDW's stat value
	STR_LOWHIGH aoa;

	UINT fNonWeighted;
	UINT noTotCol;
	UINT noExt;

	UINT fDetType;

	UINT idOver;		// Id's count over flag
  STR_RSAID id;
//	STR_MG_STAT		mgStat;

//	STR_RANGE		merge;		// Range of Aet for AET Merge
//	STR_RANGE		filter;		// Window Cell(Track, Scan)

	BOOL fCwTh;		// CW Control Flag's switch value
	UINT vCWThr;		// value of CWThreshold

	UINT noCh;		// Track Channel
	UINT noFLT;		// Track Filter #

	// 스캔과 관련된 플레그 및 정밀 분석
	UINT fScan;		// On Scan Flag
	UINT fAnal;
  BOOL fReqScan;

	// 초기화 하지 않아도 될 변수
	UINT coStep;
	UINT inStep[_spMaxTryScan];
	UINT coPulse[_spMaxTryScan];
	UINT stepAnal;	// 스캔 분석 단계
	UINT coReCol;

	UINT bScanSt;

	// Overlapped # AET list
  UINT coOvAET;                // counter of overlapped AET
  UINT inOvAET[_spOverlapCoEMT];

	UINT coAET;
	UINT ioAET[_spOverlapCoEMT];

	// 정밀 추적 플레그
	UINT			fFineTrk;
	time_t			tCmplTrk;

	// 추적/스캔 Lost 될때의 더하는 펄스 수 및 타임아웃 설정
	STR_LOST ksp;
	STR_LOST sap;

  // 신호 숨기 및 신호 삭제 플레그
  // 2005-05-04 2:07오후
  UINT bSigShow;

} STR_LOCAET ;

//##ModelId=43D4818E0142
typedef struct {				// New AET structure
	STR_AET aet;		// original AET
	STR_EXT	ext;		// exteded infomation of AET

} STR_NEWAET ;

//##ModelId=43D4818E0174
typedef struct {
	STR_AET aet;
  STR_CHINFTAB ksp;        // track info.

} STR_TRKAET ;

//##ModelId=43D4818E01D8
typedef struct {
	STR_AET	aet;
  STR_CHINFTAB sap;        // track info.

} STR_SCNAET ;

//##ModelId=43D4818E01F6
typedef struct {
  STR_AET oAet;           // orginal AET
  STR_EXT eAet;           // AET's common AET
 
} STR_MGAET ;

//##ModelId=43D4818E021E
typedef STR_NEWAET	STR_UPDAET;		// UPAET와 NEWAET는 동일구조 

//##ModelId=43D4818E0250
typedef struct {
    UINT        code;
    STR_AET     aet;
 
} STR_AETFLT ;

/////////////////////////////////////////////////////////////////////////////////////////
// 기본 IPL 구조
// 

/////////////////////////////////////////////////////////////////////////////////////////
//  COMMON MEMORY Flash-ROM 구성 
//
//	AM29F080-90EC( 1 M-Byte )
//	TOTAL SIZE  :  16 MB( 4-column x 4-row )
//	BANK SIZE   :   4 MB( 1MB/CHIP x 4 column )  
//	BANK No.    :   4 ( row )  
//	SECTOR SIZE : 256 KB( 64KB/CHIP x 4 )  
//	SECTOR No.  : 16/BANK, 64/TOTAL  
//
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	 Name			Address					BLOCK ADDRESS				SECTOR
//				from		to		D31~D24	D23~D16	D15~D8	D7~D0
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Bank 0	0x08000000	0x083FFFFF	Chip[0] Chip[1] Chip[2] Chip[3]		#0 ~ 15
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Bank 1	0x08400000	0x083FFFFF	Chip[0] Chip[1] Chip[2] Chip[3]		#16 ~ 31
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Bank 2	0x08000000	0x083FFFFF	Chip[0] Chip[1] Chip[2] Chip[3]		#32 ~ 47
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	Bank 3	0x08000000	0x083FFFFF	Chip[0] Chip[1] Chip[2] Chip[3]		#48 ~ 63
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
/////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
//  Flash-ROM Write 용 상수 정의 
//
/* Define Flash-ROM VMEbus Base Address */
#define ahwCMF_PgmBase		(ahwVME_CMF + 0x000000)		//0x08000000, Use for Program Download
#define ahwCMF_PgmLast		(ahwVME_CMF + 0xF00000)		//0x08F00000, 15MB
#define ahwCMF_IPLBase		(ahwVME_CMF + 0xF00000)		//0x08F00000, Use for IPL Download
#define ahwCMF_IPLLast		ahwVME_CMS					//0x09000000, 1MB
#define ahwCMF_SYSBase      (ahwVME_CMF + 0xEC0000)     //0x08F00000, Use for IPL Download

/* Define Flash-ROM Bank VMEbus Base Address Pointer */
#define phwCMF_Bank0		(UINT *)(ahwCMF_Bank0)
#define phwCMF_Bank1		(UINT *)(ahwCMF_Bank1)
#define phwCMF_Bank2		(UINT *)(ahwCMF_Bank2)
#define phwCMF_Bank3		(UINT *)(ahwCMF_Bank3)

/* Define Flash-ROM Byte(size 4bytes) Program Command Cycle */
#define FlsBytesProgCmd_1	0xAAAAAAAA
#define FlsBytesProgCmd_2	0x55555555
#define FlsBytesProgCmd_3	0xA0A0A0A0

/* Define Flash-ROM Sector(Size 256kbyte) Erase Command Cycle */
#define FlsSectEraseCmd_1	0xAAAAAAAA
#define FlsSectEraseCmd_2	0x55555555
#define FlsSectEraseCmd_3	0x80808080
#define FlsSectEraseCmd_4	0xAAAAAAAA
#define FlsSectEraseCmd_5	0x55555555
#define FlsSectEraseCmd_6	0x30303030

/* Define Flash-ROM Sector(256 KBytes) Size */
#define FlsSectSize_Byte	0x40000				// debug, for test
#define FlsSectSize_Uint	0x10000

/* Define Flash-ROM Bank(4 MBytes) Size */
#define FlsBankSize_Byte	0x400000
#define FlsBankSize_Uint	0x100000

/* IPL의 Flash-ROM Write Status Report 빈도 상수 정의 : IPL 100개 마다 Status 보고 */
#define	_spIplWriteRatio	10			// ratio of inc. write status
#define	_spIplWriteStatThr	40
#define	_spIplEraseStatThr	40
#define	_spIplWriteStatEnd	100

/* Flash ROM Write 후 대기 Loop 회수 정의 : 10, Normal 7 us에 Loop 회 정도면 Write 됨 */
#define _spMaxWriteWait		20

/* Flash ROM Blank Data 정의 */
#define _spBlankFlash		0xFFFFFFFF

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 주파수 구조체 
//
//##ModelId=43D4818E0296
typedef struct {
	UINT 	type;
	int		low; 
	int		hgh; 
	UINT	bw;
	UINT	patType;
	int		swtLev;
	int		dwLow[_spMaxSwtLev];
	int		dwHgh[_spMaxSwtLev];
	UINT	ppLow;
	UINT	ppHgh;
} IPL_FRQ;	

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 PRI 구조체 
//
//##ModelId=43D4818E02BE
typedef struct {
	UINT 	type;
	int		low; 
	int		hgh; 
	UINT	patType;
	UINT	jtrPer;
	int		swtLev;
	int		swtValLow[_spMaxSwtLev];
	int		swtValHgh[_spMaxSwtLev];
	UINT	ppLow;
	UINT	ppHgh;
} IPL_PRI;	
	
/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 LowHigh 구조체 
//
//##ModelId=43D4818E02FB
typedef struct
{
	int	low;
	int	hgh;
} IPL_LOWHGH;

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 스캔 구조체 
//
//##ModelId=43D4818E0323
typedef	struct 
{
	UINT	type;
	UINT	prdLow;
	UINT	prdHgh;
} IPL_AS;

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL용 platform 구조체 
//
//##ModelId=43D4818E0341
typedef	struct 
{
	UINT	noplat;
	UCHAR	platName[20];
} IPL_PLAT;		//추가 `98.8.25 

/////////////////////////////////////////////////////////////////////////////////////////
//  IPL 구조체 
//
#ifdef M68K
//##ModelId=43D4818E0373
typedef struct 
{
	UINT		noIPL;
	UINT		sigType;
	IPL_FRQ		frq;
	IPL_PRI		pri;
	IPL_LOWHGH	pw;
	IPL_AS		as;
	UINT		tmoDel;
	UINT		thrLev;
	UINT		autoWarn;
	UCHAR		elintNot[8];
	UCHAR		elintName[20];
	UINT		cat;
	UINT		thrERP;
    IPL_PLAT	platform[5];	// Modified `98.8.25 

	UINT		checksum;
} STR_IPL;

#else
typedef struct
{
    UINT        noIPL;
    int         sigType;
    IPL_FRQ     frq;
    IPL_PRI     pri;
    IPL_LOWHGH  pw;
    IPL_AS      as;
    UINT        tmoDel;
    UINT        thrLev;
    UINT        autoWarn;
    UCHAR       elintNot[8];
    UCHAR       elintName[20];
    UINT        cat;
    UINT        thrERP;
    IPL_PLAT    platform[5];    // Modified `98.8.25 
 
} STR_IPL;

#endif

#endif
