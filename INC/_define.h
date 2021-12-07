/* 
 파 일 명 : _define.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :   
 가    정 : 
 저 자 명 : Lee, DW 
 변 경 자 : CWLEE, 조철희
 변경내용 : (목적)
 변경일시 : 98. 7. 15.
           `98. 8. 25.	Rxc -> RDF 
           `98. 9. 3    _spScnDfltLvl 추가 
           `98. 9. 7    _bitObj* 변경  
           `98. 9. 7    _spKSPNewEMTNum 추가
           `98. 9. 9    _spBitNorm, _spBitError 추가
           				BIT Result Bit-Mask 정의 추가   
           `98. 9. 17   #define _spRdfInitDelay(2Sec) 추가
                        #define prc_ISR(15), _spBdISR(15), _spBdCnfISR(0xF00) 추가
           `98. 9. 22   _spPrcInfDelay 를 1초에서 1.5초로 변경
           `98. 9. 24   _spPrcInfDelay 를 1.5초에서 1초로 변경
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 : 
 출력정의 : 
 관련모듈 : 
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 : 
*****************************************************************************************/

#ifndef _DEFINE_H_
#define _DEFINE_H_

enum { _spZero=0, _spOne, _spTwo, _spThree, _spFour } ;

enum { WHITE=0, BLACK, RED, GREEN, BLUE, BROWN, SKY, YELLOW, CYAN } ;

#define ONE_SEC             20000000			// 1 sec  / 50 ns */
#define ONE_MILLISEC        (ONE_SEC/1000)		// 1 msec / 50 ns */
#define ONE_MICROSEC        (ONE_MILLISEC/1000)	// 1 usec / 50 ns */

// Scan Anal. Level Definition, ScanAnalRange
//##ModelId=42757D4B0250
enum { _spNoScan=0, _spScanType, _spScanAnalRSA, _spScanAnalReq } ;

#define		prc_All						0

/////////////////////////////////////////////////////////////////////////////////////////
//  시스템 마크로 정의 
// 
#define		CASE							break;case
#define		DEFAULT						break;default

/////////////////////////////////////////////////////////////////////////////////////////
//  RSA 외부장치 정의  
// 
#define		_inPRC						0x000
#define		_etCCU						0x001	/* OCU */
#define		_etPMC						0x002	/* JSM */
#define		_etRDF						0x003	/* 수신기 RXDF */	//`98.8.25
#define		_etCPT						0x004	/* OCU+JSM */		//'98.9.3

/////////////////////////////////////////////////////////////////////////////////////////
//  In Init SRAM, Memory Pattern
// 
#define		XSH_MODE					0x58534820	// "XSH "
#define		BOOT_MODE					0x424f4f54  // "BOOT"

/////////////////////////////////////////////////////////////////////////////////////////
//  In Init SRAM, Memory Pattern
// 
#define		PATTERN_A					0xaaaaaaaa
#define		PATTERN_0					0x00000000

/////////////////////////////////////////////////////////////////////////////////////////
//  RSA 시스템 운용 모드 정의  
// 
/* 시스템 모드 */
#define		_oprSysPO					0x0		/* 전원 인가시 초기값 */
#define		_oprSysES					0x1		/* ES 모드 */ 
#define		_oprSysEW					0x2		/* EW 모드  */
#define		_oprSysRD					0x3		/* 모드 */

/* Operation mode of RSA */
#define		_waitConnect			0x1		/* 전원 인가시 초기값 */
#define		_connectLan				0x2		/* 전원 인가시 초기값 */
#define		_setMode					0x3		/* ES 모드 */ 
#define		_startSys					0x4		/* EW 모드  */
#define		_startIPL					0x5		/* 모드 */
#define		_downloadIPL			0x6		/* 모드 */

/* Operation mode of RXDF */
#define		_reqBitSys				0x1
#define		_echoBitSys				0x2
#define		_readyRxdf				0x0

/* RSA 동작 모드 */
#define		_oprBOOT					0x010		/* 전원 인가시 초기값 */
#define		_oprINIT					0x011		/* 초기화 모드 */ 
#define		_oprIBIT					0x012		/* IBIT 모드  */
#define		_oprSBIT					0x013		/* SBIT 모드 */
#define		_oprUBIT					0x014		/* SBIT 모드 */
#define		_oprCBIT					0x015		/* SBIT 모드 */
#define		_oprRUN						0x016		/* 정상 신호 분석 모드 */	
#define		_oprSTOP					0x017		/* 시스템 중단 모드 */	
#define		_oprHALT					0x018		/* 시스템 종료 모드 */	
#define		_oprRESTART				0x019		/* 시스템 재시작 모드 */	
#define		_oprReady					0x01a		// ready status
#define		_oprRXDF					0x01b

/* RSA 동작 대기 모드 */
#define		_waitRsaInit			0x020		/* 시스템 종료 명령 대기 */
#define		_waitRunStart			0x023		/* 프로세서 분석 시작 명령 대기 */
#define		_waitRunStop			0x024		/* 프로세서 분석 종료 명령 대기 */
#define		_waitPrcHalt			0x025		/* 프로세서 종료 명령 대기 */
#define		_waitIplStart			0x026		/* IPL 다운로드 시작 명령 대기 */
#define		_waitIplDown			0x027		/* IPL 다운로드 시작 명령 대기 */
#define		_waitIplEnd				0x028		/* IPL 다운로드 종료 명령 대기 */
#define		_waitSubTest			0x029		/* 시스템 점검 모드 명령 대기 */
#define		_waitShutdown			0x02A		/* 시스템 종료 명령 대기 */

#define		_waitPrcInit			0x030		/* 프로세서 초기화 결과 대기 */
#define		_waitPrcIbit			0x031		/* 프로세서 IBIT 결과 대기 */
#define		_waitPrcCbit			0x032		/* 프로세서 CBIT 결과 대기 */
#define		_waitPrcSbit			0x033		/* 프로세서 SBIT 결과 대기 */

#define		_waitRdfInit			0x040		/* RxDF 초기화 결과 대기 */
#define		_waitRdfIbit			0x041		/* RxDF IBIT 결과 대기 */
#define		_waitRdfCbit			0x042		/* RxDF CBIT 결과 대기 */
#define		_waitRdfSbit			0x043		/* RxDF SBIT 결과 대기 */

#define		_resetSW					0x01		// Delete Anal & Oper Task
#define		_readyAnal				0x02		// create Anal & Oper Task

/////////////////////////////////////////////////////////////////////////////////////////
//   U-RBIT 대상 정의 : `99.9.7
// 
#define		_bitObjOru				1
#define		_bitObjPdfu				2
#define		_bitObjSdfu				3
#define		_bitObjTsd				4
#define		_bitObjB1sp				5
#define		_bitObjB2sp				6
#define		_bitObjB3sp				7
#define		_bitObjRsa				8

/////////////////////////////////////////////////////////////////////////////////////////
//   BIT Result Bit-Mask  정의 : `98.9.9
// 
#define		_bitRstMskEs			0x0007FFFF;
#define		_bitRstMskRsa			0x3F7FFFFF
#define		_bitRstMskCip			0x00000007
#define		_bitRstMskHw			0x000000C0
#define		_bitRstMskVol			0x07000000
#define		_bitRstMskSap			0x00000038
#define		_bitRstMskNsp			0x00000700
#define		_bitRstMskKsp1		0x00003800
#define		_bitRstMskKsp2		0x0001C800
#define		_bitRstMskKsp3		0x000E0000
#define		_bitRstMskKsp4		0x00700000
#define		_bitRstMskSio			0x38000000

#define		_bitRstMskRomni		0x00000007
#define		_bitRstMskRctrl		0x0007FFFF
#define		_bitRstMskRleft		0x0000001F
#define		_bitRstMskRright	0x0000001F
#define		_bitRstMskRshare	0x00000001

/////////////////////////////////////////////////////////////////////////////////////////
//   탐지 프로세서 시스템 파라메터 
// 
#define		_spMaxScPdw						1023	// pulse count is 10 bit
#define   _spMinAnalScn					140		// Scan Anal Min. Pulse count
#define   _spMinPulLobe					15		// Min. pulse # in main lobe
// #define		_spMaxTryScan			4		// Scan Max. trial step

#define		_spMaxTkPdw						1024
#define 	_spMaxNewTPDW					256
#define 	_spMaxThreatNum				8
#define		_spNMaxFreqGC					10		// 4 
#define   _spMaxMesgSize        255
#define   _spMaxEMTNum          256     // Before value is 256
#define   _spKSPNewEMTNum       256     // Maximum New AET number of KSP, 98. 09. 07
#define 	_spMaxNewPDW					256
#define 	_spMaxNewPulseGroup		11		// 5 
#define		_spMaxAoaGroup				24

#define		_spAmbiMax						60
#define		_spMaxTaskNum					256
#define		_spMaxQueueNum				_spMaxEMTNum
#define		_spMaxQueueSize				(_spMaxEMTNum+1)	// Maximum Queue size

#define   _spTkTimeRes          10      // 0.1 sec( res. 1s)
#define   _spScTimeRes          10      // 0.1 sec( res. 1s)

#define		_spAOABinSize					0x200

/////////////////////////////////////////////////////////////////////////////////////////
// 시스템 파라메터   
// 
#define		_spFirstPRIBand 				800		
#define		_spLastPRIBand 					409600 	

#define		_spBasePTCount					5		/* 5 */
#define		_spPTAcceptCount				8		/* 10 */
#define		_spSPRIAnalAcceptCount	12		/* 24 */
#define		_spJPRIAnalAcceptCount	12		/* 48 */
#define		_spDSPRIAcceptValue			3000	/* 150 us */
#define		_spDSPCount							500
#define		_spTOAtol								8		/* 0.4 us <- 1 us */
#define		_spMaxMultiplePRI				40		/* 2 us */
#define		_spBasePTRCount					4		
#define		_spTrkBasePTRCount			2		

#define		_spMaxSwtLev						16
#define		_spMaxCoRsaAmbi					30
#define		_spMaxCoSysAmbi					5

/////////////////////////////////////////////////////////////////////////////////////////
//   Tolerance  
// 
#define 	_spLargeTOAGab					0x00000190	/* 50ns(0x00000001), 200ms(0x003D0901) */
#define 	_spMaxTOATol						40000		/* 20 ms */

// #define		_spSpriTol				8		 	/* 0.4 us <- 2 us */
#define 	_spJpriTol							12			/* 0.5 us <- 2 us */
#define 	_spJtrPer								0.13
#define 	_spPRITol								40			/* 2000 ns */

/////////////////////////////////////////////////////////////////////////////////////////
//   주파수 밴드 및 영역 
// 
#define 	_spLFBand								0
#define 	_spMFBand								1
#define 	_spHFBand								2

#define 	_spLFBandLimit					0x0640		/* Decimal 1600 */
#define 	_spMFBandLimit					0x12C0 		/* Decimal 4800 */
#define 	_spHFBandLimit					0x3FFF 		/* Decimal 16400 */

/////////////////////////////////////////////////////////////////////////////////////////
//   PDW 시스템 제원 범위  
// 

#define 	_spAOAmax				0x3FF		// 359.6484375 Degree 	

// System Resolution Definition 
#define 	_spAOAres				0.351562	// Degree */
#define 	_spAMPres				0.3125		// dB */
#define 	_spTOAres				0.000000050	// SEC(50 ns) */
#define 	_spPWres				50.         // pw res.

// System Offser value, `99.05.17 */
#define		_spPAoffset				(-70)       // amplitude initial value */

#define 	_spTimeres             	20000000    // 1 sec / 50 ns */
#define 	_spOneSec              	_spTimeres	// 1 sec  / 50 ns */
#define 	_spOneMilli            	(_spOneSec/1000)  // 1 msec / 50 ns */
#define 	_spOneMicrosec         	(_spOneMilli/1000)
#define		_spDeltimeres			(10L)		//

#define		_spOverToa				200000		// 0.2 sec
	
/////////////////////////////////////////////////////////////////////////////////////////
//  주파수/방위 윈도우 크기 
// 
#define 	_spLowFrqTol				3		/* Accuracy 1 	3/1.25=2.4(3x1.25=3.75)	*/
#define 	_spMidFrqTol				5		/* Accuracy 2 	6/1.25=4.8(5x1.25=6.25) */
#define 	_spHghFrqTol				8		/* Accuracy 3 	9/1.25=7.2(8x1.25=10)   */
#define 	_spLowAoaTol				20		/* Accuracy 4.5	13.5/0.703125=19.2(20)	*/
#define 	_spMidAoaTol				13		/* Accuracy 3   9/0.703125=12.3(13)	*/
#define 	_spHghAoaTol				9		/* Accuracy 2   6/0.703125=8.53(9)	*/

//		for Emitter Merge table, tolerance of direction regardless of band
#define		_spMgTblTolAoa				30
/* #define		_spMgTblTolAoa				_max(_max( _spMgAoaLow, _spMgAoaMid ), _spMgAoaHgh ) */

//		SBIT AET count
#define     _spSBitAet              3

/////////////////////////////////////////////////////////////////////////////////////////
//  시스템 기본 플래그 
// 
#define 	_spTrue            	 	1
#define 	_spFalse           	 	0
#define 	_spPass             	0			// modified from  1, 99.05.03
#define 	_spFail             	-1			// modified form -1, 99.05.03
#define		_spNoTimeout			0L
#define 	_spKnown				1
#define 	_spUnknown          	0
#define 	_spNone			    	-1
#define 	_spMark					-1
#define 	_spUnMark				512 		/* Equal to _spMaxEMTNum */
#define		_spNoMark				-512
#define		_spFlagSet				1
#define		_spFlagReset			0
#define		_spNull					0			
#define		_spPlus					1
#define		_spMinus				-1
#define		_spEnable				1
#define		_spDisable				0
#define		_spBitNorm				0			// Added `98.9.9
#define		_spBitError				1			// Added `98.9.9
#define		_spBitUnknown			2			// Added `98.9.9
#define		_spInitTime				(-1)

#define   _spEndCollect			(-1)
#define		_spFifoEmpty			(-2)		// 추적, 스캔 FIFOEMPTY 값

/////////////////////////////////////////////////////////////////////////////////////////
//  definition Freq. range in associated IPL
// 
#define   _spIplMaxNum            2100

#define		_spFreqMax				18000000	// 주파수 최대 값
#define   _spFreqMin    			500000      // 주파수 최소 값

#define		_spFiplBand				32			// 주파수 밴드 개수
#define   _spFhistRes             90000       // 9 MHz 의 Histogram res.

/////////////////////////////////////////////////////////////////////////////////////////
//  definition maximum value of each var. type
// 
#define		_spMaxVal08				0xff
#define		_spMaxVal32				0xffffffff

#define		_spMaxAetCount			(50000)	// 개수는 ((-1)-추적최대수집개수) 보다 적어야한다.

/////////////////////////////////////////////////////////////////////////////////////////
//  Max Overlapped Emitter
// 
#define		_spOverlapCoEMT			_spMaxEMTNum

/////////////////////////////////////////////////////////////////////////////////////////
//  Maximu Scan Anal,. step
// 
#define     _spMaxTryScan           5
#define     _spMaxEffTryScan        4

/////////////////////////////////////////////////////////////////////////////////////////
//  definition maximum value of each var. type
// 
#define		_spBkCmpAnalThr			10			// threshold count of comp. anal count

#define		_spWarning				(-10)		// threshold count of comp. anal count

/////////////////////////////////////////////////////////////////////////////////////////
//  definition of window cell's valid or invalid 
// 
#define		_spInvChannel			(-5)		// threshold count of comp. anal count
#define		_spInvAET				(-1)		// threshold count of comp. anal count

#define		_spFixedOverlapRatio	(0.05)		// 5 % ratio of total space
#define		_spAgileOverlapRatio	(0.15)		// 5 % ratio of total space

/////////////////////////////////////////////////////////////////////////////////////////
// COM_AET's control varibles definition
//
// enum KSP_ANAL { CompleteAnal=0, SimpleAnal } ;
// KSP_ANAL 
//##ModelId=42757D4B026F
enum { PrecStag=0, PrecFrqPat, PrecPriPat } ;
// KSP_SAP_STEP
//##ModelId=42757D4B028D
enum { _spSetWinC=1, _spColStep, _spAnlStep, _spCotStep, _spScnEnd=0, _spTrkEnd=0 } ;

// Standard Track WinCell's pulsecount and timeout

#define     _spCWTo                 3
#define     _spCWPc                 50          // CW's pulse count

#define     _spChirpPc              50
#define     _spChirpTo              3

#define     _spNormPc               150         // Normal AET's time out
#define     _spAbnormPc             256			// Normal AET's time out, debug 200->256

/////////////////////////////////////////////////////////////////////////////////////////
//  definition of Track + Scan Result Info's status valuse
// 
// #define		_spInsPul				1			// Insufficency of Pulse
// #define		_spScnSuc				2			// Scan's result sucess
// #define		_spScnFal				3			// Scan's result fail
// #define		_spUpdSuc				0
// #define		_spLost					1

/////////////////////////////////////////////////////////////////////////////////////////
//  definition of Scan Status value
// 
#define		_spRsaScn				1
#define		_spReqScn				2

/////////////////////////////////////////////////////////////////////////////////////////
//  definition of Scan Anal.
// 
#define 	_spHistRes				( 100 * ONE_MICROSEC )  // 펄스열의 DTOA res. 의 히스토그램

/////////////////////////////////////////////////////////////////////////////////////////
//  definition maximum check KSP's DM
// 
#define		_spCoKSP				4

/////////////////////////////////////////////////////////////////////////////////////////
//  에미터 Category  
// 
#define 	catUnknown				0x00
#define 	catAir					0x01
#define 	catSurface				0x02
#define 	catSubsurface			0x03
#define	 	catLand					0x04

/////////////////////////////////////////////////////////////////////////////////////////
//  시그날 타입   
// 

/////////////////////////////////////////////////////////////////////////////////////////
//  PRI 패턴 타입  
// 
#define		ppSine					0x01
#define		ppSawPls				0x02
#define		ppSawMns				0x03
#define 	ppDwlSwt				0x04

/////////////////////////////////////////////////////////////////////////////////////////
//  스캔 분석 상태  
// 
#define		ssRsaUndo				0x00
#define		ssRsaSucc				0x01
#define		ssRsaFail				0x02
#define		ssOcuSucc				0x03
#define		ssOcuFail				0x04

/////////////////////////////////////////////////////////////////////////////////////////
//  에미터 생존 상태 
// 
#define 	esNEW               	0x01
#define 	esSTUDY_ASP				0x02
#define 	esSTUDY_FSP				0x03
#define 	esSTUDY_PRI				0x04
#define		esTRACK					0x05
#define 	esSLEEPING          	0x06
#define 	esAWAKE             	0x07
#define 	esLOST              	0x08
#define 	esDYING             	0x09

/////////////////////////////////////////////////////////////////////////////////////////
//  RSA 타스크 우선순위 정의  
// 
#define		tp_Self					0
#define		tp_RC					5
#define		tp_Main					9

//	Common Task Id & pririty in NSP/KSP/SAP
#define		tp_MngTsk				10
#define		tp_RcvPrc				30
#define		tp_SndPrc				60
#define		tp_RunBit				70			// change RcvSIO task's pri

//	CIP Task for Control & Analysis
#define		tp_RcvLan				20
#define		tp_RcvSIO				80
#define		tp_SndLan				40
#define		tp_SndSIO				50
#define		tp_CtlTrk				90
#define		tp_IdtAet				100
#define		tp_CreAet				110
#define		tp_CtlLst				120
#define		tp_MdyDat				105
#define		tp_MdyAet				130

//	BIT Task
//#define		tp_TstBit				75
#define		tp_TstBit				85
#define		tp_MxxBit				84
#define		tp_Snd232				40

//	NSP, KSP, SAP Task for Analysis
#define		tp_MngScn				130		// only Scan Task

#define		tp_GthSig			 	170
#define		tp_AnlSig				150
#define		tp_ExtPul				160		// only Scan Task
#define		tp_HGtSig			 	140		// in KSP, SAP for Collecting control

/////////////////////////////////////////////////////////////////////////////////////////
//  RSA 타스크간 통신을 위한 시스템 큐 ID 정의  
// 
#define		_spOneQSize				1
#define		_spSysQSize				(_spMaxEMTNum*2)

#define		SQ_DrvTsk				10
#define		SQ_MngTsk				11
#define		SQ_BitMan				11
#define		SQ_RcvPrc				13
#define		SQ_SndPrc				16
#define		SQ_RunBit				18
#define		SQ_InRBit				19		// inner run bit
#define		SQ_Ready				20

// #define		SQ_RcvSIO				14
#define		SQ_SndLan				17
#define		SQ_SndSIO				15
#define		SQ_RcvSIO				14
#define		SQ_CtlTrk				29
#define		SQ_IdtAet				20
#define		SQ_CreAet				21
#define		SQ_CtlLst				22
#define		SQ_MdyAet				23
#define		SQ_MxxBit				24

#define		SQ_GthSig			 	34
#define		SQ_AnlSig				35
#define		SQ_MngScn				33		// only Scan Task
#define		SQ_ExtPul				36		// only Scan Task

#define     _spNoMaxTask            32
#define     _spCoMaxSysQueue        64
#define     _spCoSbc                7
#define		_spCoMaxCh								32			// IBIT result for filter channel, 99.05.03

#define     prc_ISR                 14          // for _inPRC Time-out `98.9.17, from 15 '98.9.22
#define     _spBdISR                15          // for _etRDF Time-out `98.9.17
#define     _spBdCnfISR             0xF00       // for _etOCU Time-out `98.9.17
#define     _spPrcInitDelay         20000000     // before 1 sec(1000000), `98.9.22
												// before 1 sec(1500000), `98.9.24
#define     _spPrcSAPUBitDelay      6000000     // 00-05-29 14:10:59
#define     _spPrcNSPUBitDelay      3000000     // 00-05-29 14:10:59
#define     _spPrcKSPUBitDelay      11000000	// 00-05-29 14:10:59

#define     _spPrcSBitDelay         (11000000)  // 11 sec
#define     _spPrcSBitNSPDelay      (1000000)   // 1.2 sec
#define     _spPrcSBitSAPDelay      (5000000)   // 3.5 sec -> 4.0 sec, 99-12-09
#define     _spPrcSBitKSPDelay      2000000     // 1.2 sec
#define     _spRdfIBitDelay         (2000000)   // 2 sec, 비트용 시험을 위해서 변~경
#define     _spRdfCBitDelay         (2000000+1000000)   // 3 sec, 비트용 시험을 위해서 변~경
// #define     _spRdfSBitDelay         (10000000)   // 10 sec, 비트용 시험을 위해서 변경
// debug, 00-02-11 16:36:02
#define     _spRdfSBitDelay         (12000000)   // 12 sec, 비트용 시험을 위해서 변경
// #define     _spRdfUBitDelay         (30000000)     // 30 sec, 비트용 시험을 위해서 ~변경
#define     _spRdfUBitDelay         (45000000)     // 45 sec, debug, 0-04-19 21:41:45
#define     _spRdfEchoDelay         (900000) // 0.9 sec, 비트용 시험을 위해서 변경
#define     _spRdfEchoDelay2        (3000000) // 3 sec, 비트용 시험을 위해서 변경
#define     _spMaxDelay         	(31000000)     // 30 sec, 비트용 시험을 위해서 ~변경

/////////////////////////////////////////////////////////////////////////////////////////
//  사용자 수신금지 영역 셀 개수 
// 
#define     _spMaxUsrIhbSize        9

/////////////////////////////////////////////////////////////////////////////////////////
//  프로세서간 메시지 수신을 위한 세마포 
// 
#define		_spMsgSemaId			100 

/////////////////////////////////////////////////////////////////////////////////////////
//  스캔 분석 Threat Level Default 값 정의  `98.9.3
// 
#define		_spScnDfltLvl			5 

#endif

