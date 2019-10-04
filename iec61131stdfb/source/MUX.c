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
*   MUX.c
*
*   History
*   -------
*   2010-12-01   File created
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
#include "ov_macros.h"
#include "ov_logfile.h"
#include "helper.h"

OV_RESULT
iec61131stdfb_MUX_setType
(OV_INSTPTR_iec61131stdfb_MUX pobj, OV_VAR_TYPE type)
{
  if (iec61131stdfb_isConnected (Ov_PtrUpCast (fb_functionblock, pobj)))
    return OV_ERR_NOACCESS;
  else
  {
	if(type == OV_VT_VOID)
		return OV_ERR_BADPARAM;
	else
	{
		iec61131stdfb_freeVec(&pobj->v_IN1);
		iec61131stdfb_freeVec(&pobj->v_IN2);
		iec61131stdfb_freeVec(&pobj->v_IN3);
		iec61131stdfb_freeVec(&pobj->v_IN4);
		iec61131stdfb_freeVec(&pobj->v_IN5);
		iec61131stdfb_freeVec(&pobj->v_IN6);
		iec61131stdfb_freeVec(&pobj->v_IN7);
		iec61131stdfb_freeVec(&pobj->v_IN8);
		pobj->v_IN1.value.vartype = type;
		pobj->v_IN2.value.vartype = type;
		pobj->v_IN3.value.vartype = type;
		pobj->v_IN4.value.vartype = type;
		pobj->v_IN5.value.vartype = type;
		pobj->v_IN6.value.vartype = type;
		pobj->v_IN7.value.vartype = type;
		pobj->v_IN8.value.vartype = type;
		return OV_ERR_OK;
	}
    
  }
}




OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_K_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_UINT  value
) {
    if(value >= 1 && value <= 8)
	{
		pobj->v_K = value;
		return OV_ERR_OK;
	}
	else
		return OV_ERR_BADPARAM;
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN1_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
	OV_RESULT res;
	
	if((pobj->v_IN1.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN1, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN1, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN2_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN2.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN2, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN2, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN3_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN3.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN3, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN3, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN4_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN4.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN4, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN4, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN5_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN5.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN5, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN5, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN6_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN6.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN6, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN6, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN7_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN7.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN7, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN7, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_IN8_set(
    OV_INSTPTR_iec61131stdfb_MUX          pobj,
    const OV_ANY*  value
) {
    OV_RESULT res;
	
	if((pobj->v_IN8.value.vartype & OV_VT_KSMASK) == (value->value.vartype & OV_VT_KSMASK))
		return ov_variable_setanyvalue(&pobj->v_IN8, value);
	else
	{
		res = iec61131stdfb_MUX_setType(pobj, value->value.vartype);
		if(Ov_OK(res))
			return ov_variable_setanyvalue(&pobj->v_IN8, value);
		else
			return res;
	}
}

OV_DLLFNCEXPORT OV_ANY* iec61131stdfb_MUX_OUT_get(
    OV_INSTPTR_iec61131stdfb_MUX          pobj
) {
    return &pobj->v_OUT;
}


OV_DLLFNCEXPORT void iec61131stdfb_MUX_destructor(OV_INSTPTR_ov_object pobj) {

	OV_INSTPTR_iec61131stdfb_MUX pinst = Ov_StaticPtrCast(iec61131stdfb_MUX, pobj);
	
	iec61131stdfb_freeVec(&pinst->v_IN1);
	iec61131stdfb_freeVec(&pinst->v_IN2);
	iec61131stdfb_freeVec(&pinst->v_IN3);
	iec61131stdfb_freeVec(&pinst->v_IN4);
	iec61131stdfb_freeVec(&pinst->v_IN5);
	iec61131stdfb_freeVec(&pinst->v_IN6);
	iec61131stdfb_freeVec(&pinst->v_IN7);
	iec61131stdfb_freeVec(&pinst->v_IN8);
	iec61131stdfb_freeVec(&pinst->v_OUT);
	fb_functionblock_destructor(pobj);
}


OV_DLLFNCEXPORT OV_RESULT iec61131stdfb_MUX_constructor(OV_INSTPTR_ov_object pobj) {

	OV_RESULT res;
	OV_INSTPTR_iec61131stdfb_MUX pinst = Ov_StaticPtrCast(iec61131stdfb_MUX, pobj);
	
	res = fb_functionblock_constructor(pobj);
	
	if(Ov_OK(res))
	{
		pinst->v_IN1.value.valueunion.val_double = 0;
		pinst->v_IN2.value.valueunion.val_double = 0;
		pinst->v_IN3.value.valueunion.val_double = 0;
		pinst->v_IN4.value.valueunion.val_double = 0;
		pinst->v_IN5.value.valueunion.val_double = 0;
		pinst->v_IN6.value.valueunion.val_double = 0;
		pinst->v_IN7.value.valueunion.val_double = 0;
		pinst->v_IN8.value.valueunion.val_double = 0;
		pinst->v_OUT.value.valueunion.val_double = 0;
		pinst->v_IN1.value.vartype = OV_VT_SINGLE;
		pinst->v_IN2.value.vartype = OV_VT_SINGLE;
		pinst->v_IN3.value.vartype = OV_VT_SINGLE;
		pinst->v_IN4.value.vartype = OV_VT_SINGLE;
		pinst->v_IN5.value.vartype = OV_VT_SINGLE;
		pinst->v_IN6.value.vartype = OV_VT_SINGLE;
		pinst->v_IN7.value.vartype = OV_VT_SINGLE;
		pinst->v_IN8.value.vartype = OV_VT_SINGLE;
		pinst->v_OUT.value.vartype = OV_VT_SINGLE;
		return OV_ERR_OK;
	}
	else
		return res;
}

OV_DLLFNCEXPORT void iec61131stdfb_MUX_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
	
	unsigned int i;
	
	
    OV_INSTPTR_iec61131stdfb_MUX pinst = Ov_StaticPtrCast(iec61131stdfb_MUX, pfb);

	iec61131stdfb_freeVec(&pinst->v_OUT);
	
	switch(pinst->v_K)
	{
		case 1:
			STDFB_DEMUX(1);
			STDFB_STATE(IN1);
			STDFB_TIMESTAMP(IN1);
		
		break;
		
		case 2:
			STDFB_DEMUX(2);
			STDFB_STATE(IN2);
			STDFB_TIMESTAMP(IN2);
		break;
		
		case 3:
			STDFB_DEMUX(3);
			STDFB_STATE(IN3);
			STDFB_TIMESTAMP(IN3);
		break;
		
		case 4:
			STDFB_DEMUX(4);
			STDFB_STATE(IN4);
			STDFB_TIMESTAMP(IN4);
		break;
		
		case 5:
			STDFB_DEMUX(5);
			STDFB_STATE(IN5);
			STDFB_TIMESTAMP(IN5);
		break;
		
		case 6:
			STDFB_DEMUX(6);
			STDFB_STATE(IN6);
			STDFB_TIMESTAMP(IN6);
		break;
		
		case 7:
			STDFB_DEMUX(7);
			STDFB_STATE(IN7);
			STDFB_TIMESTAMP(IN7);
		break;
		
		case 8:
			STDFB_DEMUX(8);
			STDFB_STATE(IN8);
			STDFB_TIMESTAMP(IN8);
		break;
		
		default:
			ov_logfile_error("%s: illegal input number, output reset", pinst->v_identifier);
			pinst->v_OUT.value.valueunion.val_bool = 0;
			pinst->v_OUT.value.vartype = OV_VT_BOOL;
		break;
	}
	
    return;
}
