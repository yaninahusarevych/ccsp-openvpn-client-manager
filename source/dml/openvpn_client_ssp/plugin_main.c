/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
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
/*********************************************************************** 
  
    module: plugin_main.c

        Implement COSA Data Model Library Init and Unload apis.
 
    ---------------------------------------------------------------

    author:

        COSA XML TOOL CODE GENERATOR 1.0

    ---------------------------------------------------------------

    revision:

        09/28/2011    initial revision.

**********************************************************************/

#include "ansc_platform.h"
#include "ansc_load_library.h"
#include "cosa_plugin_api.h"
#include "plugin_main.h"
#include "cosa_apis_testcomponentplugin.h"

#define THIS_PLUGIN_VERSION                         1

int ANSC_EXPORT_API
COSA_Init
    (
        ULONG                       uMaxVersionSupported, 
        void*                       hCosaPlugInfo         /* PCOSA_PLUGIN_INFO passed in by the caller */
    )
{
    PCOSA_PLUGIN_INFO               pPlugInfo  = (PCOSA_PLUGIN_INFO)hCosaPlugInfo;

    if ( uMaxVersionSupported < THIS_PLUGIN_VERSION )
    {
      /* this version is not supported */
        return -1;
    }   
    
    pPlugInfo->uPluginVersion       = THIS_PLUGIN_VERSION;
    /* register the back-end apis for the data model */
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_GetParamUlongValue",  X_RDK_OpenVPNClient_GetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_SetParamUlongValue",  X_RDK_OpenVPNClient_SetParamUlongValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_GetParamStringValue",  X_RDK_OpenVPNClient_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_SetParamStringValue",  X_RDK_OpenVPNClient_SetParamStringValue);
	pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_GetParamBoolValue",  X_RDK_OpenVPNClient_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_SetParamBoolValue",  X_RDK_OpenVPNClient_SetParamBoolValue);
	pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_GetParamIntValue",  X_RDK_OpenVPNClient_GetParamIntValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_SetParamIntValue",  X_RDK_OpenVPNClient_SetParamIntValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "X_RDK_OpenVPNClient_Commit",  X_RDK_OpenVPNClient_Commit);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetEntryCount",  Tunnel_GetEntryCount);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetEntry",  Tunnel_GetEntry);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_IsUpdated",  Tunnel_IsUpdated);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_Synchronize",  Tunnel_Synchronize);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetParamStringValue",  Tunnel_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_SetParamStringValue",  Tunnel_SetParamStringValue);
    return  0;
}

BOOL ANSC_EXPORT_API
COSA_IsObjectSupported
    (
        char*                        pObjName
    )
{
    
    return TRUE;
}

void ANSC_EXPORT_API
COSA_Unload
    (
        void
    )
{
    /* unload the memory here */
}
