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
#include "cosa_apis_openvpn.h"
#include "utils.h"

#define THIS_PLUGIN_VERSION                         1

COSAGetParamValueByPathNameProc    g_GetParamValueByPathNameProc;
COSASetParamValueByPathNameProc    g_SetParamValueByPathNameProc;
COSAGetParamValueStringProc        g_GetParamValueString;
COSAGetParamValueUlongProc         g_GetParamValueUlong;
COSAGetParamValueIntProc           g_GetParamValueInt;
COSAGetParamValueBoolProc          g_GetParamValueBool;
COSASetParamValueStringProc        g_SetParamValueString;
COSASetParamValueUlongProc         g_SetParamValueUlong;
COSASetParamValueIntProc           g_SetParamValueInt;
COSASetParamValueBoolProc          g_SetParamValueBool;
COSAGetInstanceNumbersProc         g_GetInstanceNumbers;
COSAValidateHierarchyInterfaceProc g_ValidateInterface;           // TODO: Check if these needed
COSAGetHandleProc                  g_GetRegistryRootFolder;       // TODO: Check if these needed
COSAGetInstanceNumberByIndexProc   g_GetInstanceNumberByIndex;    // TODO: Check if these needed
COSAGetInterfaceByNameProc         g_GetInterfaceByName;          // TODO: Check if these needed
COSAGetHandleProc                  g_GetMessageBusHandle;         // TODO: Check if these needed
COSAGetSubsystemPrefixProc         g_GetSubsystemPrefix;          // TODO: Check if these needed
char*                              g_SubsystemPrefix;
COSARegisterCallBackAfterInitDmlProc  g_RegisterCallBackAfterInitDml;
COSARepopulateTableProc            g_COSARepopulateTable;

//void *                       g_pDslhDmlAgent;
extern ANSC_HANDLE     g_MessageBusHandle_Irep;
extern char            g_SubSysPrefix_Irep[32];

int ANSC_EXPORT_API
COSA_Init
    (
        ULONG                       uMaxVersionSupported, 
        void*                       hCosaPlugInfo         /* PCOSA_PLUGIN_INFO passed in by the caller */
    )
{
    PCOSA_PLUGIN_INFO               pPlugInfo  = (PCOSA_PLUGIN_INFO)hCosaPlugInfo;
    openvpnmgr_log("COSA_Init --> Entry\n");

    COSAGetParamValueByPathNameProc pGetParamValueByPathNameProc = (COSAGetParamValueByPathNameProc)NULL;
    COSASetParamValueByPathNameProc pSetParamValueByPathNameProc = (COSASetParamValueByPathNameProc)NULL;
    COSAGetParamValueStringProc     pGetStringProc              = (COSAGetParamValueStringProc       )NULL;
    COSAGetParamValueUlongProc      pGetParamValueUlongProc     = (COSAGetParamValueUlongProc        )NULL;
    COSAGetParamValueIntProc        pGetParamValueIntProc       = (COSAGetParamValueIntProc          )NULL;
    COSAGetParamValueBoolProc       pGetParamValueBoolProc      = (COSAGetParamValueBoolProc         )NULL;
    COSASetParamValueStringProc     pSetStringProc              = (COSASetParamValueStringProc       )NULL;
    COSASetParamValueUlongProc      pSetParamValueUlongProc     = (COSASetParamValueUlongProc        )NULL;
    COSASetParamValueIntProc        pSetParamValueIntProc       = (COSASetParamValueIntProc          )NULL;
    COSASetParamValueBoolProc       pSetParamValueBoolProc      = (COSASetParamValueBoolProc         )NULL;
    COSAGetInstanceNumbersProc      pGetInstanceNumbersProc     = (COSAGetInstanceNumbersProc        )NULL;
    COSARegisterCallBackAfterInitDmlProc pRegisterCallBackAfterInitDmlProc = (COSARegisterCallBackAfterInitDmlProc)NULL;
    COSARepopulateTableProc        pCOSARepopulateTable        = (COSARepopulateTableProc           )NULL;

    COSAValidateHierarchyInterfaceProc
        pValInterfaceProc           = (COSAValidateHierarchyInterfaceProc)NULL;
    COSAGetHandleProc               pGetRegistryRootFolder      = (COSAGetHandleProc                 )NULL;
    COSAGetInstanceNumberByIndexProc
        pGetInsNumberByIndexProc    = (COSAGetInstanceNumberByIndexProc  )NULL;
    COSAGetInterfaceByNameProc      pGetInterfaceByNameProc     = (COSAGetInterfaceByNameProc        )NULL;

    if ( uMaxVersionSupported < THIS_PLUGIN_VERSION )
    {
        openvpnmgr_log("cosa_init: version is not supported");
      /* this version is not supported */
        return -1;
    }   
    
    openvpnmgr_log("cosa_init: version is supported"); 
    pPlugInfo->uPluginVersion       = THIS_PLUGIN_VERSION;
    /* register the back-end apis for the data model */
	pPlugInfo->RegisterFunction(pPlugInfo->hContext, "OpenVPNClient_GetParamBoolValue",  OpenVPNClient_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "OpenVPNClient_SetParamBoolValue",  OpenVPNClient_SetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetEntryCount",  Tunnel_GetEntryCount);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetEntry",  Tunnel_GetEntry);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetParamBoolValue",  Tunnel_GetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetParamStringValue",  Tunnel_GetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_SetParamStringValue",  Tunnel_SetParamStringValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_GetParamIntValue",  Tunnel_GetParamIntValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_SetParamBoolValue",  Tunnel_SetParamBoolValue);
    pPlugInfo->RegisterFunction(pPlugInfo->hContext, "Tunnel_SetParamIntValue",  Tunnel_SetParamIntValue);



    pGetParamValueByPathNameProc = (COSAGetParamValueByPathNameProc)pPlugInfo->AcquireFunction("COSAGetParamValueByPathName");
    if( pGetParamValueByPathNameProc != NULL)
    {
        openvpnmgr_log("cosa_init: pGetParamValueByPathNameProc is not NULL");
        g_GetParamValueByPathNameProc = pGetParamValueByPathNameProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetParamValueByPathNameProc is NULL");
        goto EXIT;
    }
    pSetParamValueByPathNameProc = (COSASetParamValueByPathNameProc)pPlugInfo->AcquireFunction("COSASetParamValueByPathName");

    if( pSetParamValueByPathNameProc != NULL)
    {
        openvpnmgr_log("cosa_init: pSetParamValueByPathNameProc is not NULL");
        g_SetParamValueByPathNameProc = pSetParamValueByPathNameProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pSetParamValueByPathNameProc is NULL");
        goto EXIT;
    }
    pGetStringProc = (COSAGetParamValueStringProc)pPlugInfo->AcquireFunction("COSAGetParamValueString");

    if( pGetStringProc != NULL)
    {
        openvpnmgr_log("cosa_init: pGetStringProc is not NULL");
        g_GetParamValueString = pGetStringProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetStringProc is NULL");
        goto EXIT;
    }
    pGetParamValueUlongProc = (COSAGetParamValueUlongProc)pPlugInfo->AcquireFunction("COSAGetParamValueUlong");

    if( pGetParamValueUlongProc != NULL)
    {
        openvpnmgr_log("cosa_init: pGetParamValueUlongProc is not NULL");
        g_GetParamValueUlong = pGetParamValueUlongProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetParamValueUlongProc is NULL");
        goto EXIT;
    }

    pGetParamValueIntProc = (COSAGetParamValueIntProc)pPlugInfo->AcquireFunction("COSAGetParamValueInt");

    if( pGetParamValueIntProc != NULL)
    {
        openvpnmgr_log("cosa_init: pGetParamValueIntProc is not NULL");
        g_GetParamValueInt = pGetParamValueIntProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetParamValueIntProc is NULL");
        goto EXIT;
    }
    pGetParamValueBoolProc = (COSAGetParamValueBoolProc)pPlugInfo->AcquireFunction("COSAGetParamValueBool");

    if( pGetParamValueBoolProc != NULL)
    {
        openvpnmgr_log("cosa_init: pGetParamValueBoolProc is not NULL");
        g_GetParamValueBool = pGetParamValueBoolProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetParamValueBoolProc is NULL");
        goto EXIT;
    }
    pSetStringProc = (COSASetParamValueStringProc)pPlugInfo->AcquireFunction("COSASetParamValueString");

    if( pSetStringProc != NULL)
    {
        openvpnmgr_log("cosa_init: pSetStringProc is not NULL");
        g_SetParamValueString = pSetStringProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pSetStringProc is NULL");
        goto EXIT;
    }
    pSetParamValueUlongProc = (COSASetParamValueUlongProc)pPlugInfo->AcquireFunction("COSASetParamValueUlong");

    if( pSetParamValueUlongProc != NULL)
    {
        openvpnmgr_log("cosa_init: pSetParamValueUlongProc is not NULL");
        g_SetParamValueUlong = pSetParamValueUlongProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pSetParamValueUlongProc is NULL");
        goto EXIT;
    }

    pSetParamValueIntProc = (COSASetParamValueIntProc)pPlugInfo->AcquireFunction("COSASetParamValueInt");

    if( pSetParamValueIntProc != NULL)
    {
        openvpnmgr_log("cosa_init: pSetParamValueIntProc is not NULL");
        g_SetParamValueInt = pSetParamValueIntProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pSetParamValueIntProc is NULL");
        goto EXIT;
    }
    pSetParamValueBoolProc = (COSASetParamValueBoolProc)pPlugInfo->AcquireFunction("COSASetParamValueBool");

    if( pSetParamValueBoolProc != NULL)
    {
        openvpnmgr_log("cosa_init: pSetParamValueBoolProc is not NULL");
        g_SetParamValueBool = pSetParamValueBoolProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pSetParamValueBoolProc is NULL");
        goto EXIT;
    }
    pGetInstanceNumbersProc = (COSAGetInstanceNumbersProc)pPlugInfo->AcquireFunction("COSAGetInstanceNumbers");

    if( pGetInstanceNumbersProc != NULL)
    {
        openvpnmgr_log("cosa_init: pGetInstanceNumbersProc is not NULL");
        g_GetInstanceNumbers = pGetInstanceNumbersProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetInstanceNumbersProc is NULL");
        goto EXIT;
    }
    pValInterfaceProc = (COSAValidateHierarchyInterfaceProc)pPlugInfo->AcquireFunction("COSAValidateHierarchyInterface");

    if ( pValInterfaceProc )
    {
        openvpnmgr_log("cosa_init: pValInterfaceProc is not NULL");
        g_ValidateInterface = pValInterfaceProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pValInterfaceProc is NULL");
        goto EXIT;
    }
    pGetRegistryRootFolder = (COSAGetHandleProc)pPlugInfo->AcquireFunction("COSAGetRegistryRootFolder");

    if ( pGetRegistryRootFolder != NULL )
    {
        openvpnmgr_log("cosa_init: pGetRegistryRootFolder is not NULL");
        g_GetRegistryRootFolder = pGetRegistryRootFolder;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetRegistryRootFolder is NULL");
        goto EXIT;
    }
    pGetInsNumberByIndexProc = (COSAGetInstanceNumberByIndexProc)pPlugInfo->AcquireFunction("COSAGetInstanceNumberByIndex");

    if ( pGetInsNumberByIndexProc != NULL )
    {
        openvpnmgr_log("cosa_init: pGetInsNumberByIndexProc is not NULL");
        g_GetInstanceNumberByIndex = pGetInsNumberByIndexProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetInsNumberByIndexProc is NULL");
        goto EXIT;
    }
    pGetInterfaceByNameProc = (COSAGetInterfaceByNameProc)pPlugInfo->AcquireFunction("COSAGetInterfaceByName");

    if ( pGetInterfaceByNameProc != NULL )
    {
        openvpnmgr_log("cosa_init: pGetInterfaceByNameProc is not NULL");
        g_GetInterfaceByName = pGetInterfaceByNameProc;
    }
    else
    {
        openvpnmgr_log("cosa_init: pGetInterfaceByNameProc is NULL");
        goto EXIT;
    }

    pRegisterCallBackAfterInitDmlProc = (COSARegisterCallBackAfterInitDmlProc)pPlugInfo->AcquireFunction("COSARegisterCallBackAfterInitDml");

    if ( !g_RegisterCallBackAfterInitDml )
    {
        openvpnmgr_log("cosa_init: g_RegisterCallBackAfterInitDml is NULL");
        goto EXIT;
    }
    pCOSARepopulateTable = (COSARepopulateTableProc)pPlugInfo->AcquireFunction("COSARepopulateTable");

    if ( !g_COSARepopulateTable )
    {
        openvpnmgr_log("cosa_init: g_COSARepopulateTable is NULL");
        goto EXIT;
    }

EXIT:
    return  0;
}

BOOL ANSC_EXPORT_API
COSA_IsObjectSupported
    (
        char*                        pObjName
    )
{
    openvpnmgr_log("COSA_IsObjectSupported --> Entry\n");
    return TRUE;
}

void ANSC_EXPORT_API
COSA_Unload
    (
        void
    )
{
    openvpnmgr_log("COSA_Unload --> Entry\n");
    /* unload the memory here */
}
