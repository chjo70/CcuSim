// CIdAet.cpp: implementation of the CCIdAet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "CIdAet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=3C96D39601F7
CCIdAet::CCIdAet()
{
	gcoLoadIPL = 0;
	gIpl = ( STR_IPL * ) malloc( 20000 * sizeof( STR_IPL ) );
}

//##ModelId=3C96D39601F8
CCIdAet::~CCIdAet()
{
	free( gIpl );
}

//##ModelId=3C96D39601F5
BOOL CCIdAet::IplRead(LPCTSTR lpszPathName)
{
    FILE *iplfile;

    STR_IPL *ptmp;

    UINT i;
    
    char da[1500];
    char str[100];

    iplfile = fopen( lpszPathName , "rt" );          /* open the IPL file    */
    if( iplfile == NULL )
    {
			return FALSE;
    }

    fgets( da, 1500, iplfile );                  /* skip the header of IPL   */
    fgets( da, 1500, iplfile );

    ptmp = &gIpl[1];
    gcoLoadIPL = 0;
		while( ! feof( iplfile ) ) {
			/* Signal Type	*/
			fscanf( iplfile, "%d", &ptmp->sigType );	// dummy ipl #

			fscanf( iplfile, "%d", &ptmp->sigType );

			if( feof( iplfile ) ) {
				break;
			}

			ptmp->noIPL = gcoLoadIPL + 1;

			/* Frequency   */
			fscanf( iplfile, "%d", &ptmp->frq.type );
			fscanf( iplfile, "%s", str );
			ptmp->frq.low = ( UINT ) ( ( double ) atof( str ) );
			fscanf( iplfile, "%s", str );
			ptmp->frq.hgh = ( UINT ) ( ( double ) atof( str ) );
			fscanf( iplfile, "%s", str );
			ptmp->frq.bw = ( UINT ) ( ( double ) atof( str ) );

			fscanf( iplfile, "%d", &ptmp->frq.patType );			// Pattern Type
			fscanf( iplfile, "%d", &ptmp->frq.swtLev );			// Pattern Type
			for( i=0 ; i < _spMaxSwtLev ; ++i ) {
				fscanf( iplfile, "%s", str );
				ptmp->frq.dwLow[i] = ( UINT ) ( ( double ) atof( str ) );
				fscanf( iplfile, "%s", str );
				ptmp->frq.dwHgh[i] = ( UINT ) ( ( double ) atof( str ) );
			}

			fscanf( iplfile, "%s", str );
			ptmp->frq.ppLow = ( UINT ) ( ( double ) atof( str ) );
			fscanf( iplfile, "%s", str );
			ptmp->frq.ppHgh = ( UINT ) ( ( double ) atof( str ) );

			/*  PRI  */
			fscanf( iplfile, "%d", &ptmp->pri.type );
			fscanf( iplfile, "%s", str );
			ptmp->pri.low = ( UINT ) ( ( double ) atof( str ) );
			fscanf( iplfile, "%s", str );
			ptmp->pri.hgh = ( UINT ) ( ( double ) atof( str ) );
			fscanf( iplfile, "%d", &ptmp->pri.patType );
			fscanf( iplfile, "%d", &ptmp->pri.jtrPer );
			fscanf( iplfile, "%d", &ptmp->pri.swtLev );
			for( i=0 ; i < _spMaxSwtLev ; ++i )  {
				fscanf( iplfile, "%s", str );
				ptmp->pri.swtValLow[i] = ( UINT ) ( ( double ) atof( str ) );
				fscanf( iplfile, "%s", str );
				ptmp->pri.swtValHgh[i] = ( UINT ) ( ( double ) atof( str ) );
			}
		fscanf( iplfile, "%d", &ptmp->pri.ppLow );
		fscanf( iplfile, "%d", &ptmp->pri.ppHgh );

		/*	Pulsewidth	*/
		fscanf( iplfile, "%s", str );
		ptmp->pw.low = ( UINT ) ( ( double ) atof( str ) );
		fscanf( iplfile, "%s", str );
		ptmp->pw.hgh = ( UINT ) ( ( double ) atof( str ) );

		/*  Antenna Scan Period */
		fscanf( iplfile, "%d", &ptmp->as.type );
		fscanf( iplfile, "%s", str );
		ptmp->as.prdLow = ( UINT ) ( ( double ) atof( str ) );
		fscanf( iplfile, "%s", str );
		ptmp->as.prdHgh = ( UINT ) ( ( double ) atof( str ) );

		/* Delete Time		*/
		fscanf( iplfile, "%d", &ptmp->tmoDel );

		/* Threat Level */
		fscanf( iplfile, "%d", &ptmp->thrLev );

		/* AutoWarning */
		fscanf( iplfile, "%d", &ptmp->autoWarn );

		/* Elint Notation */
		fscanf( iplfile, "%s", ptmp->elintNot );

		/* Elint Name */
		fscanf( iplfile, "%s", ptmp->elintName );

		/* Category */
		fscanf( iplfile, "%d", &ptmp->cat );

		/* Threat ERP */
		fscanf( iplfile, "%d", &ptmp->thrERP );

		/* Platform name */
		fscanf( iplfile, "%d", &ptmp->platform[0].noplat );
		fscanf( iplfile, "%s", ptmp->platform[0].platName );

		fscanf( iplfile, "%d", &ptmp->platform[1].noplat );
		fscanf( iplfile, "%s", ptmp->platform[1].platName );

		fscanf( iplfile, "%d", &ptmp->platform[2].noplat );
		fscanf( iplfile, "%s", ptmp->platform[2].platName );

		fscanf( iplfile, "%d", &ptmp->platform[3].noplat );
		fscanf( iplfile, "%s", ptmp->platform[3].platName );

		fscanf( iplfile, "%d", &ptmp->platform[4].noplat );
		fscanf( iplfile, "%s", ptmp->platform[4].platName );

#ifdef ID_DEBUG
	  fprintf( stderr, "#" );
#endif

//     	DISP_FineIPL( ptmp );
		++ gcoLoadIPL;
		++ ptmp;
			
  }

	fclose( iplfile );
	return TRUE;

}


//##ModelId=3C96D39601EB
int CCIdAet::GetCoIpl()
{
	return gcoLoadIPL;
}
