/**********************************************************************/
/**************   Sonata RSA Hardware Support Program    **************/
/**********************************************************************/
/*	FILENAME    : hw_def.h
	TARGET      : SONATA RSA 99 (Model II)
	DATE        : (C)1999. 7. 18.
 **********************************************************************/

#ifndef _HW_DEF_
#define _HW_DEF_

#ifndef _WIN32
typedef unsigned int bool;
#endif

// LED Definition
#define LED0		0
#define LED1		1

/******* LOGIC DEFINITION *******/
#define	word32				unsigned	int
#define	word16				unsigned	short int
#define	word08				unsigned	char

#define	true   				1
#define	false				0
#define	RCV_MODE_OFF 		0
#define	RCV_MODE_PDW 		1
#define	RCV_MODE_BPDW 		2
#define	RCV_MODE_BIT 		3
#define	RCV_MODE_BBIT 		4
#define	RCV_MODE_1BIT 		5
#define	RCV_MODE_B1BIT 		6

#define Fifo_StatusError	0
#define Fifo_Empty			1
#define Fifo_Full			2
#define Fifo_HalfFull		3
#define Fifo_NotEmpty		4

#define	prc_AUTO			0x00
#define prc_CIP             0x01
#define prc_SAP             0x02
#define prc_NSP             0x03
#define prc_KSP				0x04
#define	prc_KSP1			0x04
#define	prc_KSP2			0x05
#define	prc_KSP3			0x06
#define	prc_KSP4			0x07
#define pwb_CMF				0x08
#define	pwb_CMS				0x09
#define	pwb_RCV				0x0A
#define	pwb_RC				0x0B

#define	pwb_AUD				0x11
#define	pwb_SAF				0x12
#define	pwb_NSF				0x13
#define	pwb_KSF1			0x14
#define	pwb_KSF2			0x15
#define	pwb_KSF3			0x16
#define	pwb_KSF4			0x17

#define	pwb_DMS				0x22
#define	pwb_DMN				0x23
#define	pwb_DMK1			0x24
#define	pwb_DMK2			0x25
#define	pwb_DMK3			0x26
#define	pwb_DMK4			0x27

#define NSF_noCell          1
#define	SAF_noCell			16
#define	KSF_noCell			32

/****** VMEbus A32 Area *********/
#define aSBC_CIP 		0x01000000
#define aSBC_SAP 		0x02000000
#define aSBC_NSP 		0x03000000
#define aSBC_KSP1 		0x04000000
#define aSBC_KSP2 		0x05000000
#define aSBC_KSP3 		0x06000000
#define aSBC_KSP4 		0x07000000
#define ahwVME_CMF 		0x08000000
#define ahwVME_CMS 		0x09000000
#define ahwVME_AUD  	0x11000000
#define ahwVME_SAF		0x12000000 
#define ahwVME_NSF		0x13000000 
#define ahwVME_KSF		0x14000000

/****** IP Memory Map Area ******/
#define ahwIPA_BASE		0xC0000000
#define ahwIPB_BASE		0xC0800000
#define ahwIPC_BASE		0xC1000000
#define ahwIPD_BASE		0xC1800000

/****** Local I/O Area **********/
#ifndef aLCSR
#define aLCSR 			0xFFF40000			// also defined rcbios.h
#endif

// #define ahwVME_AUD  	0x11000000
#define aGCSR 			0xFFF40100
#define aMC2IC_REG		0xFFF42000			// MC2 Chip base address
#define ahwIPAB 		0xFFF58400
#define ahwIPCD 		0xFFF58500			// debug, 01-02-06
// #define ahwIPCD 		0xFFF58500			// debug, 01-02-06
#define ahwIPCD_DM 		0xFFF58500
#define aIPIC_REG		0xFFFBC000
#define aIPIC_INT       0xFFFBC004
#define aSYS_TOD        0xFFFC1FF8

/****** VMEbus A16 Area *********/
#define ahwVME_RC		0xFFFF0000
#define ahwVME_RCV		0xFFFF0F00
#define aVME_GCSR		0xFFFFD200

// Old hw_str.h
#define ahwVME_REL		0xFFFF0081				
#define phwAUD_TestLED0			(word32 *)(ahwVME_AUD + 0x80)

/************************************************************/
/*	CM (Common Memory) Board 								*/ 
/************************************************************/
#define	ahwCMF_Bank0				  (ahwVME_CMF + 0x000000)
#define	ahwCMF_Bank1				  (ahwVME_CMF + 0x400000)
#define	ahwCMF_Bank2				  (ahwVME_CMF + 0x800000)
#define	ahwCMF_Bank3				  (ahwVME_CMF + 0xC00000)
#define	phwCMF_B0Comm1		(word32 *)(ahwCMF_Bank0 + 0x15554)
#define	phwCMF_B0Comm2		(word32 *)(ahwCMF_Bank0 + 0x0AAA8)
#define	phwCMF_B1Comm1		(word32 *)(ahwCMF_Bank1 + 0x15554)
#define	phwCMF_B1Comm2		(word32 *)(ahwCMF_Bank1 + 0x0AAA8)
#define	phwCMF_B2Comm1		(word32 *)(ahwCMF_Bank2 + 0x15554)
#define	phwCMF_B2Comm2		(word32 *)(ahwCMF_Bank2 + 0x0AAA8)
#define	phwCMF_B3Comm1		(word32 *)(ahwCMF_Bank3 + 0x15554)
#define	phwCMF_B3Comm2		(word32 *)(ahwCMF_Bank3 + 0x0AAA8)

/************************************************************/
/*	NSF (New-Signal Filter) Board							*/ 
/************************************************************/
#define	phwNSF_ReadPerr			(word16 *)(ahwVME_NSF + 0x00)
#define	phwNSF_ClearPerr		(word16 *)(ahwVME_NSF + 0x02)
#define phwNSF_TestLED0			(word16 *)(ahwVME_NSF + 0x04)	
#define phwNSF_TestLED1			(word16 *)(ahwVME_NSF + 0x06)
#define phwNSF_IgnoreMatch		(word16 *)(ahwVME_NSF + 0x08)
#define phwNSF_MainGate			(word16 *)(ahwVME_NSF + 0x0C)
#define ahwNSF_WindowWords				  (ahwVME_NSF + 0x100000)
#define ahwNSF_CounterWords				  (ahwVME_NSF + 0x200000)
#define phwNSF_PseudoGen		(word16 *)(ahwVME_NSF + 0x200000)

/************************************************************/
/*	KSF (Known-Signal Filter) Board													*/ 
/************************************************************/
#define ahwKSF_CounterWords		(ahwVME_KSF + 0x00000000)
#define ahwKSF_PseudoGen			(ahwVME_KSF + 0x00000100)
#define ahwKSF_WindowWords		(ahwVME_KSF + 0x00000400)
#define	ahwKSF_ReadPerr				(ahwVME_KSF + 0x00100000)
#define	ahwKSF_ClearPerr			(ahwVME_KSF + 0x00100002)
#define ahwKSF_TestLED0				(ahwVME_KSF + 0x00100004)	
#define ahwKSF_TestLED1				(ahwVME_KSF + 0x00100006)

/************************************************************/
/*	SAF (Scan Ananlysis Filter) Board												*/ 
/************************************************************/
#define ahwSAF_CounterWords		(ahwVME_SAF + 0x00000000)
#define ahwSAF_PseudoGen			(ahwVME_SAF + 0x00000100)
#define ahwSAF_WindowWords		(ahwVME_SAF + 0x00000400)
#define	ahwSAF_ReadPerr				(ahwVME_SAF + 0x00100000)
#define	ahwSAF_ClearPerr			(ahwVME_SAF + 0x00100002)
#define ahwSAF_TestLED0				(ahwVME_SAF + 0x00100004)	
#define ahwSAF_TestLED1				(ahwVME_SAF + 0x00100006)
#define ahwSAF_EnableMatch		(ahwVME_SAF + 0x00100008)

/************************************************************/
/*  AUD (Audio) Board																				*/
/************************************************************/
#define phwAUD_OpenFrqWin			(word32 *)(ahwVME_AUD)
#define phwAUD_OpenAoaWin 		(word32 *)(ahwVME_AUD + 0x04)
#define phwAUD_SetLowerFrq		(word32 *)(ahwVME_AUD + 0x08)
#define phwAUD_SetUpperFrq		(word32 *)(ahwVME_AUD + 0x0C)
#define phwAUD_SetFromAoa			(word32 *)(ahwVME_AUD + 0x10)
#define phwAUD_SetToAoa				(word32 *)(ahwVME_AUD + 0x14)
#define phwAUD_SetFromPa			(word32 *)(ahwVME_AUD + 0x18)
#define phwAUD_SetToPa				(word32 *)(ahwVME_AUD + 0x1C)
#define phwAUD_SetEnable			(word32 *)(ahwVME_AUD + 0x40)
#define phwAUD_TestLED				(word32 *)(ahwVME_AUD + 0x80)
#define phwAUD_ReadBit				(word32 *)(ahwVME_AUD + 0xA0)
#define phwAUD_ClearBit				(word32 *)(ahwVME_AUD + 0xA4)

/************************************************************/
/*	DM (Data Memory) Board with IP interface								*/ 
/************************************************************/
#define phwDM_ReadFifo				(word32 *)(ahwIPCD_DM + 0x00)	/* modify 99.07.20 */
#define phwDM_ResetFifo				(word32 *)(ahwIPCD_DM + 0x08)	/* modify 99.07.20 */
#define phwDM_MakeBitData			(word32 *)(ahwIPCD_DM + 0x10)	/* modify 99.07.20 */
#define phwDM_ClearPerr				(word32 *)(ahwIPCD_DM + 0x18)	/* modify 99.07.20 */
#define phwDM_ReadExtStatus		(word32 *)(ahwIPCD_DM + 0x20)	/* modify 99.07.20 */
#define phwDM_SetBitData			(word32 *)(ahwIPCD_DM + 0x40)	/* modify 99.07.20 */
#define phwDM_ClearHalfInt		(word32 *)(ahwIPCD_DM + 0x80)	/* modify 99.07.20 */
#define phwDM_ClearFullInt		(word32 *)(ahwIPCD_DM + 0x88)	/* modify 99.07.20 */

/*        <<< DM BOARD EXTERNAL STATUS BIT MAP >>> 
      D7     D6     D5     D4     D3     D2     D1     D0
   +------+------+------+------+------+------+------+------+
   |Parity| FIFO | FIFO | FIFO |      SLOT ID NUMBER       |
   | err  | Empty| Half | Full |                           | 
   +------+------+------+------+------+------+------+------+
								   Slot ID		Board ID 
	 								 0010				SAF
									 0011				NSF
									 0100				KSF1
									 0101				KSF2
									 0110				KSF3
									 0111				KSF4
*/

/************************************************************/
/*	RCV (PDW Receive) Board									*/ 
/************************************************************/
#define	phwRCV_LoFrqWin					(word16 *)(ahwVME_RCV + 0x00)
#define	phwRCV_HiFrqWin					(word16 *)(ahwVME_RCV + 0x12)
#define	phwRCV_FromAoaWin				(word16 *)(ahwVME_RCV + 0x24)
#define	phwRCV_ToAoaWin					(word16 *)(ahwVME_RCV + 0x36)
#define phwRCV_AoaEnable				(word16 *)(ahwVME_RCV + 0x48)
#define phwRCV_FrqEnable				(word16 *)(ahwVME_RCV + 0x4A)
#define	phwRCV_BitPdw1					(word32 *)(ahwVME_RCV + 0x60)
#define	phwRCV_BitPdw2					(word32 *)(ahwVME_RCV + 0x64)
#define	phwRCV_BitPdw3					(word32 *)(ahwVME_RCV + 0x68)
#define	phwRCV_BitPdw4					(word32 *)(ahwVME_RCV + 0x6C)
#define phwRCV_BitPri						(word16 *)(ahwVME_RCV + 0x70)
#define phwRCV_B1LoFrq					(word16 *)(ahwVME_RCV + 0x72) 
#define phwRCV_B1HiFrq					(word16 *)(ahwVME_RCV + 0x74) 
#define phwRCV_B2LoFrq					(word16 *)(ahwVME_RCV + 0x76) 
#define phwRCV_B2HiFrq					(word16 *)(ahwVME_RCV + 0x78) 
#define phwRCV_B3LoFrq					(word16 *)(ahwVME_RCV + 0x7A) 
#define phwRCV_B3HiFrq					(word16 *)(ahwVME_RCV + 0x7C) 
#define phwRCV_ModeControl			(word08 *)(ahwVME_RCV + 0x81)
#define phwRCV_InhibitStatus		(word32 *)(ahwVME_RCV + 0x84)
#define phwRCV_1BitPdw					(word16 *)(ahwVME_RCV + 0x88)


#define phwRCV_SetlowFrq

/************************************************************/
/*	RC (Receiver Control) Board															*/ 
/************************************************************/
#define	phwRC_SelectSIO1				(word16 *)(ahwVME_RC + 0xA0)
#define	phwRC_SelectSIO2				(word16 *)(ahwVME_RC + 0xB0)
#define	phwRC_ResetSIO	    		(word16 *)(ahwVME_RC + 0xC0)
#define	phwRC_TurnOnBit	    		(word16 *)(ahwVME_RC + 0xD0)
#define	phwRC_ReadMode	    		(word16 *)(ahwVME_RC + 0xE0)

/************************************************************/
/*	PDW Reciver's Freq. range each bands										*/
/************************************************************/
// #define		

#endif	/* _HW_DEF_ */
