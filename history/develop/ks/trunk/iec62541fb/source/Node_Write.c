/*
*	Copyright (C) 2015
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
***********************************************************************/

#ifndef OV_COMPILE_LIBRARY_iec62541fb
#define OV_COMPILE_LIBRARY_iec62541fb
#endif


#include "iec62541fb.h"
#include "libov/ov_macros.h"
#include "fb_namedef.h"

OV_DLLFNCEXPORT OV_RESULT iec62541fb_Write_Execute_set(
		OV_INSTPTR_iec62541fb_Write          pinst,
		const OV_BOOL  value
) {
	OV_INSTPTR_iec62541fb_Connect pConnect = NULL;
	OV_INSTPTR_iec62541fb_NodeGetHandle pNodeGetHandle = NULL;
	UA_WriteResponse WriteResponse;
	UA_String tempString;

	if(value == FALSE || pinst->v_Execute == TRUE){
		//only react on the rising edge
		pinst->v_Execute = value;
		return OV_ERR_OK;
	}

	pConnect = Ov_DynamicPtrCast(iec62541fb_Connect, fb_connection_getFirstConnectedObject(Ov_PtrUpCast(fb_object, pinst), FALSE, TRUE, "ConnectionHdl"));
	if(pConnect == NULL){
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; //todo
		return OV_ERR_BADVALUE;
	}
	if(pConnect->v_ConnectionHdl == 0){
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; //todo
		return OV_ERR_BADVALUE;
	}
	if(pConnect->v_Client == NULL){
		//internal error
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; //todo
		return OV_ERR_BADVALUE;
	}

	pNodeGetHandle = Ov_DynamicPtrCast(iec62541fb_NodeGetHandle, fb_connection_getFirstConnectedObject(Ov_PtrUpCast(fb_object, pinst), FALSE, TRUE, "NodeHdl"));
	if(pNodeGetHandle == NULL){
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; //todo
		return OV_ERR_BADVALUE;
	}
	if(pNodeGetHandle->v_NodeHdl == 0){
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; //todo
		return OV_ERR_BADVALUE;
	}

	UA_WriteRequest_init(&pNodeGetHandle->v_WriteRequest);
	pNodeGetHandle->v_WriteRequest.nodesToWrite = UA_WriteValue_new();
	pNodeGetHandle->v_WriteRequest.nodesToWriteSize = 1;
	pNodeGetHandle->v_WriteRequest.nodesToWrite[0].nodeId = UA_NODEID_STRING_ALLOC(1, pNodeGetHandle->v_NodeID.Identifier); /* assume this node exists */
	pNodeGetHandle->v_WriteRequest.nodesToWrite[0].attributeId = UA_ATTRIBUTEID_VALUE;
	pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.hasValue = UA_TRUE;
	switch (pinst->v_Variable.value.vartype & OV_VT_KSMASK){
	case OV_VT_INT:
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.type = &UA_TYPES[UA_TYPES_INT32];
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.data = &pinst->v_Variable.value.valueunion.val_int;
		break;
	case OV_VT_UINT:
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.type = &UA_TYPES[UA_TYPES_UINT32];
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.data = &pinst->v_Variable.value.valueunion.val_uint;
		break;
	case OV_VT_SINGLE:
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.type = &UA_TYPES[UA_TYPES_FLOAT];
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.data = &pinst->v_Variable.value.valueunion.val_single;
		break;
	case OV_VT_DOUBLE:
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.type = &UA_TYPES[UA_TYPES_DOUBLE];
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA_NODELETE; //do not free the integer on deletion
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.data = &pinst->v_Variable.value.valueunion.val_double;
		break;
	case OV_VT_STRING:
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.type = &UA_TYPES[UA_TYPES_STRING];
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.storageType = UA_VARIANT_DATA; //do not free the integer on deletion
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.data = UA_String_new();
		tempString = UA_String_fromChars(pinst->v_Variable.value.valueunion.val_string);
		pNodeGetHandle->v_WriteRequest.nodesToWrite[0].value.value.data = &tempString;
		break;
	default:
		break;
	}

	WriteResponse = UA_Client_write(pConnect->v_Client, &pNodeGetHandle->v_WriteRequest);
	if(WriteResponse.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
		pinst->v_Error = FALSE;
		pinst->v_ErrorID = 0;
	}else{
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; // todo
	}
	UA_WriteResponse_deleteMembers(&WriteResponse);

	pinst->v_Execute = value;
	return OV_ERR_OK;
}


OV_DLLFNCEXPORT OV_RESULT iec62541fb_Write_ConnectionHdl_set(
		OV_INSTPTR_iec62541fb_Write          pinst,
		const OV_UINT  value
) {
	if(value == 0){
		pinst->v_Done = TRUE;
	}else{
		pinst->v_Done = FALSE;
	}
	pinst->v_ConnectionHdl = value;
	pinst->v_Busy = FALSE;
	pinst->v_Error = FALSE;
	pinst->v_ErrorID = 0;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT iec62541fb_Write_NodeHdl_set(
		OV_INSTPTR_iec62541fb_Write          pinst,
		const OV_UINT  value
) {
	if(value == 0){
		pinst->v_Done = TRUE;
	}else{
		pinst->v_Done = FALSE;
	}
	pinst->v_Busy = FALSE;
	pinst->v_Error = FALSE;
	pinst->v_ErrorID = 0;
	pinst->v_NodeHdl = value;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT void iec62541fb_Write_startup(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	//OV_INSTPTR_iec62541fb_Write pinst = Ov_StaticPtrCast(iec62541fb_Write, pobj);

	/* do what the base class does first */
	fb_functionblock_startup(pobj);

	/*
	pinst->v_NodeAddInfo.IndexRangeCount = 0;
	pinst->v_NodeAddInfo.AttributeId = 0;
	*/

	return;
}