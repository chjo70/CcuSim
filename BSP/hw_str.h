/**********************************************************************/
/**************   Sonata RSA Hardware Support Program    **************/
/**********************************************************************/
/*   FILENAME    : hw_str.h
     TARGET      : SONATA RSA 98 (Model I)
     PROGRAMMER  : KIM,YONG-WOO
     DATE        : (C)1998.  3.  16.
				   (C)1998.  7.  13.  -- RCV 관련 구조체 수정
				   (C)1998.  7.  15.  -- in dummy of register word0
				   (C)1998.  7.  27.  -- t_cnt_lsb 추가
				   (C)1999.  7.  18.  -- NSF Counter 추가
 **********************************************************************/

#ifndef _HW_STR_H_
#define _HW_STR_H_

#include "../BSP/hw_def.h"

#include "../INC/_type.h"
#include "../INC/_pdw.h"

//##ModelId=43D4818A0056
typedef struct {			// old version
  word16  lower_frq;
  word16  upper_frq;
  word16  from_aoa;
  word16  to_aoa;
} INHIBIT_WINDOW_WORDS;

//##ModelId=43D4818A007E
typedef struct
{
    int     flg;		 // 0 -> Inhibit 사용 안함, 1 -> 사용함
    int     fr;
    int     to;
} hwLAN_IHB_AOA;

//##ModelId=43D4818A00A6
typedef struct
{
    int     flg;		// 0 -> Inhibit 사용 안함, 1 -> 사용함
    int     bnd;		// 1:Band1, 2:Band2, 3:Band3
    int     low;
    int     hgh;
} hwLAN_IHB_FRQ;

//##ModelId=43D4818A00CE
typedef struct
{
    int     LowerBC;    // 1:Band1, 2:Band2, 3:Band3
    int     UpperBC;    // 1:Band1, 2:Band2, 3:Band3
    int     LowerFrq;
    int     UpperFrq;
    int     FromAoa;
    int     ToAoa;
    int			FromPa;
    int			ToPa;

} AUD_RANGE;


/************************************************************/
/*		Mode Control Register for Receiver Board		    */
/************************************************************/

	/*        <<< RCV Board Mode Control Word >>
	   D7     D6     D5     D4     D3     D2     D1     D0
  	+------+------+------+------+------+------+------+------+
  	| PDW  |      | PDW  |Reject|  DV  | Dest | Src  | BIT  |
  	|Enable|      |Bypass|CalPdw| Check|      |      |Enable|
  	+------+------+------+------+------+------+------+------+ */

//##ModelId=43D4818A00F6
typedef union {
	word08	byte;
	struct {
		word08	PDW_Enable		: 1;
		word08	_dummy1				: 1;
		word08	PDW_Bypass		: 1;
		word08	Reject_CalPdw	: 1;
		word08	DV_Check			: 1;
		word08	Destination		: 1;
		word08	Source				:	1;
		word08	Bit_Enable		:	1;
	} bit;

} RCV_MODE_CONTROL_WORD;

/************************************************************/
/* Filter Register Words for NSF Boards           */
/************************************************************/

/*
 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|U|C|L|R|P|T| STAT  |   |       To_AOA      |     From_AOA      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   |        UPPER_BC_FRQ         |           LOWER_BC_FRQ      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   |       UPPER_PW      |      LOWER_PW       |    UPPER_PA   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     |              P_CNT    |     T_CNT       |    LOWER_PA   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

*/

/*
 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|U|C|   | T_CNT(LSB)    |       To_AOA      |     From_AOA      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| STAT  |BC |        UPPER_FRQ        |        LOWER_FRQ        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   |       UPPER_PW      |      LOWER_PW       |    UPPER_PA   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|L|R|P|T|        P_CNT          |     T_CNT     |    LOWER_PA   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

*/

/*
 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|U|C|   |               |       To_AOA      |     From_AOA      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| STAT  |BC |        UPPER_FRQ        |        LOWER_FRQ        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   |       UPPER_PW      |      LOWER_PW       |    UPPER_PA   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   |L|R|P|T|      P_CNT        |     T_CNT     |    LOWER_PA   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

*/

//##ModelId=43D4818A011E
typedef struct {
	union {
		word32	word;
		struct {
			word32	use     		: 1;	/* 0 = not use,	   1 = in use */
			word32	check_stat	: 1;	/* 1 = check stat bits */
			word32	late				: 1;	/* late */
			word32	p_req				: 1;	/* pseudo-PDW request */
			word32	p_ena				: 1;	/* pulse counter enable */
			word32	t_ena				: 1;	/* timer counter enable */
			word32	stat				: 4;	/* status value */
			word32	_dummy			: 2;
			word32	to_aoa			:10;
			word32	from_aoa		:10;
		} nsf ;							// NSF

    struct {
      word32  use         : 1;    /* 0 = not use,    1 = in use   */
      word32  check_stat  : 1;    /* 1 = check stat bits */
      word32  _dummy1			: 2;
      word32  _dummy2     : 8;    /* only for Scan Filter (SAF)   */
      word32  to_aoa      :10;
      word32  from_aoa    :10;
    } ksf ;

    struct {
      word32  use         : 1;    /* 0 = not use,    1 = in use   */
      word32  check_stat  : 1;    /* 1 = check stat bits */
      word32  _dummy			: 2;
      word32  t_cnt_lsb   : 8;    /* only for Scan Filter (SAF)   */
      word32  to_aoa      :10;
      word32  from_aoa    :10;
    } saf ;							// KSF

    struct {
      word32  use         : 1;    /* 0 = not use,    1 = in use   */
      word32  check_stat  : 1;    /* 1 = check stat bits */
      word32  _dummy      : 2;
      word32  t_cnt_lsb   : 8;    /* only for Scan Filter (SAF)   */
      word32  to_aoa      :10;
      word32  from_aoa    :10;
    } b ;  							// Old Cell_Words
	} w0;

	union {
		word32	word;
		struct {
			word32	_dummy			 : 2;
			word32	upper_bc     : 2;
			word32	upper_frq    :13;	/* upper limit of bc & frequency */
			word32	lower_bc     : 2;
			word32	lower_frq    :13;	/* lower limit of bc & frequency */
		} nsf2 ;						// NSF
    struct {
      word32  _dummy			 : 2;
      word32  upper_bc_frq :15;   /* upper limit of bc & frequency */
      word32  lower_bc_frq :15;   /* lower limit of bc & frequency */
    } nsf ;                        // NSF

		struct {
      word32  stat        : 4;    /* status value */
      word32  bc          : 2;    /* Band Code of frequency */
      word32  upper_frq   :13;    /* upper limit of frequency */
      word32  lower_frq   :13;    /* lower limit of frequency */
    } ksf ;							// KSF

    struct {
			word32  stat        : 4;    /* status value */
			word32  bc          : 2;    /* Band Code of frequency */
			word32  upper_frq   :13;    /* upper limit of frequency */
			word32  lower_frq   :13;    /* lower limit of frequency */
		} saf ;							// SAF

		struct {
			word32  stat        : 4;    /* status value */
			word32  bc          : 2;    /* Band Code of frequency */
			word32  upper_frq   :13;    /* upper limit of frequency */
			word32  lower_frq   :13;    /* lower limit of frequency */
		} b;							// Old Cell_Words
	} w1;

	union {
		word32	word;
		struct {
			word32	_dummy			: 2;	/* dummy */
			word32	upper_pw		:11;	/* upper limit of pulse width */
			word32	lower_pw		:11;	/* lower limit of pulse width */
			word32	upper_pa		: 8;	/* upper limit of pulse amplitude */
		} nsf ;

    struct {
      word32  _dummy			: 2;    /* dummy */
      word32  upper_pw    :11;    /* upper limit of pulse width   */
      word32  lower_pw    :11;    /* lower limit of pulse width   */
      word32  upper_pa    : 8;    /* upper limit of pulse amplitude */
    } ksf ;

    struct {
      word32  _dummy			: 2;    /* dummy */
      word32  upper_pw    :11;    /* upper limit of pulse width   */
      word32  lower_pw    :11;    /* lower limit of pulse width   */
      word32  upper_pa    : 8;    /* upper limit of pulse amplitude */
    } saf ;

    struct {
      word32  _dummy			: 2;    /* dummy */
      word32  upper_pw    :11;    /* upper limit of pulse width   */
      word32  lower_pw    :11;    /* lower limit of pulse width   */
      word32  upper_pa    : 8;    /* upper limit of pulse amplitude */
    } b ;							// Old Cell_Words

	} w2;

	union {
		word32	word;
		struct {
			word32	_dummy			: 3;	/* dummy */
			word32	p_cnt				:12;	/* pulse counter */
			word32	t_cnt				: 9;	/* timer counter (MSB for SAF board) */
			word32	lower_pa		: 8;	/* lower limit of pulse amplitude */
		} nsf ;

    struct {
      word32  _dummy			: 2;    /* dummy */
      word32  late        : 1;    /* late */
      word32  p_req       : 1;    /* pseudo-PDW request */
      word32  p_ena       : 1;    /* pulse counter enable */
      word32  t_ena       : 1;    /* timer counter enable */
      word32  p_cnt       :10;    /* pulse counter */
      word32  t_cnt       : 8;    /* timer counter (MSB for SAF Board)    */
      word32  lower_pa    : 8;    /* lower limit of pulse amplitude */
    } ksf ;

    struct {
      word32  late        : 1;    /* late */
      word32  p_req       : 1;    /* pseudo-PDW request */
      word32  p_ena       : 1;    /* pulse counter enable */
      word32  t_ena       : 1;    /* timer counter enable */
      word32  p_cnt_msb   : 2;    /* pulse counter */
      word32  p_cnt       :10;    /* pulse counter */
      word32  t_cnt       : 8;    /* timer counter (MSB for SAF Board)    */
      word32  lower_pa    : 8;    /* lower limit of pulse amplitude */
    } saf ;

    struct {
      word32  _dummy			: 2;    /* dummy */
      word32  late        : 1;    /* late */
      word32  p_req       : 1;    /* pseudo-PDW request */
      word32  p_ena       : 1;    /* pulse counter enable */
      word32  t_ena       : 1;    /* timer counter enable */
      word32  p_cnt       :10;    /* pulse counter */
      word32  t_cnt       : 8;    /* timer counter (MSB for SAF Board)    */
      word32  lower_pa    : 8;    /* lower limit of pulse amplitude */
    } b ;

	} w3;		/* This word is not used at NSF */

} CELL_WORDS;

/************************************************************/
/* Tagged PDW (Pulse Descriptor Words) Structure            */
/************************************************************/

/*
 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|0|0|  STAT |  DIRECTION (AOA)  |D|BC |       FREQUENCY         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|0|1|     |     PULSE WIDTH     |   TOA (MSB)   |PULSE AMPLITUDE|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|1|0|           |                   TOA (LSB)                   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|1|1|           |CHANNEL NUMBER |    PMOP       |     FDIFF     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

//##ModelId=43D4818A0146
typedef struct {
	union	{
		word32	word;
		struct	{
	    word32 pc     :  2;
			word32 stat		:  4;
			word32 aoa		: 10;
			word32 dv			:  1;
			word32 bc			:  2;
			word32 frq 		: 13;
		} b;
	} ph1;

	union	{
		word32	word;
		struct	{
		    word32 pc   :  2;
			word32 _dummy :  2;
			word32 pq 		:  1;
			word32 pw	 		: 11;
			word32 toah		:  8;
			word32 pa			:  8;
		} b;
	} ph2;

	union {
		word32	word;
		struct {
			word32 pc     :  2;
			word32 _dummy :  6;
			word32 toal		: 24;
		} b;
	} ph3;

	union	{
		word32	word;
		struct	{
	    word32 pc			:  2;
			word32 _dummy :  6;
			word32 ch	  	:  8;
			word32 pmop   :  8;
			word32 fdiff	:  8;
		} b;
	} ph4;
} TPDW_STRUCT;


/************************************************************/
/* Pseudo PDW (Pulse Descriptor Words) Structure            */
/************************************************************/

/*
 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|0|0|                             |1|1|         | CHANNEL NUMBER|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

//##ModelId=43D4818A0164
typedef union	{
	word32	word;
	struct	{
	  word32 pc       :  2;
		word32 _dummy1	: 15;
		word32 bc				:  2;
		word32 _dummy2	:  5;
		word32 channel	:  8;
	} b;
} PSEUDO_PDW_STRUCT;

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////
//	hw_bsp.c
//
void    NSF_SetWindowWords(CELL_WORDS *pcw);
BOOL    NSF_ReadPerr(void);
void    NSF_ClearPerr(void);
void    NSF_TurnOnTestLED(int LEDno, BOOL bTurnOn);
void    NSF_SetIgnoreMatch(BOOL bCmnd);
void    NSF_ReqPseudoPDW(void);
void    NSF_OpenMainGate(BOOL bCmnd);
void    NSF_InitBoard(void);

void    KSF_CloseWindow(int noKSF, int noCell);
void    KSF_SetWindowWords(int noKSF, int noCell, CELL_WORDS *pcw);
void    KSF_SetCounterWord(int noKSF, int noCell, CELL_WORDS *pcw);
void    KSF_SetCellWords(int noKSF, int noCell, CELL_WORDS *pcw);
BOOL    KSF_ReadPerr(int noKSF );
void    KSF_ClearPerr(int noKSF);
void    KSF_TurnOnTestLED(int noKSF, int LEDno, BOOL bTurnOn);
void    KSF_InitBoard(int noKSF);

void    SAF_CloseWindow(int noCell);
void    SAF_SetWindowWords(int noCell, CELL_WORDS *pcw);
void    SAF_SetCounterWord(int noCell, CELL_WORDS *pcw);
void    SAF_SetCellWords(int noCell, CELL_WORDS *pcw);
BOOL    SAF_ReadPerr(void);
void    SAF_ClearPerr(void);
void    SAF_TurnOnTestLED(int LEDno, BOOL bTurnOn);
void    SAF_EnableMatch( BOOL bEnable );
void    SAF_InitBoard(void);

void    REL_TurnOnBit(BOOL bBit);

word32  DM_GetFifo(void);
void    DM_ResetFifo(void);
void    DM_MakeBitData(void);
void    DM_ClearPerr(void);
word32  DM_ReadExtStatus(void);
/*
word32  DM_ReadSlotID(void);
*/
BOOL    DM_FifoEmpty(void);
BOOL    DM_FifoHalfFull(void);
BOOL    DM_FifoFull(void);
word32  DM_ReadFifoStatus(void);
BOOL    DM_ParityError(void);
void    RCV_SetAoaEnaBitMap(word16 nBitMap);
void    RCV_SetFrqEnaBitMap(word16 nBitMap);
void    RCV_SetFrqInhibitWindows( hwLAN_IHB_FRQ *pww);
void    RCV_SetAoaInhibitWindows( hwLAN_IHB_AOA *pww);
void    RCV_InitInhibitWindows(void);
void    RCV_SetBitPdw(TPDW_STRUCT *pdw);
void    RCV_SetBitPri(word16 nValue);
void    RCV_Gen1BitPdw(void);
void    RCV_SetBandRange(void);
void    RCV_SetModeControl_BitMap(RCV_MODE_CONTROL_WORD nBitMap);
void    RCV_SetDvCheckEnable(BOOL bEnable);
void    RCV_SetRejectCalPdwEnable(BOOL bEnable);
void    RCV_SetModeControl_Mode(int nMode);
word32  RCV_ReadInhibitStatus(void);
BOOL    RCV_InhibitOccured(void);
void    RCV_InitBoard(void);

void    AUD_OpenFrqWin(void);
void    AUD_OpenAoaWin(void);
void    AUD_SetAudioRange(AUD_RANGE *ar);
void    AUD_SetEnable(BOOL bEnable);
void    AUD_TurnOnTestLED(int nLEDno, BOOL bTurnOn);
void    AUD_InitBoard(void);

////////////////////////////////////////////////////////////////////
//	vhw_bsp.c
//
UINT 	vNSF_SetWindowWords(CELL_WORDS *pcw);
UINT 	vNSF_SetCounterWord(CELL_WORDS *pcw);
UINT 	vNSF_ReadPerr(USHRT *val );
UINT 	vNSF_ClearPerr(void);
UINT 	vNSF_TurnOnTestLED(int LEDno, BOOL bTurnOn);
UINT  vNSF_SetCellWords( CELL_WORDS *pcw );
UINT 	vNSF_SetIgnoreMatch(BOOL bCmnd);
UINT 	vNSF_ReqPseudoPDW(void);
BOOL 	vNSF_OpenMainGate(BOOL bCmnd);		//
UINT 	vNSF_WinCellWideOpen();
UINT	vNSF_SetBypassMode();
UINT 	vNSF_InitBoard(void);
UINT 	vKSF_CloseWindow(int noKSF, int noCell);
UINT 	vKSF_SetWindowWords(int noKSF, int noCell, CELL_WORDS *pcw);
UINT 	vKSF_SetCounterWord(int noKSF, int noCell, CELL_WORDS *pcw);
UINT 	vKSF_SetCellWords(int noKSF, int noCell, CELL_WORDS *pcw);
UINT 	vKSF_ReadPerr(int noKSF, USHRT *val );
UINT 	vKSF_ClearPerr(int noKSF);
UINT 	vKSF_TurnOnTestLED(int noKSF, int LEDno, BOOL bTurnOn);
UINT 	vKSF_InitBoard(int noKSF);

////////////////////////////////////////////////////////////////////
//  Scan
//
UINT 	vSAF_CloseWindow(int noCell);
UINT 	vSAF_SetWindowWords(int noCell, CELL_WORDS *pcw);
UINT 	vSAF_SetWindowWords_close(int noCell, CELL_WORDS *pcw);
UINT 	vSAF_SetCounterWord(int noCell, CELL_WORDS *pcw);
UINT 	vSAF_SetCellWords(int noCell, CELL_WORDS *pcw);
UINT 	vSAF_SetCellWords_close(int noCell, CELL_WORDS *pcw);
UINT 	vSAF_ReadPerr( USHRT *val );
UINT 	vSAF_ClearPerr(void);
UINT 	vSAF_TurnOnTestLED(int LEDno, BOOL bTurnOn);
UINT 	vSAF_EnableMatch( BOOL bEnable );
UINT 	vSAF_InitBoard( void );
UINT	vSAF_StopWindow(int noCell);

UINT 	vDM_GetFifo( UINT *val );
UINT 	vDM_ResetFifo( void );
UINT 	vDM_MakeBitData( void );
UINT 	vDM_ClearPerr( void );
UINT 	vDM_ReadExtStatus( UINT *val );
UINT 	vDM_ReadSlotID( UINT *val );
BOOL 	vDM_FifoEmpty(void);
BOOL 	vDM_FifoHalfFull(void);
BOOL 	vDM_FifoFull( void );
UINT 	vDM_ReadFifoStatus( UINT *fifostat );
BOOL 	vDM_ParityError( void );
UINT	vDM_ClearHalfInterrupt(BOOL	val);
UINT	vDM_ClearFullInterrupt(BOOL	val);

UINT 	vRCV_SetAoaEnaBitMap(word16 nBitMap);
UINT 	vRCV_SetFrqEnaBitMap(USHRT nBitMap);
UINT 	vRCV_SetFrqInhibitWindows(hwLAN_IHB_FRQ *pww );
UINT 	vRCV_SetAoaInhibitWindows(hwLAN_IHB_AOA *pww );
UINT 	vRCV_InitInhibitWindows( void );
UINT 	vRCV_SetBitPdw(TNEW_PDW *pdw);
// UINT 	vRCV_SetBitPdw(TPDW_STRUCT *pdw);
UINT 	vRCV_SetBitPri( USHRT nValue );
UINT 	vRCV_Gen1BitPdw( void );
UINT 	vRCV_SetBandRange( void );
UINT 	vRCV_SetModeControl_BitMap( RCV_MODE_CONTROL_WORD nBitMap );
UINT 	vRCV_SetDvCheckEnable(BOOL bEnable);
UINT 	vRCV_SetRejectCalPdwEnable(BOOL bEnable);
UINT 	vRCV_SetModeControl_Mode(int    nMode);
UINT 	vRCV_ReadInhibitStatus( UINT *val );
BOOL 	vRCV_InhibitOccured( void );
UINT	vRCV_BandOverlabReject(USHRT lbandLow, USHRT lbandHgh, USHRT mbandLow, USHRT mbandHgh, USHRT hbandLow, USHRT hbandHgh);
BOOL 	vRCV_InitBoard( void );
UINT 	vAUD_OpenFrqWin( void );
UINT 	vAUD_OpenAoaWin( void );
UINT 	vAUD_SetAudioRange(AUD_RANGE *par);
UINT 	vAUD_SetEnable(BOOL bEnable);
UINT 	vAUD_TurnOnTestLED(BOOL bTurnOn);
UINT 	vAUD_InitBoard( void );

#ifdef __cplusplus
}
#endif

#endif

