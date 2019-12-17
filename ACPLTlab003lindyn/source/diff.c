
/******************************************************************************
*
*   FILE
*   ----
*   diff.c
*
*   History
*   -------
*   2014-06-03   File created
*   author  : Constantin Wagner, Chair of Process Control Engineering, RWTH Aachen
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_ACPLTlab003lindyn
#define OV_COMPILE_LIBRARY_ACPLTlab003lindyn
#endif


#include "ACPLTlab003lindyn.h"
#include "ov_macros.h"
#include "ov_time.h"

OV_DLLFNCEXPORT void ACPLTlab003lindyn_diff_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
	OV_TIME_SPAN temp;
	double dbl=0;
    OV_INSTPTR_ACPLTlab003lindyn_diff pinst = Ov_StaticPtrCast(ACPLTlab003lindyn_diff, pfb);
    if(pinst->v_methcount>1){
    	ov_time_diff( &temp, pltc,&(pinst->v_timeold)) ;
    	Ov_TimeSpanToDouble(temp, dbl);
    	pinst->v_XOUT=pinst->v_KD*(pinst->v_XIN-pinst->v_xold) /dbl;
    }

    pinst->v_ENO=pinst->v_EN;

    pinst->v_xold=pinst->v_XIN;
    pinst->v_timeold=*pltc;
    return;
}

