/*
*   Copyright (C) 2010
*   Chair of Process Control Engineering,
*   D-52056 Aachen, Germany.
*   All rights reserved.
*
*
*   This file is part of the ACPLT/OV Package 
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*/
/******************************************************************************
*
*   FILE
*   ----
*   ROL.c
*
*   History
*   -------
*   2010-12-15   File created
*
*******************************************************************************
*
*   This file is generated by the 'fb_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_iec61131stdfb
#define OV_COMPILE_LIBRARY_iec61131stdfb
#endif


#include "iec61131stdfb.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_ROL_IN_set(
    OV_INSTPTR_iec61131stdfb_ROL          pobj,
    const OV_UINT  value
) {
    pobj->v_IN = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_ROL_N_set(
    OV_INSTPTR_iec61131stdfb_ROL          pobj,
    const OV_UINT  value
) {
    pobj->v_N = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_UINT iec61131stdfb_ROL_OUT_get(
    OV_INSTPTR_iec61131stdfb_ROL          pobj
) {
    return pobj->v_OUT;
}


OV_DLLFNCEXPORT void iec61131stdfb_ROL_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_iec61131stdfb_ROL pinst = Ov_StaticPtrCast(iec61131stdfb_ROL, pfb);

	pinst->v_N = pinst->v_N % (8 * sizeof(OV_UINT));	//rotation is periodic
	pinst->v_OUT = pinst->v_IN << pinst->v_N | pinst->v_IN >> ((8 * sizeof(OV_UINT)) - pinst->v_N);
	
    return;
}

