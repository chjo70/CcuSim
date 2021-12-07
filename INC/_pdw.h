/****************************************************************************************
 �� �� �� : _pdw.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 ��    �� :   
 ��    �� : 
 �� �� �� : Jo. Churl-hee
 �� �� �� : 
 ���泻�� : (����)
 �����Ͻ� : 99-04-06 1:59����
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 �Է����� : 
 ������� : 
 ���ø�� : 
 �ڷᱸ�� : (��������)
 ����ó��/���ͼ���:
 ������ �Ͻ� : 
*****************************************************************************************/

#ifndef _PDW_H_
#define	_PDW_H_

// PDW�� Phase ����
#define PDW_WORD_LEN				4
#define PDW_WORD_CNT				4
#define	SizeOfPDW						16
#define ByteOfPhase					4
#define	SizeOfPSEUDO_PDW		ByteOfPhase

// PDW ���� �� ���� ��
#define PDW_CW							4
#define	PDW_CHIRPUP					2
#define	PDW_CHIRPDN					3
#define	PDW_PMOP						1
#define	PDW_NORMAL					0
#define	PDW_BIT							15

// PDW ����, Platform�� � ���̳Ŀ� ���� UNIX �� �����Ͽ� ������ �Ǵ� ���� ��������.
#ifndef _WIN32
//##ModelId=43D4818D01CD
typedef union {
	UCHAR	bpdw[ PDW_WORD_CNT ][ PDW_WORD_LEN ];
	UINT	wpdw[ PDW_WORD_CNT ];
	struct {
		UCHAR phase1        : 2;	/* Phase 1 */
		UCHAR stat          : 4;
		UCHAR direction_h   : 2;
		UCHAR direction_l   : 8;
		UCHAR dv            : 1;
		UCHAR band          : 2;
		UCHAR frequency_h   : 5;
		UCHAR frequency_l   : 8;

		UCHAR phase2        : 2;	/* Phase 2 */
		UCHAR fil1          : 2;
		UCHAR pq            : 1;
		UCHAR pulse_width_h : 3;
		UCHAR pulse_width_l : 8;
		UCHAR toa_1         : 8;
		UCHAR amplitude     : 8;

		UCHAR phase3        : 2;	/* Phase 3 */
		UCHAR fil2          : 6;
		UCHAR toa_2         : 8;
		UCHAR toa_3         : 8;
		UCHAR toa_4         : 8;
		
		UCHAR phase4        : 2;	/* Phase 4 */
		UCHAR fil3          : 5;
		UCHAR chlp          : 1;
		UCHAR channel       : 8;
		UCHAR pmop          : 8;
		UCHAR freq_diff     : 8;

	} item;
} TNEW_PDW;

#else	/* dos */
typedef union {
	UCHAR bpdw[ PDW_WORD_CNT ][ PDW_WORD_LEN ];
	UINT  wpdw[ PDW_WORD_CNT ];
  struct {
		UCHAR direction_h   : 2;	/* Phase 1 */
		UCHAR stat          : 4;
		UCHAR phase1        : 2;
		UCHAR direction_l   : 8;
		UCHAR frequency_h   : 5;
		UCHAR band          : 2;
		UCHAR dv            : 1;

		UCHAR frequency_l   : 8;	/* Phase 2 */
		UCHAR pulse_width_h : 3;
		UCHAR pq            : 1;
		UCHAR fil1          : 2;
		UCHAR phase2        : 2;
		UCHAR pulse_width_l : 8;
		UCHAR toa_4         : 8;

		UCHAR amplitude     : 8;	/* Phase 3 */
		UCHAR fil2          : 6;
		UCHAR phase3        : 2;
		UCHAR toa_3         : 8;
		UCHAR toa_2         : 8;
		UCHAR toa_1         : 8;

		UCHAR chlp          : 1;	/* Phase 4 */
		UCHAR fil3          : 5;
		UCHAR phase4        : 2;          
		UCHAR channel       : 8;
		UCHAR pmop          : 8;
		UCHAR freq_diff     : 8;

	} item ;

} TNEW_PDW;

#endif   /* end of ifdef _UNIX */

#endif	// #ifndef _PDW_H_

