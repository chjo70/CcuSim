// CnfSys.h: interface for the CCnfSys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNFSYS_H__1BDF07D8_4599_4177_8ADD_C19F12048A07__INCLUDED_)
#define AFX_CNFSYS_H__1BDF07D8_4599_4177_8ADD_C19F12048A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./BSP/hw_def.h"
#include "./BSP/hw_str.h"

#include "./INC/_pdw.h"
#include "./INC/_aetipl.h"
#include "./INC/_system.h"
#include "./INC/_sysmsg.h"

#define SYS_FILENAME "sysdata.txt"

class CCnfSys  
{
public:
	STR_SYS m_sp;
	STR_CNFSYS m_cnfsys;
	
public:
	UINT SaveToVariable( char *str,FILE *sysfile, UINT line );
	UINT SaveToVariable2( char *str,FILE *sysfile, UINT line );
	int SysRead( void );
	CCnfSys();
	virtual ~CCnfSys();

};

#endif // !defined(AFX_CNFSYS_H__1BDF07D8_4599_4177_8ADD_C19F12048A07__INCLUDED_)
