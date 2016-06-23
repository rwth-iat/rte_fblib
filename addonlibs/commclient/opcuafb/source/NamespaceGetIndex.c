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

#ifndef OV_COMPILE_LIBRARY_opcuafb
#define OV_COMPILE_LIBRARY_opcuafb
#endif


#include "opcuafb.h"
#include "libov/ov_macros.h"
#include "fb_namedef.h"


//remove the function if the open62541 files are updated!


/**
 * Get the namespace-index of a namespace-URI
 *
 * @param client The UA_Client struct for this connection
 * @param namespaceUri The interested namespace URI
 * @param namespaceIndex The namespace index of the URI. The value is unchanged in case of an error
 * @return Indicates whether the operation succeeded or returns an error code
 */
UA_StatusCode UA_EXPORT UA_Client_NamespaceGetIndex(UA_Client *client, UA_String *namespaceUri, UA_UInt16 *namespaceIndex);

UA_StatusCode UA_Client_NamespaceGetIndex(UA_Client *client, UA_String *namespaceUri, UA_UInt16 *namespaceIndex){
	UA_ReadRequest ReadRequest;
	UA_ReadResponse ReadResponse;
	UA_StatusCode retval = UA_STATUSCODE_BADUNEXPECTEDERROR;

	UA_ReadRequest_init(&ReadRequest);
	ReadRequest.nodesToRead = UA_ReadValueId_new();
	ReadRequest.nodesToReadSize = 1;
	ReadRequest.nodesToRead[0].attributeId = UA_ATTRIBUTEID_VALUE;
	ReadRequest.nodesToRead[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_NAMESPACEARRAY);

	ReadResponse = UA_Client_Service_read(client, ReadRequest);
	UA_ReadRequest_deleteMembers(&ReadRequest);

	if(ReadResponse.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
		retval = ReadResponse.responseHeader.serviceResult;
		goto cleanup;
	}

	if(ReadResponse.resultsSize != 1 || !ReadResponse.results[0].hasValue){
		retval = UA_STATUSCODE_BADNODEATTRIBUTESINVALID;
		goto cleanup;
	}

	if(ReadResponse.results[0].value.type != &UA_TYPES[UA_TYPES_STRING]){
		retval = UA_STATUSCODE_BADTYPEMISMATCH;
		goto cleanup;
	}

	retval = UA_STATUSCODE_BADNOTFOUND;
	for(UA_UInt16 iterator = 0; iterator < ReadResponse.results[0].value.arrayLength; iterator++){
		if(UA_String_equal(namespaceUri, &((UA_String*)ReadResponse.results[0].value.data)[iterator] )){
			*namespaceIndex = iterator;
			retval = UA_STATUSCODE_GOOD;
			break;
		}
	}

	cleanup:
	UA_ReadResponse_deleteMembers(&ReadResponse);

	return retval;
}

OV_DLLFNCEXPORT OV_RESULT opcuafb_NamespaceGetIndex_Execute_set(
		OV_INSTPTR_opcuafb_NamespaceGetIndex          pinst,
		const OV_BOOL  value
) {
	OV_INSTPTR_opcuafb_Connect pConnect = NULL;
	UA_String namespaceUri;
	UA_UInt16 NamespaceIndex = 0;
	UA_StatusCode result = UA_STATUSCODE_GOOD;

	if(value == FALSE || pinst->v_Execute == TRUE){
		//only react on the rising edge
		pinst->v_Execute = value;
		return OV_ERR_OK;
	}

	pConnect = Ov_DynamicPtrCast(opcuafb_Connect, fb_connection_getFirstConnectedObject(Ov_PtrUpCast(fb_object, pinst), FALSE, TRUE, "ConnectionHdl"));
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

	//reuse memory for this temp string
	namespaceUri = UA_STRING(pinst->v_NamespaceUri);

	result = UA_Client_NamespaceGetIndex(pConnect->v_Client, &namespaceUri, &NamespaceIndex);
	if(result == UA_STATUSCODE_GOOD){
		pinst->v_Error = FALSE;
		pinst->v_ErrorID = 0;
		pinst->v_Done = TRUE;

		pinst->v_NamespaceIndex = (OV_UINT)NamespaceIndex;
	}else{
		pinst->v_Done = FALSE;
		pinst->v_Error = TRUE;
		pinst->v_ErrorID = 1; //todo
	}

	pinst->v_Execute = value;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT opcuafb_NamespaceGetIndex_ConnectionHdl_set(
		OV_INSTPTR_opcuafb_NamespaceGetIndex          pinst,
		const OV_UINT  value
) {
	if(value == 0){
		pinst->v_Done = TRUE;
	}else{
		if(pinst->v_ConnectionHdl == 0 && fb_connection_getFirstConnectedObject(Ov_PtrUpCast(fb_object, pinst), FALSE, TRUE, "Execute") == NULL){
			//we have a new connection and no connection on execute, so prepare for a new activation
			opcuafb_NamespaceGetIndex_Execute_set(pinst, FALSE);
		}
		pinst->v_Done = FALSE;
	}
	pinst->v_ConnectionHdl = value;
	pinst->v_Busy = FALSE;
	pinst->v_Error = FALSE;
	pinst->v_ErrorID = 0;
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT opcuafb_NamespaceGetIndex_NamespaceUri_set(
		OV_INSTPTR_opcuafb_NamespaceGetIndex          pinst,
		const OV_STRING  value
) {
	pinst->v_Done = FALSE;
	return ov_string_setvalue(&pinst->v_NamespaceUri,value);
}

OV_DLLFNCEXPORT OV_RESULT opcuafb_NamespaceGetIndex_constructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_opcuafb_NamespaceGetIndex pinst = Ov_StaticPtrCast(opcuafb_NamespaceGetIndex, pobj);
	OV_RESULT    result;

	/* do what the base class does first */
	result = fb_functionblock_constructor(pobj);
	if(Ov_Fail(result))
		return result;

	pinst->v_Done = FALSE;
	return ov_string_setvalue(&pinst->v_NamespaceUri, OV_UA_NAMESPACEURI);
}

