/*
*	Copyright (C) 2010
*	Chair of Process Control Engineering,
*	Aachen University of Technology.
*	All rights reserved.
*
*	Redistribution and use in source and binary forms, with or without
*	modification, are permitted provided that the following conditions
*	are met:
*	1. Redistributions of source code must retain the above copyright
*	   notice, this list of conditions and the following disclaimer.
*	2. Redistributions in binary form must print or display the above
*	   copyright notice either during startup or must have a means for
*	   the user to view the copyright notice.
*	3. Redistributions in binary form must reproduce the above copyright
*	   notice, this list of conditions and the following disclaimer in
*		the documentation and/or other materials provided with the
*		distribution.
*	4. Neither the name of the Chair of Process Control Engineering nor
*		the name of the Aachen University of Technology may be used to
*		endorse or promote products derived from this software without
*		specific prior written permission.
*
*	THIS SOFTWARE IS PROVIDED BY THE CHAIR OF PROCESS CONTROL ENGINEERING
*	``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CHAIR OF
*	PROCESS CONTROL ENGINEERING BE LIABLE FOR ANY DIRECT, INDIRECT,
*	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
*	OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
*	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*	WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*	POSSIBILITY OF SUCH DAMAGE.
*/
/******************************************************************************
*
*   FILE
*   ----
*   MID.c
*
*   History
*   -------
*   2010-11-30   File created
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
#include "libov/ov_logfile.h"
#include "libov/ov_string.h"
#include "libov/ov_malloc.h"


OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MID_IN_set(
    OV_INSTPTR_iec61131stdfb_MID          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_IN,value);
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MID_L_set(
    OV_INSTPTR_iec61131stdfb_MID          pobj,
    const OV_UINT  value
) {
    pobj->v_L = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MID_P_set(
    OV_INSTPTR_iec61131stdfb_MID          pobj,
    const OV_UINT  value
) {
    pobj->v_P = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_STRING iec61131stdfb_MID_OUT_get(
    OV_INSTPTR_iec61131stdfb_MID          pobj
) {
    return pobj->v_OUT;
}


OV_DLLFNCEXPORT void iec61131stdfb_MID_shutdown(OV_INSTPTR_ov_object pobj) {

	OV_INSTPTR_iec61131stdfb_MID pinst = Ov_StaticPtrCast(iec61131stdfb_MID, pobj);
	
	ov_string_setvalue(&pinst->v_IN, "");
	ov_string_setvalue(&pinst->v_OUT, "");
	ov_object_shutdown(pobj);
}


OV_DLLFNCEXPORT void iec61131stdfb_MID_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
	
	unsigned int i;
	unsigned int in_length;
	
	OV_STRING p_char;
	
    OV_INSTPTR_iec61131stdfb_MID pinst = Ov_StaticPtrCast(iec61131stdfb_MID, pfb);
	
	ov_string_setvalue(&pinst->v_OUT, "");	//free memory
	
	
	if(!pinst->v_P) //exit, if position is 0
		return;
	
	if(!pinst->v_L)	//exit, if length is 0
		return;
	
	in_length = ov_string_getlength(pinst->v_IN);
	
	if(pinst->v_P <= in_length)
	{
		p_char = (OV_STRING) ov_malloc((pinst->v_L + 1) * sizeof(char));
		if(p_char != NULL)
		{
			for(i=0; i < pinst->v_L; i++)
				if(pinst->v_P - 1 + i < in_length)
					p_char[i] = pinst->v_IN[(pinst->v_P - 1)+ i];
				else
				{
					ov_logfile_warning("%s: next character exceeds input string, stopping operation", pinst->v_identifier);
					break;
				}
			
			p_char[i] = 0;
			ov_string_setvalue(&pinst->v_OUT, p_char);
			ov_free(p_char);
		}
		else
		{
			ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
			return;
		}
	}
	else
	{
		ov_logfile_warning("%s: specified position is not part of the input string", pinst->v_identifier);
	}
	
	
	
    return;
}

