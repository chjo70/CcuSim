/****************************************************************************************
 �� �� �� : _system.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ��    �� :   
 ��    �� : 
 �� �� �� : Jo. Churl-hee
 �� �� �� : 
 ���泻�� : (����)
 �����Ͻ� : 99-04-07 3:20����
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 �Է����� : 
 ������� : 
 ���ø�� : 
 �ڷᱸ�� : (��������)
 ����ó��/���ͼ���:
 ������ �Ͻ� : 
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
#define		_spIplMaxHopJitPer	20			// Hopping�϶� �ִ� Jitter �� ��밪
																			// 2005-04-20 3:41����

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
#define		_spFtFixFrqLow			(2*_spRxdfFrqLow)		// debug, 1 -> 4, 05�� ���� ���� 4�� ��. 
#define		_spFtFixFrqMid			(2*_spRxdfFrqMid)		// ���򵵿��� Stable, Jitter ����ϴ� ���� ������ 
#define		_spFtFixFrqHgh			(2*_spRxdfFrqHgh)		// 4 -> 2�� ������.

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

#define		_spScMinTimeOutiOfPrd	(3.5)		// 3.5 ���� ��ĵ�ֱ� Ÿ�� �ƿ�

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

#define			_spAnalMinPulseStableEmitter			20		// Stable ������ �ּ� �޽� ����(���� �� ��ĵ ��ȣ�� �����)
#define			_spAnalMinPulseJitterEmitter			20

// 2005-07-05 7:56����
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
    UINT    Pdw_Max;            // ���� PDW �ִ��
  	UINT    Aoa_Shift_Cnt;      // ���� ������ BIN ũ�� = 2^N
    UINT    Aoa_Peak_Thr;       // ���� ������׷� PEAK �Ӱ谪  // 00.02.09
    UINT    Aoa_Hist_Thr;       // ���� ������׷� ���� �Ӱ谪  // 00.02.09
    UINT    Aoa_Range_Margin;   // ���� �׷� ���� margin
 
    UINT    Freq_Shift_Cnt;     // ���ļ� ������ BIN ũ�� = 2^N
    UINT    Freq_Peak_Thr;      // ���ļ� ������׷� PEAK �Ӱ谪    // 00.02.09
    UINT    Freq_Hist_Thr;      // ���ļ� ������׷� ���� �Ӱ谪    // 00.02.09
    UINT    Freq_Range_Margin;  // ���ļ� �׷� ���� margin
   
    UINT    Rpt_Aet_Cnt;    // Ž��; �ϳ��� �׷쿡�� REPORT�� AET�� ������ ����
 
} STR_NP ;

//##ModelId=43D4818A025F
typedef struct {
    UINT    Pdw_Max;            // ���� PDW �ִ��
/*  UINT    Aoa_Shift_Cnt;      // ���� ������ BIN ũ�� = 2^N
    UINT    Aoa_Peak_Thr;       // ���� ������׷� PEAK �Ӱ谪  // 00.02.09
    UINT    Aoa_Hist_Thr;       // ���� ������׷� ���� �Ӱ谪  // 00.02.09
    UINT    Aoa_Range_Margin;   // ���� �׷� ���� margin
 
    UINT    Freq_Shift_Cnt;     // ���ļ� ������ BIN ũ�� = 2^N
    UINT    Freq_Peak_Thr;      // ���ļ� ������׷� PEAK �Ӱ谪    // 00.02.09
    UINT    Freq_Hist_Thr;      // ���ļ� ������׷� ���� �Ӱ谪    // 00.02.09
    UINT    Freq_Range_Margin;  // ���ļ� �׷� ���� margin
*/
 
    UINT    Rpt_Aet_Cnt;    // ����; �ϳ��� �׷쿡�� REPORT�� AET�� ������ ����
 
} STR_KP ;

//##ModelId=43D4818A027D
typedef struct {
    UINT    Cw_Min_Cnt;         // CW��ȣ�� �м��ϱ� ���� �ּ� CW����
 
    UINT    Mpc;                //000223 // Stable �޽����� �ּ� �޽��� (Min. Pulse Count)
    UINT    Mjpc;               //000223 // Jitter �޽����� �ּ� �޽��� (Min. Jitter Pulse Count)
    UINT    Rpc;                // ���� �޽����� �޽��� (Reference Pule Count)
    UINT    Rjgpc;              // 000404  Jitter Stagger �����޽����� �ּ� �޽��� (Min. Jitter Stagger Pulse Count)
 
    UINT    Stb_Max_Miss;       // �ִ� ��� STABLE MISS ����
    UINT    Jit_Max_Miss;       // �ִ� ��� JITTER MISS ����
 
    UINT    Reflex_Zone;        // �ݻ��� ó�� ����
    UINT    Hprf_First_Pri;     // �ݻ���ó�� ������ High PRF���� ó��
 
    UINT    Jitter_P;           // �ִ� Ž�� jitter %  990226
 
    UINT    Dtoa_Sd;            // 500ns / (50 ns) MEAN ERROR
    UINT    Freq_Sd;            // low : 1.5 / (0.5MHz), mid : 3.75 / (1.25MHz), High : 4.5 / (1.5MHz)
 
 
    UINT    Jstg_Pt_P;          // Jitter Stagger�м����� Stagger�� ����� �޽����� ���� ���, �̻���~�� Stagger�� ����
    UINT    Jit_Merge_Miss_Cnt; // �ִ� ��� ���� JITTER MISS ����
 
    // ���� �м�
    UINT    Pat_Min_Cnt;        // ���� �м��� �ʿ��� �ּ� �޽���
    UINT    Lhp;                // Least Half Period �ּ� ���ֱ� �޽���
    UINT    Cross_Over;         // ���Ͽ��� LHP���� ����� ���������� �ִ� ȸ��
    UINT    Lhp_Thresh;         // ���� Ȯ�ο� ���Ǵ� �ּҹ��ֱ��� ȸ��
    UINT    Bad_Max;            // ���� Ȯ�ο��� �ִ� bad ȸ��
    UINT    Filt_Fac;           // Filtering Factor ���� �Ķ���� ��չ迭(filt[])�� ���鶧 ����� ��~�ϴ� ��ȣ��
    UINT    Maxparam_Min;       // ��չ迭(filt[])�� �ִ밪�� �ּ����� ��
    UINT    Pp_Max_Margin_P;    // �����ֱ� �������� ���Ǵ� �ִ밪�� margin %
//  UINT    Pp_Bin_Cnt;         // �����ֱ� ���ϱ�� Histogram Bin ��
    UINT    Pp_Match_P;         // �����ֱ� ���ϱ⿡�� ���Ϻ񱳿��� ��������
//  UINT    Pp_Pri_Match_Margin;    // �����ֱ� �������� PRI mean error margin (1us)
//  UINT    Pp_Freq_Match_Margin;   // �����ֱ� �������� FREQ mean error margin (2.5 5 6 MHz)
 
    // MAKE AET
    UINT    Conti_Thr;          // ���Ӽ� �ִ� ����
    UINT    Rpt_Pul_Cnt;        // �� �� �̻��� �޽����� AET�� ������ REPORT ���
 
} STR_CM ;
 
//##ModelId=43D4818A029B
typedef struct {
  UINT            Pdw_Max;            // ���� PDW �ִ��
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

  // Ž�� system parameters
  STR_NP      np;

  // ���� system parameters
  STR_KP      kp;

  // ����(Common) system parameters
  STR_CM      cm;

  // ��ĵ(SAP) system parameters
  STR_SC      sc;

} STR_SYS ;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_

STR_SYS		_sp;

// Update AOA threshold
UINT	_sprfaoa[4] = { 0, 2*_spRxdfAoaLow, 2*_spRxdfAoaMid, 2*_spRxdfAoaHgh } ;

// �����ͷ� �����ϴ� �� 
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

