/*
*   Copyright (C) 1998
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
/****************************************************************************
*									    *
*    functionblock                      				    *
*                                                          		    *
*    greater comparison (VDI/VDE 3696)                                      *
*                                                                           *
****************************************************************************/
/*
*   type: gt
*   ========
*/
/*
*   history
*   -------
*   created : 4.5.1999
*   author  : Michael Klamann, Chair of Process Control Engineering, RWTH Aachen
*/
/*
*   description
*   -----------
*   Similar to standardfunction  GT in IEC 1131-3.
*   Limited to two input values but extended by a tolerance input. 
*
*   U1 has to be at least larger than U2 + TOL to be regarded as greater.
*/
/*
*   C-Includes
*   ----------
*   none
*/
/*  
*   defines
*   -------
*   none
*/
/*
*   modul-declaration
*   -----------------
*/
#include "vdivde3696.h"
#include "libov/ov_macros.h"

OV_RESULT OV_DLLFNCEXPORT vdivde3696_gt_constructor(
	OV_INSTPTR_ov_object	pobj
) {
	OV_RESULT res;
	OV_INSTPTR_vdivde3696_gt pgt;

	res = fb_functionblock_constructor(pobj);
	if (Ov_Fail(res)) return res;
	pgt = Ov_StaticPtrCast(vdivde3696_gt, pobj);
	pgt->v_en = TRUE;
	return OV_ERR_OK;
}

void OV_DLLFNCEXPORT vdivde3696_gt_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
	OV_INSTPTR_vdivde3696_gt port = Ov_StaticPtrCast(vdivde3696_gt, pfb);

	/*
	*   local variables
	*   ---------------
	*   none
	*/
	/*
	*   instructions
	*   ------------
	*/

        if (port->v_en) /* functionblock enable */
        {
	  /* set enable output to true */
	  port->v_eno = TRUE;

	  /* greater comparison */
	  if (port->v_u1 > (port->v_u2 + port->v_tol))
	  {
	    /* greater */
	    port->v_q = TRUE;
	  }
	  else /* NOT greater */
	  {
	    port->v_q = FALSE;
	  }
	}
        else /* functionblock NOT enable */
        {
	  port->v_eno = FALSE;
	}

       /* add 1 to counter */
	port->v_counter = (port->v_counter+1)%10000;

/*******  end  *******/
	return;
	}







