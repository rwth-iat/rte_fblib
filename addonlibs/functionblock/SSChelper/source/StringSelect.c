
/******************************************************************************
*
*   FILE
*   ----
*   StringSelect.c
*
*   History
*   -------
*   2017-09-26   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_SSChelper
#define OV_COMPILE_LIBRARY_SSChelper
#endif


#include "SSChelper.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT void SSChelper_StringSelect_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_SSChelper_StringSelect pinst = Ov_StaticPtrCast(SSChelper_StringSelect, pfb);

    if(pinst->v_Q == FALSE){
    	ov_string_setvalue(&pinst->v_OUT, pinst->v_IN1);
    }
    else {
    	ov_string_setvalue(&pinst->v_OUT, pinst->v_IN2);
    }
    return;
}

