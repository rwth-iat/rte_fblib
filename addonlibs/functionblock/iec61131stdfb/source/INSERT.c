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
*   INSERT.c
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
#include "libov/ov_malloc.h"
#include "libov/ov_string.h"


OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_INSERT_IN1_set(
    OV_INSTPTR_iec61131stdfb_INSERT          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_IN1,value);
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_INSERT_IN2_set(
    OV_INSTPTR_iec61131stdfb_INSERT          pobj,
    const OV_STRING  value
) {
    return ov_string_setvalue(&pobj->v_IN2,value);
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_INSERT_P_set(
    OV_INSTPTR_iec61131stdfb_INSERT          pobj,
    const OV_UINT  value
) {
    pobj->v_P = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_STRING iec61131stdfb_INSERT_OUT_get(
    OV_INSTPTR_iec61131stdfb_INSERT          pobj
) {
    return pobj->v_OUT;
}


OV_DLLFNCEXPORT void iec61131stdfb_INSERT_destructor(OV_INSTPTR_ov_object pobj) {

	OV_INSTPTR_iec61131stdfb_INSERT pinst = Ov_StaticPtrCast(iec61131stdfb_INSERT, pobj);
	
	ov_string_setvalue(&pinst->v_IN1, "");
	ov_string_setvalue(&pinst->v_IN2, "");
	ov_string_setvalue(&pinst->v_OUT, "");
	fb_functionblock_destructor(pobj);
}


OV_DLLFNCEXPORT void iec61131stdfb_INSERT_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
	unsigned int i;
	unsigned int in_length;
	unsigned int end_length;
	
	OV_STRING p_begin;
	OV_STRING p_end;
	
    OV_INSTPTR_iec61131stdfb_INSERT pinst = Ov_StaticPtrCast(iec61131stdfb_INSERT, pfb);
	
	ov_string_setvalue(&pinst->v_OUT, "");
	
	in_length = ov_string_getlength(pinst->v_IN1);
	
	if(pinst->v_P < in_length)
	{
		if(pinst->v_P == 0)
		{
			ov_logfile_error("%s: specified position outside input string", pinst->v_identifier);
			return;
		}
		
		end_length = in_length - (pinst->v_P - 1);
		
		p_begin = (OV_STRING) ov_malloc((pinst->v_P + 1) * sizeof(char));
		p_end = (OV_STRING) ov_malloc((end_length + 1) * sizeof(char));
		if(((p_begin != NULL) && (p_end != NULL)))
		{
			for(i=0; i < pinst->v_P - 1; i++)
				p_begin[i] = pinst->v_IN1[i];
			p_begin[i] = 0;
			
			for(i=0; i < end_length; i++)
				p_end[i] = pinst->v_IN1[i + pinst->v_P - 1];
			p_end[i] = 0;
			
			if(Ov_Fail(ov_string_setvalue(&pinst->v_OUT, p_begin)))
				if(pinst->v_P != 1)
				{
					ov_free(p_begin);
					ov_free(p_end);
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
					return;
				}			
				
			if(Ov_Fail(ov_string_append(&pinst->v_OUT, pinst->v_IN2)))
				if(ov_string_getlength(pinst->v_IN2) > 0)
				{
					ov_free(p_begin);
					ov_free(p_end);
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
					return;
				}
				
			if(Ov_Fail(ov_string_append(&pinst->v_OUT, p_end)))
				if(end_length != 0)
				{
					ov_free(p_begin);
					ov_free(p_end);
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
					return;
				}
					
					
			ov_free(p_begin);
			ov_free(p_end);
		}
		else
		{
			ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
			ov_free(p_begin);
			ov_free(p_end);
			return;
		}
	}
	else
	{
		if(Ov_OK(ov_string_setvalue(&pinst->v_OUT, pinst->v_IN1)))
		{
			if(Ov_Fail(ov_string_append(&pinst->v_OUT, pinst->v_IN2)))
			{
				if(ov_string_getlength(pinst->v_IN2) > 0)
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
			}
		}
		else
		{
			if(ov_string_getlength(pinst->v_IN1) > 0)
				ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
		}
		
		if(pinst->v_P > in_length)
			ov_logfile_alert("%s: position is not inside input string, concatinating", pinst->v_identifier);
	}

    return;
}

