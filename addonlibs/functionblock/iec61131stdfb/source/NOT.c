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
*   NOT.c
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
#include "stdfb_macros.h"
#include "libov/ov_macros.h"
#include "libov/ov_logfile.h"
#include "helper.h"


OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_NOT_IN_set(
    OV_INSTPTR_iec61131stdfb_NOT          pobj,
    const OV_ANY*  value
) {
    if((value->value.vartype & OV_VT_KSMASK) == (pobj->v_IN.value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN, value);
	else
	{
		if (iec61131stdfb_isConnected (Ov_PtrUpCast (fb_functionblock, pobj)))
			return OV_ERR_NOACCESS;
		else
		{
			iec61131stdfb_freeVec(&pobj->v_IN);
			iec61131stdfb_freeVec(&pobj->v_OUT);
			switch(value->value.vartype & OV_VT_KSMASK)
			{
				case OV_VT_BOOL:
				case OV_VT_UINT:
				case OV_VT_BYTE:
				case OV_VT_BOOL_VEC:
				case OV_VT_UINT_VEC:
				case OV_VT_BYTE_VEC:
					pobj->v_OUT.value.vartype = value->value.vartype;;
				return ov_variable_setanyvalue(&pobj->v_IN, value);
				
				default:
					return OV_ERR_BADPARAM;
			}
			return OV_ERR_GENERIC;
		}
	}
}

OV_DLLFNCEXPORT OV_ANY* iec61131stdfb_NOT_OUT_get(
    OV_INSTPTR_iec61131stdfb_NOT          pobj
) {
    return &pobj->v_OUT;
}

OV_DLLFNCEXPORT void iec61131stdfb_NOT_destructor(OV_INSTPTR_ov_object pobj) {

	OV_INSTPTR_iec61131stdfb_NOT pinst = Ov_StaticPtrCast(iec61131stdfb_NOT, pobj);
	
	iec61131stdfb_freeVec(&pinst->v_IN);
	iec61131stdfb_freeVec(&pinst->v_OUT);
	fb_functionblock_destructor(pobj);
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_NOT_constructor(OV_INSTPTR_ov_object pobj) {

	OV_RESULT res;
	OV_INSTPTR_iec61131stdfb_NOT pinst = Ov_StaticPtrCast(iec61131stdfb_NOT, pobj);
	
	res = fb_functionblock_constructor(pobj);
	
	if(Ov_OK(res))
	{
		pinst->v_IN.value.valueunion.val_double = 0;
		pinst->v_OUT.value.valueunion.val_double = 0;
		pinst->v_IN.value.vartype = OV_VT_BOOL;
		pinst->v_OUT.value.vartype = OV_VT_BOOL;
		return OV_ERR_OK;
	}
	else
		return res;
}


OV_DLLFNCEXPORT void iec61131stdfb_NOT_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
	
	unsigned int i;
	
    OV_INSTPTR_iec61131stdfb_NOT pinst = Ov_StaticPtrCast(iec61131stdfb_NOT, pfb);
	
	iec61131stdfb_freeVec(&pinst->v_OUT);
	
	if(!(pinst->v_IN.value.vartype & OV_VT_ISVECTOR))
	{
		switch(pinst->v_IN.value.vartype & OV_VT_KSMASK)
		{
			
			case OV_VT_BOOL:
				pinst->v_OUT.value.vartype = OV_VT_BOOL;
				pinst->v_OUT.value.valueunion.val_bool = (! pinst->v_IN.value.valueunion.val_bool);
			break;
			
			case OV_VT_UINT:
				pinst->v_OUT.value.vartype = OV_VT_UINT;
				pinst->v_OUT.value.valueunion.val_uint = (pinst->v_IN.value.valueunion.val_uint ^ 0xFFFFFFFF);
			break;
			
			case OV_VT_BYTE:
				pinst->v_OUT.value.vartype = OV_VT_BYTE;
				pinst->v_OUT.value.valueunion.val_byte = (pinst->v_IN.value.valueunion.val_byte ^ 0xFF);
			break;
				
			default:
				pinst->v_OUT.value.vartype = OV_VT_BOOL;
				pinst->v_OUT.value.valueunion.val_bool = FALSE;
				ov_logfile_alert("%s: logical NOT of given datatype senseless", pinst->v_identifier);
			break;
		}
	}
	else
	{
		switch(pinst->v_IN.value.vartype & OV_VT_KSMASK)
		{
		
			case OV_VT_BOOL_VEC:
				pinst->v_OUT.value.vartype = OV_VT_BOOL_VEC;
				if(Ov_OK(Ov_SetDynamicVectorLength(&pinst->v_OUT.value.valueunion.val_bool_vec, pinst->v_IN.value.valueunion.val_bool_vec.veclen, BOOL)))
				{
					for(i=0; i<pinst->v_IN.value.valueunion.val_bool_vec.veclen; i++)
					{
						pinst->v_OUT.value.valueunion.val_bool_vec.value[i] = (!pinst->v_IN.value.valueunion.val_bool_vec.value[i]);
					}
				}
				else
				{
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
					return;
				}
			break;
		
			case OV_VT_UINT_VEC:
				pinst->v_OUT.value.vartype = OV_VT_UINT_VEC;
				if(Ov_OK(Ov_SetDynamicVectorLength(&pinst->v_OUT.value.valueunion.val_uint_vec, pinst->v_IN.value.valueunion.val_uint_vec.veclen, UINT)))
				{
					for(i=0; i<pinst->v_IN.value.valueunion.val_uint_vec.veclen; i++)
					{
						pinst->v_OUT.value.valueunion.val_uint_vec.value[i] = (pinst->v_IN.value.valueunion.val_uint_vec.value[i] ^ 0xFFFFFFFF);
					}
				}
				else
				{
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
					return;
				}
			break;
			
			case OV_VT_BYTE_VEC:
				pinst->v_OUT.value.vartype = OV_VT_BYTE_VEC;
				if(Ov_OK(Ov_SetDynamicVectorLength(&pinst->v_OUT.value.valueunion.val_byte_vec, pinst->v_IN.value.valueunion.val_byte_vec.veclen, BYTE)))
				{
					for(i=0; i<pinst->v_IN.value.valueunion.val_byte_vec.veclen; i++)
					{
						pinst->v_OUT.value.valueunion.val_byte_vec.value[i] = (pinst->v_IN.value.valueunion.val_byte_vec.value[i] ^ 0xFF);
					}
				}
				else
				{
					ov_logfile_error("%s: allocation of memory failed, no operation performed", pinst->v_identifier);
					return;
				}
			break;
			
			default:
				pinst->v_OUT.value.vartype = OV_VT_BOOL;
					pinst->v_OUT.value.valueunion.val_bool = FALSE;
				ov_logfile_alert("%s: logical NOT of given datatype senseless", pinst->v_identifier);
			break;
		}
	}
	
	/****************** handling states nad timestamp ******************/
	STDFB_STATE(IN);
	STDFB_TIMESTAMP(IN);
	
    return;
}

