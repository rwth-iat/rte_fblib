/*
 * utilities.c
 *
 *  Created on: Aug 30, 2017
 *      Author: julian
 */
#include "SSChelper.h"
#include "ov_macros.h"

#include "ov_path.h"
#include "ov_memstack.h"
#include "ov_result.h"
#include "ov_logfile.h"

#include "fb_namedef.h"

#include "ov_call_macros_10.h"


static void extractBehindSeperator(const OV_STRING inputstring, OV_STRING *pathname, OV_STRING *varname, char seperator){
	OV_UINT len = 0;
	OV_UINT i = 0;

	if(!inputstring){
		return;
	}
	ov_string_setvalue(pathname, inputstring);
	len = ov_string_getlength(inputstring);	//iterate backwards, for speed :-)
	for(i = len-1 ; i > 1; i--){
		if(inputstring[i] == seperator){
			ov_string_setvalue(varname, &inputstring[i+1]);
			(*pathname)[i] = '\0';
			ov_string_setvalue(pathname,*pathname);
			break;
		}
	}
	return;
}

OV_RESULT SSChelper_getObjectAndVarnameFromSetVariable(
		const OV_INSTPTR_ov_object pinst,
		const OV_STRING nameToCheck,
		OV_INSTPTR_ov_object *pTargetObj,
		OV_STRING *ptargetVarname
) {
	OV_STRING targetPathname = NULL;
	OV_STRING pathRelativeobject = NULL;
	OV_INSTPTR_ov_domain containerDomain = NULL;

	*pTargetObj = NULL;
	//split the input at dot
	extractBehindSeperator(nameToCheck, &targetPathname, ptargetVarname, '.');

	if(targetPathname == NULL){
		return OV_ERR_BADPARAM;
	}else if(targetPathname[0] == '/'){
		//we have a full path
		*pTargetObj = ov_path_getobjectpointer(targetPathname, 2);
	}else{
		//we have a relative path
		ov_memstack_lock();
		//all path are relative to the activeHeader
		containerDomain =Ov_GetParent(ov_containment, pinst);
		ov_string_setvalue(&pathRelativeobject, ov_path_getcanonicalpath(Ov_PtrUpCast(ov_object, containerDomain), 2));
		*pTargetObj = getrelativeobjectpointer(pathRelativeobject, targetPathname);
		ov_memstack_unlock();
	}
	if(Ov_CanCastTo(fb_port, *pTargetObj)){
		//we have a fc port, so adjust everything
		ov_string_setvalue(ptargetVarname, nameToCheck);
		*pTargetObj = Ov_PtrUpCast(ov_object, Ov_GetParent(ov_containment, *pTargetObj));
	}
	ov_string_setvalue(&targetPathname, NULL);
	ov_string_setvalue(&pathRelativeobject,NULL);

	return OV_ERR_OK;
}

OV_RESULT SSChelper_setNamedVariable(const OV_INSTPTR_ov_object pTargetObj, const OV_STRING targetVarname, OV_ANY *value){
	OV_RESULT result = OV_ERR_OK;
	OV_ELEMENT element;
	OV_ELEMENT varElement;
	OV_VTBLPTR_ov_object pVtblObj = NULL;

	if(pTargetObj == NULL){
			return OV_ERR_BADPARAM;
	}else if (Ov_CanCastTo(fb_functionchart, pTargetObj)){
		//set variable in a functionchart
		result = fb_functionchart_setport(Ov_StaticPtrCast(fb_functionchart, pTargetObj), targetVarname, value);
	}else{
		//set variable in a object
		varElement.elemtype = OV_ET_NONE;
		element.elemtype = OV_ET_OBJECT;
		element.pobj = pTargetObj;

		//search the variable for the set operation
		ov_element_searchpart(&element, &varElement, OV_ET_VARIABLE, targetVarname);
		if(varElement.elemtype == OV_ET_VARIABLE) {
			//port found, use the setter to write the value
			Ov_GetVTablePtr(ov_object, pVtblObj, pTargetObj);
			result = pVtblObj->m_setvar(varElement.pobj, &varElement, value);
		}
	}

	return result;
}

OV_RESULT SSChelper_getNamedVariable(const OV_INSTPTR_ov_object pTargetObj, const OV_STRING targetVarname, OV_ANY *value){
	OV_RESULT result = OV_ERR_OK;
	OV_ELEMENT element;
	OV_ELEMENT varElement;
	OV_VTBLPTR_ov_object pVtblObj = NULL;
	OV_ANY tmpAny = {.value.vartype=OV_VT_VOID};

	if(pTargetObj == NULL){

		result = OV_ERR_BADPARAM;
	}else if (Ov_CanCastTo(fb_functionchart, pTargetObj)){
		//get variable in a functionchart
		ov_memstack_lock();
		result = fb_functionchart_getport(Ov_StaticPtrCast(fb_functionchart, pTargetObj), targetVarname, &tmpAny);
		result |= Ov_SetAnyValue(value, &tmpAny);
		ov_memstack_unlock();
	}else{
		//get variable in a object
		varElement.elemtype = OV_ET_NONE;
		element.elemtype = OV_ET_OBJECT;
		element.pobj = pTargetObj;

		//search the variable for the get operation
		ov_element_searchpart(&element, &varElement, OV_ET_VARIABLE, targetVarname);
		if(varElement.elemtype == OV_ET_VARIABLE) {
			//port found, use the getter to read the value
			Ov_GetVTablePtr(ov_object, pVtblObj, pTargetObj);
			ov_memstack_lock();
			result = pVtblObj->m_getvar(varElement.pobj, &varElement, &tmpAny);
			result |= Ov_SetAnyValue(value, &tmpAny);
			ov_memstack_unlock();
		}else{
			result = OV_ERR_BADPARAM;
		}
	}
	if(result != OV_ERR_OK){
		Ov_SetAnyValue(value,NULL);
	}
	return result;
}
