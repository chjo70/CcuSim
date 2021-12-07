// CIdAet.h: interface for the CCIdAet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIDAET_H__83378F32_4AD6_4CB3_B477_277A402640E7__INCLUDED_)
#define AFX_CIDAET_H__83378F32_4AD6_4CB3_B477_277A402640E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./BSP/hw_def.h"
#include "./BSP/hw_str.h"

#include "./INC/_pdw.h"
#include "./INC/_aetipl.h"
#include "./INC/_system.h"
#include "./INC/_sysmsg.h"

//##ModelId=3C96D39601BA
typedef unsigned int IPLINDEX;


/////////////////////////////////////////////////////////////////////////////////////////
//  주파수 테이블화 구조체 
//
//##ModelId=3C96D39601CD
class CCIdAet  
{
protected:
	//##ModelId=3C96D39601CE
	int        		gcoLoadIPL;         // The total number of IPL
public:

public:


	//##ModelId=3C96D39601D8
	STR_IPL     	*gpIpl;             // pointer of gIpl
	//##ModelId=3C96D39601E2
	STR_IPL     	*gIpl;							// IPL record variable

public:
	//##ModelId=3C96D39601EB
	int GetCoIpl( void );
	//##ModelId=3C96D39601F5
	BOOL IplRead(LPCTSTR lpszPathName);
	//##ModelId=3C96D39601F7
	CCIdAet();
	//##ModelId=3C96D39601F8
	virtual ~CCIdAet();

};

#endif // !defined(AFX_CIDAET_H__83378F32_4AD6_4CB3_B477_277A402640E7__INCLUDED_)
