
/******************************************************************************
*
*   FILE
*   ----
*   linkObject.c
*
*   History
*   -------
*   2013-05-18   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_fbcomlib
#define OV_COMPILE_LIBRARY_fbcomlib
#endif


#include "fbcomlib.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_BOOL fbcomlib_linkObject_doReset_get(
    OV_INSTPTR_fbcomlib_linkObject          pobj
) {
    return pobj->v_doReset;
}

OV_DLLFNCEXPORT OV_RESULT fbcomlib_linkObject_doReset_set(
    OV_INSTPTR_fbcomlib_linkObject          pobj,
    const OV_BOOL  value
) {
    pobj->v_doReset = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void fbcomlib_linkObject_startup(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_fbcomlib_linkObject pinst = Ov_StaticPtrCast(fbcomlib_linkObject, pobj);

    /* do what the base class does first */
    fb_functionblock_startup(pobj);

    /* do what */


    return;
}

OV_DLLFNCEXPORT void fbcomlib_linkObject_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_fbcomlib_linkObject pinst = Ov_StaticPtrCast(fbcomlib_linkObject, pfb);

    return;
}

