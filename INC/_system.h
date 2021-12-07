/****************************************************************************************
 파 일 명 : _system.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :   
 가    정 : 
 저 자 명 : Jo. Churl-hee
 변 경 자 : 
 변경내용 : (목적)
 변경일시 : 99-04-07 3:20오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 : 
 출력정의 : 
 관련모듈 : 
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 : 
*****************************************************************************************/

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/////////////////////////////////////////////////////////////////////////////////////////
//  for RSA configuration definition
//
#define		_spScnLev				6

/////////////////////////////////////////////////////////////////////////////////////////
//  for RXDF configuration definition
//
//	Band 1
#define		_spBd1LvlThr			IDIV( ( -54 - _spPAoffset ), _spAMPres )    // -54 dB
#define		_spBd1FmpThr			0x60
#define		_spBd1PmpThr			0x60
#define		_spBd1AntOffLeft		0x60
#define		_spBd1AntOffRght		0x60
#define		_spBd1BlkAnt			0x9090
#define		_spBd1NotFlt			0x60
#define		_spBd1PinAtt			0x60
#define		_spBd1BandEn			0x1

//	Band 2
#define		_spBd2LvlThr			IDIV( ( -53 - _spPAoffset ), _spAMPres )    // -53 dB
#define		_spBd2FmpThr			0x60
#define		_spBd2PmpThr			0x60
#define		_spBd2AntOffLeft		0x60
#define		_spBd2AntOffRght		0x60
#define		_spBd2BlkAnt			0x9090
#define		_spBd2NotFlt			0x60
#define		_spBd2PinAtt			0x60
#define		_spBd2BandEn			0x1

//	Band 3
#define		_spBd3LvlThr			IDIV( ( -52 - _spPAoffset ), _spAMPres )	// -52 dB
#define		_spBd3FmpThr			0x60
#define		_spBd3PmpThr			0x60
#define		_spBd3AntOffLeft		0x60
#define		_spBd3AntOffRght		0x60
#define		_spBd3BlkAnt			0x9090
#define		_spBd3NotFlt			0x60
#define		_spBd3PinAtt			0x60
#define		_spBd3BandEn			0x1

/////////////////////////////////////////////////////////////////////////////////////////
//  
//	RXDF Direction & Freq Error
#define		_spRxdfAoaLow			(UDIV( 8, _spAOAres ))			// 14( 8 deg. )
#define		_spRxdfAoaMid			(UDIV( 5., _spAOAres ))			// 9 ( 5 deg. )
#define		_spRxdfAoaHgh			(UDIV( 3.5, _spAOAres ))		// 6 ( 3.5 deg. )

#define		_spRxdfFrqLow			2			// about 1.25(2*0.625)MHz
#define		_spRxdfFrqMid			2			// about 2.5(2*1.25)MHz
#define		_spRxdfFrqHgh			2			// 3(2*1.5) MHz

/////////////////////////////////////////////////////////////////////////////////////////
//  
//	Stable Toa Tolerance
#define		_spSpriTol				10			// 500 ns

/////////////////////////////////////////////////////////////////////////////////////////
//  for Identify, system parameter definition
//	Identify for Freq.
// debug, 99-12-09 19:44:46
#define     _spIdFixFrqLow			_spRxdfFrqLow	
#define     _spIdFixFrqMid			_spRxdfFrqMid	
#define     _spIdFixFrqHgh			_spRxdfFrqHgh	

#define     _spIdAgileFrqLow		100			/* 0 dB */
#define     _spIdAgileFrqMid		100			/* 0 dB */
#define     _spIdAgileFrqHgh		100			/* 0 dB */

//  Period of Freq.
#define		_spIdFrqPrd						50
#define		_spIdPriPrd						50

//	Identify for PRI.
#define		_spIdPri							10		// PRI tolerance of Id.
#define		_spIplMaxJitPer				15		// Jitter PRI tolerance of Id.
																			// debug, 00-10-11 14:52:15
#define		_spIplMaxHopJitPer	20			// Hopping일때 최대 Jitter 율 허용값
																			// 2005-04-20 3:41오후

//	Identify for scan period
#define		_spIdScnPrd				0			// Scan period tolerance of Id.

/////////////////////////////////////////////////////////////////////////////////////////
//  for Merge, system parameter definition
//	Merge for direction
//	debug, 1 -> 3, 00-09-20 09:43:31
#define		_spMgAoaLow				(3*_spRxdfAoaLow)	// 4.922 deg.
#define		_spMgAoaMid				(3*_spRxdfAoaMid)	// 3.164 deg.
#define		_spMgAoaHgh				(3*_spRxdfAoaHgh)	// 2.109 deg.

//	Merge for Fixed freq.
//	debug, 1 -> 3, 00-09-20 09:43:31
#define		_spMgFixFrqLow			(3*_spRxdfFrqLow)	// 1.25 MHz
#define		_spMgFixFrqMid			(3*_spRxdfFrqMid)	// 2.5 MHz
#define		_spMgFixFrqHgh			(3*_spRxdfFrqHgh)	// 3.0 Mhz

//	Merge for Agile freq.
#define		_spMgAgileFrqMean		50			// 10% of (mean-mean) -> 50
#define		_spMgAgileFrqIn			20			// 20% of (min-min)
#define		_spMgAgileFrqOut		10			// 10% of (max-max)
#define		_spMgAgileFrqLowPat		(3*_spRxdfFrqLow)	// 10% of freq. low
#define		_spMgAgileFrqMidPat		(3*_spRxdfFrqMid)	// 10% of freq. mid
#define		_spMgAgileFrqHghPat		(3*_spRxdfFrqHgh)	// 10% of freq. hgh

// When modify the AET's freq and PRI, the tolerance freq. and pri value.
#define		_spMdAgileFrq			1000		// 1GHz(the difference of freq's max and min

//	Merge for PRI
#define		_spMgFixPri				(4*_spSpriTol)	// each Stable PRIs, merge, 1->4, debug, 00-09-20 09:43:31
#define		_spMgAgilePriMean		50			// 10% of (mean-mean) -> 50, debug 
#define		_spMgAgilePriIn			20			// 20% of (min-min)
#define		_spMgAgilePriOut		10			// 10% of (max-max)
#define		_spMgAgilePriPat		(4*_spSpriTol)	// 10% of freq. low

//	Merge for Period each Freq, PRI, and scan 
#define		_spMgFrqPrd				5			// 5% of period
#define		_spMgPriPrd				5			// 5% of period
#define		_spMgScnPrd				5			// 5% of period

//	Merge for Pattern Period
#define		_spMgJtrPer				4			// not use, from 99-07-23 13:37:55

#define		_spMgPW					100			// not use, from 99-07-23 13:47:44
//	Merge for Pulsewidth

#define		_spMdyMethod			2			// 2 -> 3

/////////////////////////////////////////////////////////////////////////////////////////
//  for tracking Info
//
// debug, 00-08-30 14:02:57
#define		_spFtFixFrqLow			(2*_spRxdfFrqLow)		// debug, 1 -> 4, 05년 이전 값은 4로 함. 
#define		_spFtFixFrqMid			(2*_spRxdfFrqMid)		// 연평도에서 Stable, Jitter 운용하는 함정 때문에 
#define		_spFtFixFrqHgh			(2*_spRxdfFrqHgh)		// 4 -> 2로 수정함.

#define		_spFtAgiFrqLow			(3*_spRxdfFrqLow)		// debug, 00-01-31 16:13:18
#define		_spFtAgiFrqMid			(3*_spRxdfFrqMid)		// debug, 00-01-31 16:13:18
#define		_spFtAgiFrqHgh			(3*_spRxdfFrqHgh)		// debug, 00-01-31 16:13:18
#define		_spFtAgiRatio				10									// debug, 00-04-19 17:46:13

#define		_spFtPw							1000

#define		_spFtPa							5

#define		_spFtAoaLow					(_spRxdfAoaLow*5)
#define		_spFtAoaMid					(_spRxdfAoaMid*5)
#define		_spFtAoaHgh					(_spRxdfAoaHgh*5)

#define		_spMaxTimesAsScan		(1.8)			// 1.5 -> 3 -> 1.8(Lee) times of scan period, 99-10-27 11:08:24
#define		_spTimesAsPulsePerPrd	(5)

//  debug, 00-04-12 11:14:06
#define		_spPdwFrqLowLow			0x031c	//  0.49812 GHz
#define		_spPdwFrqLowHgh			0x0c80	//  2.0000 GHz
#define		_spPdwFrqMidLow			0x023d	//  1.9975 GHz
#define		_spPdwFrqMidHgh			0x0ec0	//  6.0000 GHz
#define		_spPdwFrqHghLow			0x0056	//  5.9965 GHz
#define		_spPdwFrqHghHgh			0x1f9a	// 18.00400 GHz

// Track Windwo Cell's pulse count & time out for maximum and minimum
#define		_spPdwTkToLow				0x1
#define		_spPdwTkToHgh				0xf0
#define		_spPdwTkPcLow				50
#define		_spPdwTkPcHgh				500

//#define		_spScToStep1			30			// res. 10 ms, 300 ms
//#define		_spScToStep2			600			// 6.0 sec
//#define		_spScToStep3			1500		// 15 sec
//#define		_spScToStep4			3000		// 30 sec
//#define		_spScToStep5			7000		// 70 sec
// debug, 00-09-02 02:21:39
#define		_spScToStep1			600			// res. 10 ms, 600 ms
#define		_spScToStep2			1500		// 15.0 sec
#define		_spScToStep3			3000		// 30 sec
#define		_spScToStep4			7000		// 70 sec
#define		_spScToStep5			_spMaxVal32		// 70 sec

//#define		_spScToStep1			70			// 
//#define		_spScToStep2			700			// 
//#define		_spScToStep3			7000		// 
//#define		_spScToStep4			7000		// 

#define		_spScMinTimeOutiOfPrd	(3.5)		// 3.5 배의 스캔주기 타임 아웃

#define		_spPdwPWLow				0x0000
#define		_spPdwPWHgh				0x07ff

#define		_spPdwPALow				0x0000
#define		_spPdwPAHgh				0x00ff

/////////////////////////////////////////////////////////////////////////////////////////
//  system parameter structure
//
#define		_spDelayScanStart			(1.5)		// times of ?

/////////////////////////////////////////////////////////////////////////////////////////
//  Minimum delete time
//
#define		_spDefaultDelTime			(10)
#define		_spMinDelTime					(1)
#define		_spMinDelTimeInCir		(10)

/////////////////////////////////////////////////////////////////////////////////////////
//  Track Anal Fail Count
//
#define     _spCoPrecStag       5
#define     _spCoPrecFrqPat     5
#define     _spCoPrecPriPat     5

/////////////////////////////////////////////////////////////////////////////////////////
//  Sending update minimum time
//
#define		_spUpdMinTimeTrk			1			// less than 1 sec
#define		_spUpdMinTimeNon			20			// less than 20 sec

/////////////////////////////////////////////////////////////////////////////////////////
//  Scan system parametes
//
#define		_spSampleTimeStep2		UMUL(  10, _spOneMilli )
#define		_spSampleTimeStep3		UMUL(  25, _spOneMilli )
#define		_spSampleTimeStep4		UMUL(  50, _spOneMilli )
#define		_spSampleTimeStep5		UMUL( 100, _spOneMilli )

#define		_spOffSampleStep1			100
#define		_spOffSampleStep2			20
#define		_spOffSampleStep3			8
#define		_spOffSampleStep4			4
#define		_spOffSampleStep5			2

#define		_spThresholdOfTrkSig	UMUL( 100, _spOneMilli )

#define		_spCoNonWeighted			(10)

#define		_spIncThr							UDIV( 8, _spAMPres )		// 02-08-11

/////////////////////////////////////////////////////////////////////////////////////////
// debug, 2004-04-13, Jo
#define     _spAnalMinPulseCount							6

#define			_spContiThresholdMinPulseCount		10

#define			_spAnalMinPulseStableEmitter			20		// Stable 에미터 최소 펄스 개수(누락 및 스캔 신호를 고려한)
#define			_spAnalMinPulseJitterEmitter			20

// 2005-07-05 7:56오후
#define     _spMaxAoaQueueSize								4

/////////////////////////////////////////////////////////////////////////////////////////
//  RF AOA margin
//

/////////////////////////////////////////////////////////////////////////////////////////
//  system parameter data structure
//
//##ModelId=43D4818A0178
typedef struct {
	UINT	mode;

} STR_CT ;

//##ModelId=43D4818A0196
typedef struct {
	UINT	aoadiff[4];
	UINT	frqdiff[4];

} STR_SP;

//##ModelId=43D4818A01B4
typedef struct {
	UINT	fixfrq[4];		// frq tol.
	UINT	agifrq[4];		// frq tol.
	UINT	pri;			// pri tol.
	UINT	prd;			// scan tol.

	UINT	frqPrd;			// When Pattern Agile, comparative period val.
	UINT	priPrd;			// When PRI Pattern, comparative period val.

} STR_ID ;

//##ModelId=43D4818A01E6
typedef struct {
//	UINT	mode;
	UINT	aoa[4];

	UINT	fixfrq[4];		// fixed/fixed, fixed/hopping, hopping/hopping
	UINT	agifrqmean;		// agile/agile, agile/pattern
	UINT	agifrqin;		// agile/agile, agile/pattern
	UINT	agifrqout;		// agile/agile, agile/pattern
	UINT	agifrqpat[4];	// pattern/pattern
	UINT	md_agifrq[4];	// debug, 00-01-31 16:35:43

	UINT	fixpri;			// stable PRI.
	UINT	agiprimean;		// agile/agile, agile/pattern
	UINT	agipriin;		// agile/agile, agile/pattern
	UINT	agipriout;		// agile/agile, agile/pattern
	UINT	agipripat;	// pattern/pattern

	UINT	frqPrd;			// When Pattern Agile, comparative period val.
	UINT	priPrd;			// When PRI Pattern, comparative period val.
	
	UINT	scnPrd;			// When scan is sucessful, comparative period val.

	UINT	jtrper;			// PRI jitter %

	UINT	pw;				// PRI jitter %

	UINT	mdyMethod;		// Method of modify parameter, debug, 00-08-31 10:19:35

} STR_MG ;

//##ModelId=43D4818A0204
typedef struct {
	UINT	aoa[4];

	UINT	fixfrq[4];
	UINT	agifrq[4];
	UINT	agiratio;		//  debug, 00-04-19 17:46:13

//	UINT	pw;				// PW
//	UINT	pa;

	UINT	CWTo;
	UINT	CWPc;

	UINT	normPc;
	UINT	abnormPc;

	UINT	chirpTo;
	UINT	chirpPc;

	float	maxTim;			// as times as scan period for collecting time out
	UINT	timPrd;			// as times as scan period for collecting pulse count

	STR_LOWHIGH	tkto;		// Track Timeout
	STR_LOWHIGH	tkpc;		// Track Pulse count

	UINT		scto[_spMaxTryScan+1];

} STR_FT ;

//##ModelId=43D4818A0222
typedef struct {
	STR_LOWHIGH		frq[4];
} STR_FG ;

//##ModelId=43D4818A0240
typedef struct {
    UINT    Pdw_Max;            // 수집 PDW 최대수
  	UINT    Aoa_Shift_Cnt;      // 방위 히스토 BIN 크기 = 2^N
    UINT    Aoa_Peak_Thr;       // 방위 히스토그램 PEAK 임계값  // 00.02.09
    UINT    Aoa_Hist_Thr;       // 방위 히스토그램 범위 임계값  // 00.02.09
    UINT    Aoa_Range_Margin;   // 방위 그룹 범위 margin
 
    UINT    Freq_Shift_Cnt;     // 주파수 히스토 BIN 크기 = 2^N
    UINT    Freq_Peak_Thr;      // 주파수 히스토그램 PEAK 임계값    // 00.02.09
    UINT    Freq_Hist_Thr;      // 주파수 히스토그램 범위 임계값    // 00.02.09
    UINT    Freq_Range_Margin;  // 주파수 그룹 범위 margin
   
    UINT    Rpt_Aet_Cnt;    // 탐지; 하나의 그룹에서 REPORT될 AET의 개수를 선언
 
} STR_NP ;

//##ModelId=43D4818A025F
typedef struct {
    UINT    Pdw_Max;            // 수집 PDW 최대수
/*  UINT    Aoa_Shift_Cnt;      // 방위 히스토 BIN 크기 = 2^N
    UINT    Aoa_Peak_Thr;       // 방위 히스토그램 PEAK 임계값  // 00.02.09
    UINT    Aoa_Hist_Thr;       // 방위 히스토그램 범위 임계값  // 00.02.09
    UINT    Aoa_Range_Margin;   // 방위 그룹 범위 margin
 
    UINT    Freq_Shift_Cnt;     // 주파수 히스토 BIN 크기 = 2^N
    UINT    Freq_Peak_Thr;      // 주파수 히스토그램 PEAK 임계값    // 00.02.09
    UINT    Freq_Hist_Thr;      // 주파수 히스토그램 범위 임계값    // 00.02.09
    UINT    Freq_Range_Margin;  // 주파수 그룹 범위 margin
*/
 
    UINT    Rpt_Aet_Cnt;    // 추적; 하나의 그룹에서 REPORT될 AET의 개수를 선언
 
} STR_KP ;

//##ModelId=43D4818A027D
typedef struct {
    UINT    Cw_Min_Cnt;         // CW신호를 분석하기 위한 최소 CW개수
 
    UINT    Mpc;                //000223 // Stable 펄스열의 최소 펄스수 (Min. Pulse Count)
    UINT    Mjpc;               //000223 // Jitter 펄스열의 최소 펄스수 (Min. Jitter Pulse Count)
    UINT    Rpc;                // 기준 펄스열의 펄스수 (Reference Pule Count)
    UINT    Rjgpc;              // 000404  Jitter Stagger 기준펄스열의 최소 펄스수 (Min. Jitter Stagger Pulse Count)
 
    UINT    Stb_Max_Miss;       // 최대 허용 STABLE MISS 개수
    UINT    Jit_Max_Miss;       // 최대 허용 JITTER MISS 개수
 
    UINT    Reflex_Zone;        // 반사파 처리 구간
    UINT    Hprf_First_Pri;     // 반사파처리 이전에 High PRF부터 처리
 
    UINT    Jitter_P;           // 최대 탐지 jitter %  990226
 
    UINT    Dtoa_Sd;            // 500ns / (50 ns) MEAN ERROR
    UINT    Freq_Sd;            // low : 1.5 / (0.5MHz), mid : 3.75 / (1.25MHz), High : 4.5 / (1.5MHz)
 
 
    UINT    Jstg_Pt_P;          // Jitter Stagger분석에서 Stagger로 추출된 펄스수의 비율 경계, 이상이~면 Stagger로 판정
    UINT    Jit_Merge_Miss_Cnt; // 최대 허용 병합 JITTER MISS 개수
 
    // 패턴 분석
    UINT    Pat_Min_Cnt;        // 패턴 분석에 필요한 최소 펄스수
    UINT    Lhp;                // Least Half Period 최소 반주기 펄스수
    UINT    Cross_Over;         // 패턴에서 LHP동안 평균을 가로지르는 최대 회수
    UINT    Lhp_Thresh;         // 패턴 확인에 사용되는 최소반주기의 회수
    UINT    Bad_Max;            // 패턴 확인에서 최대 bad 회수
    UINT    Filt_Fac;           // Filtering Factor 패턴 파라메터 평균배열(filt[])을 만들때 평균을 취~하는 신호수
    UINT    Maxparam_Min;       // 평균배열(filt[])의 최대값의 최소한의 수
    UINT    Pp_Max_Margin_P;    // 패턴주기 검증에서 사용되는 최대값의 margin %
//  UINT    Pp_Bin_Cnt;         // 패턴주기 구하기용 Histogram Bin 수
    UINT    Pp_Match_P;         // 패턴주기 구하기에서 패턴비교에서 성공비율
//  UINT    Pp_Pri_Match_Margin;    // 패턴주기 검증에서 PRI mean error margin (1us)
//  UINT    Pp_Freq_Match_Margin;   // 패턴주기 검증에서 FREQ mean error margin (2.5 5 6 MHz)
 
    // MAKE AET
    UINT    Conti_Thr;          // 연속성 최대 지수
    UINT    Rpt_Pul_Cnt;        // 이 값 이상의 펄스수의 AET는 무조건 REPORT 대상
 
} STR_CM ;
 
//##ModelId=43D4818A029B
typedef struct {
  UINT            Pdw_Max;            // 수집 PDW 최대수
  UINT            st[_spMaxTryScan];
  UINT            offst[_spMaxTryScan];

  UINT            thtrkprd;
 
} STR_SC;

//##ModelId=43D4818A02B9
typedef struct {
  UINT        mode;

  UINT        ver[2];
  UINT        date;
 
	// Control system parameters
	UINT		scnLev;		// 6

	STR_SP		sp;

	STR_FG		pw;			// Antenna Freq. range

//	STR_ID		id;
	STR_MG		mg;
	STR_FT		ft;

  // 탐지 system parameters
  STR_NP      np;

  // 추적 system parameters
  STR_KP      kp;

  // 공통(Common) system parameters
  STR_CM      cm;

  // 스캔(SAP) system parameters
  STR_SC      sc;

} STR_SYS ;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_

STR_SYS		_sp;

// Update AOA threshold
UINT	_sprfaoa[4] = { 0, 2*_spRxdfAoaLow, 2*_spRxdfAoaMid, 2*_spRxdfAoaHgh } ;

// 에미터로 인지하는 값 
UINT	_spdiffaoa[4] = { 0, 5*_spRxdfAoaLow, 5*_spRxdfAoaMid, 5*_spRxdfAoaHgh } ;

#else
extern STR_SYS	_sp;
extern UINT	_sprfaoa[4];
extern UINT	_spdiffaoa[4];

#endif

#ifdef __cplusplus
}
#endif

#endif

