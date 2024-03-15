/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**************************************************************************

    module: cosa_apis_pluginsampleobj.h

        For COSA Data Model Library Development

    -------------------------------------------------------------------

    description:

        This file defines the apis for objects to support Data Model Library.

    -------------------------------------------------------------------


    author:

        COSA XML TOOL CODE GENERATOR 1.0

    -------------------------------------------------------------------

    revision:

        12/02/2010    initial revision.

**************************************************************************/


#ifndef  _COSA_APIS_PLUGINSAMPLEOBJ_H
#define  _COSA_APIS_PLUGINSAMPLEOBJ_H

#include "slap_definitions.h"

/***********************************************************************

 APIs for Object:

    InternetGatewayDevice.X_CISCO_COM_COSADataModel.PluginSampleObj.

    *  PluginSampleObj_GetBulkParamValues
    *  PluginSampleObj_SetBulkParamValues
    *  PluginSampleObj_Validate
    *  PluginSampleObj_Commit
    *  PluginSampleObj_Rollback

***********************************************************************/
BOOL
X_RDK_OpenVPNClient_GetParamStringValue
	(
		ANSC_HANDLE 				hInsContext,
		char*						pParamName,
		char*						pValue,
		ULONG*						pUlSize
	);

BOOL
X_RDK_OpenVPNClient_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
X_RDK_OpenVPNClient_GetParamUlongValue
    (
 	ANSC_HANDLE                 	hInsContext,
        char*                       pParamName,
        ULONG*                      puLong
    );

BOOL
X_RDK_OpenVPNClient_GetParamIntValue
	(
		 ANSC_HANDLE				 hInsContext,
		char*						 pParamName,
		int*						 pInt
	);

BOOL
X_RDK_OpenVPNClient_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        char*                       pString
    );

BOOL
X_RDK_OpenVPNClient_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        BOOL                        bValue
    );

BOOL
X_RDK_OpenVPNClient_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
       ULONG                      	uValue
    );

BOOL
X_RDK_OpenVPNClient_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pParamName,
        int                      	iValue
    );

ULONG
X_RDK_OpenVPNClient_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
Tunnel_GetEntryCount
    (
        ANSC_HANDLE hInsContext
    );

ANSC_HANDLE
Tunnel_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

BOOL
Tunnel_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
Tunnel_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
Tunnel_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
Tunnel_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    );

BOOL
Tunnel_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
Tunnel_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    );

BOOL
Tunnel_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    );

BOOL
Tunnel_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pIntValue
    );
#endif
