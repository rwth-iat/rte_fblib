
/******************************************************************************
*
*   FILE
*   ----
*   commandCreator.c
*
*   History
*   -------
*   2015-06-15   File created
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


OV_DLLFNCEXPORT OV_RESULT SSChelper_commandCreator_start_set(
    OV_INSTPTR_SSChelper_commandCreator          pobj,
    const OV_BOOL  value
) {
    pobj->v_start = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void SSChelper_commandCreator_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_SSChelper_commandCreator pinst = Ov_StaticPtrCast(SSChelper_commandCreator, pfb);

    return;
}

