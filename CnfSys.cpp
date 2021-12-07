// CnfSys.cpp: implementation of the CCnfSys class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ccusim.h"
#include "CnfSys.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCnfSys::CCnfSys()
{

}

CCnfSys::~CCnfSys()
{

}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CCnfSys::SysRead
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-11-13 19:17:31
//
int CCnfSys::SysRead()
{
  FILE *sysfile;

  UINT *ptmp;

  UINT line;

  printf( "\n STR_SYS's size[%d byte]", sizeof( STR_SYS ) );

  memset( & m_sp, 0xf0, sizeof( STR_SYS ) );
  m_sp.date = time( NULL );
  //  sp.time - time(NULL);

  sysfile = fopen( SYS_FILENAME, "rt" );          /* open the IPL file    */
  if( sysfile == NULL ) {
    fprintf( stderr, "[Error] Can not open the SYS file. \n ( in %d Line(s), %s File)", __LINE__, __FILE__ );
    fprintf( stderr, " SYS DATA All 0xffffffff" );
    return 0;
  }

  ptmp = ( UINT * ) & m_sp;
  line = 1;
  while( !feof( sysfile ) ) {
    UINT bret;
    char str[ 100 ];
    char cat[ 100 ];

    cat[ 0 ] = fgetc( sysfile );
    cat[ 1 ] = NULL;
    if( cat[ 0 ] == '#' || cat[ 0 ] == '\t' || cat[ 0 ] == ' ' ) {
      char key;

      //      printf( "\n---------------------------------" );
      do {
        key = fgetc( sysfile );
        //        printf( "%1c" , key );
      }
      while( key != 0x0d && key != 0x0a && !feof( sysfile ) );
      //      printf( "\n---------------------------------" );

      ++ line;
    }
    else if( cat[ 0 ] != 0x0d && cat[ 0 ] != 0x0a && !feof( sysfile ) ) {
      fscanf( sysfile, "\n%s\t", str );
      strcat( cat, str );
      bret = SaveToVariable( cat, sysfile, line );
			if( bret == _spFalse )
				bret = SaveToVariable2( cat, sysfile, line );

      if( bret == _spTrue ) {
        //        printf( "\n %s->%d" , cat, val );
      }
      else {
        //        printf( "\n Invalid lines[%d]" , line );
      }
    }
    else if( cat[ 0 ] == 0x0d || cat[ 0 ] == 0x0a ) {
      ++ line;
      //      printf( "\n Dummy lines[%d]", line );
    }
  }

  //  printf( "\n-------------------------------------------------------------------------------------------------");
	/*
  ptmp = ( UINT * ) & m_sp;
  for( i = 0 ; i < sizeof( STR_SYS ) / sizeof( UINT ) ; ++i ) {
    if( *ptmp++ == 0xf0f0f0f0 ) {
      printf( "[%d]", i );  WhereIs;
    }
  }
	*/

  fclose( sysfile );

  return line;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CCnfSys::SaveToVariable
//! \author   조철희
//! \param    str 인자형태 char *
//! \param    sysfile 인자형태 FILE *
//! \param    line 인자형태 UINT
//! \return   UINT
//! \version  1.37
//! \date     2006-11-13 20:53:51
//! \warning
//
UINT CCnfSys::SaveToVariable( char *str,FILE *sysfile, UINT line ) 
{
	UINT        val;
	float	   fval;
    
  val = 123456;

	if( strcmp( str, "spaoadiff1" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spaoadiff[1-1] );
		return _spTrue;
	}
  else if( strcmp( str, "spaoadiff2" ) == 0 ) {
    fscanf( sysfile, "%d", & m_cnfsys.spaoadiff[2-1] );
    return _spTrue;
  }
  else if( strcmp( str, "spaoadiff3" ) == 0 ) {
    fscanf( sysfile, "%d", & m_cnfsys.spaoadiff[3-1] );
    return _spTrue;
  }
  else if( strcmp( str, "spfrqdiff1" ) == 0 ) {
    fscanf( sysfile, "%d", & m_cnfsys.spfrqdiff[1-1] );
    return _spTrue;
  }
	else if( strcmp( str, "spfrqdiff2" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spfrqdiff[2-1] );
		return _spTrue;
	}
	else if( strcmp( str, "spfrqdiff3" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spfrqdiff[3-1] );
		return _spTrue;
	}
	else if( strcmp( str, "sptrkaoa" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.sptrkaoa );
		return _spTrue;
	}
	else if( strcmp( str, "sptrkfixfrq" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.sptrkfixfrq );
		return _spTrue;
	}
	else if( strcmp( str, "sptrkagifrq" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.sptrkagifrq );
		return _spTrue;
	}
	else if( strcmp( str, "spmrgaoa" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spmrgaoa );
		return _spTrue;
	}
	else if( strcmp( str, "spmrgfrq" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spmrgfrq );
		return _spTrue;
	}
	else if( strcmp( str, "spminstb" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spminstb );
		return _spTrue;
	}
	else if( strcmp( str, "spminjit" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spminjit );
		return _spTrue;
	}
	else if( strcmp( str, "spminrefpri" ) == 0 ) {
			fscanf( sysfile, "%d", & m_cnfsys.spminrefpri );
			return _spTrue;
	}
	else if( strcmp( str, "spminagipri" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spminagipri );
		return _spTrue;
	}
	else if( strcmp( str, "spshiftaoa" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spshiftaoa );
		return _spTrue;
	}
	else if( strcmp( str, "spshiftfrq" ) == 0 ) {
		fscanf( sysfile, "%d", & m_cnfsys.spshiftfrq );
		return _spTrue;
	}
	else if( strcmp( str, "Mode" ) == 0 ) {
		fscanf( sysfile, "%d", & val );
		m_sp.mode = val;
		return _spTrue;
	}
	else if( strcmp( str, "Ver" ) == 0 ) {
		memset( & m_sp.ver[0], 0, sizeof( UINT ) * 2 );
		fscanf( sysfile, "%s", & m_sp.ver[0] );
		return _spTrue;
	}
	else if( strcmp( str, "ScanLevel" ) == 0 ) {
		fscanf( sysfile, "%d", & val );	    
		m_sp.scnLev = val;
		return _spTrue;
	}
	else if( strcmp( str, "_spRxdfAoaLow" ) == 0 ) {
		m_sp.sp.aoadiff[0] = _spZero;
		fscanf( sysfile, "%d", & val );	    
		m_sp.sp.aoadiff[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "_spRxdfAoaMid" ) == 0 ) {
		fscanf( sysfile, "%d", & val );	    
		m_sp.sp.aoadiff[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "_spRxdfAoaHgh" ) == 0 ) {
		fscanf( sysfile, "%d", & val );	    
		m_sp.sp.aoadiff[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "_spRxdfFrqLow" ) == 0 ) {
		m_sp.sp.frqdiff[0] = _spZero;
		fscanf( sysfile, "%d", & val );	    
		m_sp.sp.frqdiff[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "_spRxdfFrqMid" ) == 0 ) {
		fscanf( sysfile, "%d", & val );	    
		m_sp.sp.frqdiff[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "_spRxdfFrqHgh" ) == 0 ) {
		fscanf( sysfile, "%d", & val );	    
		m_sp.sp.frqdiff[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "PdwBand1Low" ) == 0 ) {
		m_sp.pw.frq[0].low = _spZero;
		m_sp.pw.frq[0].hgh = _spZero;
		fscanf( sysfile, "%d", & val );	    
		m_sp.pw.frq[1].low = val;
		return _spTrue;
	}
	else if( strcmp( str, "PdwBand1Hgh" ) == 0 ) {
		m_sp.pw.frq[0].low = _spZero;
		m_sp.pw.frq[0].hgh = _spZero;
		fscanf( sysfile, "%d", & val );
		m_sp.pw.frq[1].hgh = val;
		return _spTrue;
	}
  else if( strcmp( str, "PdwBand2Low" ) == 0 ) {
		m_sp.pw.frq[0].low = _spZero;
		m_sp.pw.frq[0].hgh = _spZero;
    fscanf( sysfile, "%d", & val );
    m_sp.pw.frq[2].low = val;
    return _spTrue;
  }
  else if( strcmp( str, "PdwBand2Hgh" ) == 0 ) {
		m_sp.pw.frq[0].low = _spZero;
		m_sp.pw.frq[0].hgh = _spZero;
		fscanf( sysfile, "%d", & val );
		m_sp.pw.frq[2].hgh = val;
		return _spTrue;
  }
  else if( strcmp( str, "PdwBand3Low" ) == 0 ) {
		m_sp.pw.frq[0].low = _spZero;
		m_sp.pw.frq[0].hgh = _spZero;
    fscanf( sysfile, "%d", & val );
    m_sp.pw.frq[3].low = val;
    return _spTrue;
	}
  else if( strcmp( str, "PdwBand3Hgh" ) == 0 ) {
		m_sp.pw.frq[0].low = _spZero;
		m_sp.pw.frq[0].hgh = _spZero;
		fscanf( sysfile, "%d", & val );
		m_sp.pw.frq[3].hgh = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAoaLow" ) == 0 ) {
		m_sp.mg.aoa[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.aoa[1] = val;
		return _spTrue;
	}
  else if( strcmp( str, "MergeAoaMid" ) == 0 ) {
		m_sp.mg.aoa[0] = _spZero;
    fscanf( sysfile, "%d", & val );
    m_sp.mg.aoa[2] = val;
    return _spTrue;
  }
  else if( strcmp( str, "MergeAoaHgh" ) == 0 ) {
		m_sp.mg.aoa[0] = _spZero;
    fscanf( sysfile, "%d", & val );
    m_sp.mg.aoa[3] = val;
    return _spTrue;
  }
	else if( strcmp( str, "MergeStableFrqLow" ) == 0 ) {
		m_sp.mg.fixfrq[0] = _spZero;
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.fixfrq[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeStableFrqMid" ) == 0 ) {
		m_sp.mg.fixfrq[0] = _spZero;
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.fixfrq[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeStableFrqHgh" ) == 0 ) {
		m_sp.mg.fixfrq[0] = _spZero;
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.fixfrq[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiFrqMean" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agifrqmean = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiFrqIn" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agifrqin = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiFrqOut" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agifrqout = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeFrqPatPrd" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.frqPrd = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiLowFrqPat" ) == 0 ) {
		m_sp.mg.agifrqpat[0] = _spZero;
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agifrqpat[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiMidFrqPat" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agifrqpat[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiHghFrqPat" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agifrqpat[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeStablePri" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.fixpri = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiPriMean" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agiprimean = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiPriIn" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agipriin = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgiPriOut" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.agipriout = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeJitPer" ) == 0 ) {
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.jtrper = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgileBWLow" ) == 0 ) {
		m_sp.mg.md_agifrq[0] = _spZero;
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.md_agifrq[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgileBWMid" ) == 0 ) {
		m_sp.mg.md_agifrq[0] = _spZero;
	  fscanf( sysfile, "%d", & val );
		m_sp.mg.md_agifrq[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeAgileBWHgh" ) == 0 ) {
		m_sp.mg.md_agifrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.md_agifrq[3] = val;
		return _spTrue;
	}

	else if( strcmp( str, "MergeAgiPriPat" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.agipripat = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergePriPatPrd" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.priPrd = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergeScnPrd" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.scnPrd = val;
		return _spTrue;
	}
	else if( strcmp( str, "MergePW" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.pw = val;
		return _spTrue;
	}
	else if( strcmp( str, "ModifyMethod" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.mg.mdyMethod = val;
		return _spTrue;
	}

	else if( strcmp( str, "TkWcStableFrqLow" ) == 0 ) {
		m_sp.ft.fixfrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.fixfrq[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcStableFrqMid" ) == 0 ) {
		m_sp.ft.fixfrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.fixfrq[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcStableFrqHgh" ) == 0 ) {
		m_sp.ft.fixfrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.fixfrq[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAgileFrqLow" ) == 0 ) {
		m_sp.ft.fixfrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.agifrq[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAgileFrqMid" ) == 0 ) {
		m_sp.ft.agifrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.agifrq[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAgileFrqHgh" ) == 0 ) {
		m_sp.ft.agifrq[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.agifrq[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAgileRatio" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.agiratio = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAoaLow" ) == 0 ) {
		m_sp.ft.aoa[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.aoa[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAoaMid" ) == 0 ) {
		m_sp.ft.aoa[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.aoa[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAoaHgh" ) == 0 ) {
		m_sp.ft.aoa[0] = _spZero;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.aoa[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcCWTo" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.CWTo = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcCWPc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.CWPc = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcNormPc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.normPc = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcAbnormPc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.abnormPc = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcChirpTo" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.chirpTo = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcChirpPc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.chirpPc = val;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcTimesOfScan" ) == 0 ) {
	    fscanf( sysfile, "%f", & fval );
		m_sp.ft.maxTim = fval;
		return _spTrue;
	}
	else if( strcmp( str, "TkWcTimesOfPatPrd" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.timPrd = val;
		return _spTrue;
	}

    else if( strcmp( str, "PdwTkToLow" ) == 0 ) {
        fscanf( sysfile, "%d", & val );
        m_sp.ft.tkto.low = val;
        return _spTrue;
    }
    else if( strcmp( str, "PdwTkToHgh" ) == 0 ) {
        fscanf( sysfile, "%d", & val );
        m_sp.ft.tkto.hgh = val;
        return _spTrue;
    }
    else if( strcmp( str, "PdwTkPcLow" ) == 0 ) {
        fscanf( sysfile, "%d", & val );
        m_sp.ft.tkpc.low = val;
        return _spTrue;
    }
    else if( strcmp( str, "PdwTkPcHgh" ) == 0 ) {
        fscanf( sysfile, "%d", & val );
        m_sp.ft.tkpc.hgh = val;
        return _spTrue;
    }

	else if( strcmp( str, "ScWcToStep1" ) == 0 ) {
		m_sp.ft.scto[5] = -1;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.scto[0] = val;
		return _spTrue;
	}
	else if( strcmp( str, "ScWcToStep2" ) == 0 ) {
		m_sp.ft.scto[5] = -1;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.scto[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "ScWcToStep3" ) == 0 ) {
		m_sp.ft.scto[5] = -1;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.scto[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "ScWcToStep4" ) == 0 ) {
		m_sp.ft.scto[5] = -1;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.scto[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "ScWcToStep5" ) == 0 ) {
		m_sp.ft.scto[5] = -1;
	    fscanf( sysfile, "%d", & val );
		m_sp.ft.scto[4] = val;
		return _spTrue;
	}

	// ANAL Scan Parameter	
	else if( strcmp( str, "SamplingTimeOfStep1" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.st[0] = 0;
		return _spTrue;
	}
	else if( strcmp( str, "SamplingTimeOfStep2" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.st[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "SamplingTimeOfStep3" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.st[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "SamplingTimeOfStep4" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.st[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "SamplingTimeOfStep5" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.st[4] = val;
		return _spTrue;
	}
	else if( strcmp( str, "InterPulseOfStep1" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.offst[0] = val;
		return _spTrue;
	}
	else if( strcmp( str, "InterPulseOfStep2" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.offst[1] = val;
		return _spTrue;
	}
	else if( strcmp( str, "InterPulseOfStep3" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.offst[2] = val;
		return _spTrue;
	}
	else if( strcmp( str, "InterPulseOfStep4" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.offst[3] = val;
		return _spTrue;
	}
	else if( strcmp( str, "InterPulseOfStep5" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.offst[4] = val;
		return _spTrue;
	}
	else if( strcmp( str, "MaxScanPrdOfTrkSig" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.thtrkprd = val;
		return _spTrue;
	}

	printf( "\n Invalid system identity[%s] in %d lines." , str, line );
	return _spFalse;

}


//////////////////////////////////////////////////////////////////////
//
//! \brief    CCnfSys::SaveToVariable2
//! \author   조철희
//! \param    str 인자형태 char *
//! \param    sysfile 인자형태 FILE *
//! \param    line 인자형태 UINT
//! \return   UINT
//! \version  1.37
//! \date     2006-11-13 20:53:51
//! \warning
//
UINT CCnfSys::SaveToVariable2( char *str,FILE *sysfile, UINT line ) 
{
	UINT        val;

	// 서성태 SST
	// NSP
	if( strcmp( str, "_sp.np.Pdw_Max" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Pdw_Max = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Aoa_Shift_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Aoa_Shift_Cnt = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Aoa_Peak_Thr" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Aoa_Peak_Thr = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Aoa_Hist_Thr" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Aoa_Hist_Thr = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Aoa_Range_Margin" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Aoa_Range_Margin = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Freq_Shift_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Freq_Shift_Cnt = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Freq_Peak_Thr" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Freq_Peak_Thr = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Freq_Hist_Thr" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Freq_Hist_Thr = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Freq_Range_Margin" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Freq_Range_Margin = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.np.Rpt_Aet_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.np.Rpt_Aet_Cnt = val;
		return _spTrue;
	}
	
	// KSP
	else if( strcmp( str, "_sp.kp.Pdw_Max" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.kp.Pdw_Max = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.kp.Rpt_Aet_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.kp.Rpt_Aet_Cnt = val;
		return _spTrue;
	}
	
	// SAP
	else if( strcmp( str, "_sp.sc.Pdw_Max" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.sc.Pdw_Max = val;
		return _spTrue;
	}
	
	// COMMON
	else if( strcmp( str, "_sp.cm.Cw_Min_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Cw_Min_Cnt = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Mpc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Mpc = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Mjpc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Mjpc = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Rpc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Rpc = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Rjgpc" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Rjgpc = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Stb_Max_Miss" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Stb_Max_Miss = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Jit_Max_Miss" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Jit_Max_Miss = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Reflex_Zone" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Reflex_Zone = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Hprf_First_Pri" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Hprf_First_Pri = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Jitter_P" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Jitter_P = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Dtoa_Sd" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Dtoa_Sd = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Freq_Sd" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Freq_Sd = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Jstg_Pt_P" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Jstg_Pt_P = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Jit_Merge_Miss_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Jit_Merge_Miss_Cnt = val;
		return _spTrue;
	}
	
	// PAT
	else if( strcmp( str, "_sp.cm.Pat_Min_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Pat_Min_Cnt = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Lhp" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Lhp = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Cross_Over" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Cross_Over = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Lhp_Thresh" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Lhp_Thresh = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Bad_Max" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Bad_Max = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Filt_Fac" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Filt_Fac = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Maxparam_Min" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Maxparam_Min = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Pp_Max_Margin_P" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Pp_Max_Margin_P = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Pp_Match_P" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Pp_Match_P = val;
		return _spTrue;
	}

	// AET
	else if( strcmp( str, "_sp.cm.Conti_Thr" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Conti_Thr = val;
		return _spTrue;
	}
	else if( strcmp( str, "_sp.cm.Rpt_Pul_Cnt" ) == 0 ) {
	    fscanf( sysfile, "%d", & val );
		m_sp.cm.Rpt_Pul_Cnt = val;
		return _spTrue;
	}
	
	printf( "\n Invalid system identity[%s] in %d lines." , str, line );
	return _spFalse;

}

