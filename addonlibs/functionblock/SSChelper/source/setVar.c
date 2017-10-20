
/******************************************************************************
*
*   FILE
*   ----
*   setVar.c
*
*   History
*   -------
*   2015-06-01   File created
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

#include "utilities.h"

OV_DLLFNCEXPORT void SSChelper_setVar_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_SSChelper_setVar pinst = Ov_StaticPtrCast(SSChelper_setVar, pfb);
    OV_INSTPTR_ov_object target=NULL;

	SSChelper_getObjectAndVarnameFromSetVariable(Ov_PtrUpCast(ov_object,pinst),pinst->v_path,&target,&pinst->v_port);
	SSChelper_setNamedVariable(target,pinst->v_port,&pinst->v_var);
    return;
}

