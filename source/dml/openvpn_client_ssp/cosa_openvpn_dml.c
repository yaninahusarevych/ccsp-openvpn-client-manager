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

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/
#include "ansc_platform.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cosa_apis.h"
#include "ccsp_psm_helper.h"

extern ANSC_HANDLE bus_handle;
extern char g_Subsystem[32];

typedef struct {
    BOOL enable;
} OpenVPNCLientData_t;

typedef struct {
    BOOL enable;
    BOOL persist_tun;
    BOOL persist_key;
    BOOL tls_auth_enable;
    int remote_port;
    int remote_resolve_time;
    char device[256];
    char conn_type[256];
    char remote_addr_ipv4[256];
    char ca_path[256];
    char cert_path[256];
    char key_pub_path[256];
    char key_priv_path[256];
    char ta_path[256];
    int user;
    int group;
    char if_local_ep[256];
    char if_remote_ep[256];
} Tunnel_t;

OpenVPNCLientData_t client;

Tunnel_t tunnels[5];

ULONG
Tunnel_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    )
{
    return FALSE;
}

ANSC_HANDLE
Tunnel_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    return FALSE;
}

BOOL
OpenVPNClient_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
    if (AnscEqualString(ParamName, "OpenVPNClientEnabled", TRUE))
    {
        *pBool = client.enable;
        return TRUE;
    }

    return FALSE;
}

BOOL
OpenVPNClient_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
    if (AnscEqualString(ParamName, "OpenVPNClientEnabled", TRUE))
    {
        client.enable = bValue;

        return TRUE;
    }

    return FALSE;
}

BOOL
Tunnel_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
    PCOSA_CONTEXT_LINK_OBJECT pTunnel_ctx = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    int index = pTunnel_ctx->InstanceNumber;
    
    if (AnscEqualString(ParamName, "Enable", TRUE))
    {
        *pBool = tunnels[index].enable;
        return TRUE;
    }

    if (AnscEqualString(ParamName, "PersistTUN", TRUE))
    {
        *pBool = tunnels[index].persist_tun;
        return TRUE;
    }

    if (AnscEqualString(ParamName, "PersistKey", TRUE))
    {
        *pBool = tunnels[index].persist_key;
        return TRUE;
    }
 
    if (AnscEqualString(ParamName, "TLS-AuthEnabled", TRUE))
    {
        *pBool = tunnels[index].tls_auth_enable;
        return TRUE;
    }

    return FALSE;
}

BOOL
Tunnel_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    )
{
    PCOSA_CONTEXT_LINK_OBJECT pTunnel_ctx = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    int index = pTunnel_ctx->InstanceNumber;

    if (AnscEqualString(ParamName, "RemotePort", TRUE))
    {
        *pInt = tunnels[index].remote_port;
        return TRUE;
    }

    if (AnscEqualString(ParamName, "RemoteResolveTime", TRUE))
    {
        *pInt = tunnels[index].remote_resolve_time;
        return TRUE;
    }

    if (AnscEqualString(ParamName, "Group", TRUE))
    {
        *pInt = tunnels[index].group;
        return TRUE;
    }
    
    if (AnscEqualString(ParamName, "User", TRUE))
    {
        *pInt = tunnels[index].user;
        return TRUE;
    }
    
    return FALSE;
}

ULONG
Tunnel_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    )
{
    PCOSA_CONTEXT_LINK_OBJECT pTunnel_ctx = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    int index = pTunnel_ctx->InstanceNumber;
    
    if( AnscEqualString(ParamName, "Device", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].device);
        return 0;
    }

    if( AnscEqualString(ParamName, "ConnectionType", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].conn_type);
        return 0;
    }

    if( AnscEqualString(ParamName, "RemoteAddressIPv4", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].remote_addr_ipv4);
        return 0;
    }

    if( AnscEqualString(ParamName, "CertificateAuthority", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].ca_path);
        return 0;
    }

    if( AnscEqualString(ParamName, "PublicKey", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].cert_path);
        return 0;
    }

    if( AnscEqualString(ParamName, "PrivateKey", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].key_priv_path);
        return 0;
    }

    if( AnscEqualString(ParamName, "TAKey", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].ta_path);
        return 0;
    }
    
    if( AnscEqualString(ParamName, "IFConfigLocalEndpoint", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].if_local_ep);
        return 0;
    }

    if( AnscEqualString(ParamName, "IFConfigRemoteEndpoint", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels[index].if_remote_ep);
        return 0;
    }
    
    return 0;
}

BOOL
Tunnel_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        bValue
    )
{
    PCOSA_CONTEXT_LINK_OBJECT pTunnel_ctx = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    int index = pTunnel_ctx->InstanceNumber;
    
    char psmPath[512];
    char strValue[16];
    snprintf(psmPath, 512, "eRT.X_RDK_OpenVPNClient.Tunnel.%d.%s", index, ParamName);
    snprintf(strValue, 16, (bValue) ? "TRUE" : "FALSE");

	if( AnscEqualString(ParamName, "Enable", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;

        tunnels[index].enable = bValue;
		return FALSE;
	}
	
    if( AnscEqualString(ParamName, "PersistTUN", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;

        tunnels[index].persist_tun = bValue;
		return FALSE;
	}

	if( AnscEqualString(ParamName, "PersistKey", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;

        tunnels[index].persist_key = bValue;
		return FALSE;
	}

	if( AnscEqualString(ParamName, "TLS-AuthEnabled", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;

        tunnels[index].tls_auth_enable = bValue;
		return FALSE;
	}

    return FALSE;
}

BOOL
Tunnel_SetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       strValue
    )

{
    PCOSA_CONTEXT_LINK_OBJECT pTunnel_ctx = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    int index = pTunnel_ctx->InstanceNumber;
    
    char psmPath[512];
    snprintf(psmPath, 512, "eRT.X_RDK_OpenVPNClient.Tunnel.%d.%s", index, ParamName);

    if (!strcmp(strValue, "error"))
        return FALSE;

	if( AnscEqualString(ParamName, "Device", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].device, strValue))
			return TRUE;
		return FALSE;
	}

	if( AnscEqualString(ParamName, "ConnectionType", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].conn_type, strValue))
			return TRUE;
		return FALSE;
	}

	if( AnscEqualString(ParamName, "RemoteAddressIPv4", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].remote_addr_ipv4, strValue))
			return TRUE;
		return FALSE;
	}

	if( AnscEqualString(ParamName, "CertificateAuthority", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].ca_path, strValue))
			return TRUE;
		return FALSE;
	}
	
    if( AnscEqualString(ParamName, "PublicKey", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].key_pub_path, strValue))
			return TRUE;
		return FALSE;
	}

    if( AnscEqualString(ParamName, "PrivateKey", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].key_priv_path, strValue))
			return TRUE;
		return FALSE;
	}

    if( AnscEqualString(ParamName, "TAKey", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].ta_path, strValue))
			return TRUE;
		return FALSE;
	}
    
    if( AnscEqualString(ParamName, "IFConfigLocalEndpoint", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].if_local_ep, strValue))
			return TRUE;
		return FALSE;
	}

    if( AnscEqualString(ParamName, "IFConfigRemoteEndpoint", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		if (strcpy(tunnels[index].if_remote_ep, strValue))
			return TRUE;
		return FALSE;
	}
    
    return FALSE;
}

BOOL
Tunnel_SetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pIntValue
    )
{
    PCOSA_CONTEXT_LINK_OBJECT pTunnel_ctx = (PCOSA_CONTEXT_LINK_OBJECT)hInsContext;
    int index = pTunnel_ctx->InstanceNumber;
    
    char psmPath[512];
    char strValue[16];
    snprintf(psmPath, 512, "eRT.X_RDK_OpenVPNClient.Tunnel.%d.%s", index, ParamName);
    snprintf(strValue, 16, "%d", *pIntValue);

    if (!strcmp(strValue, "error"))
        return FALSE;

	if( AnscEqualString(ParamName, "RemotePort", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		tunnels[index].remote_port = *pIntValue;
		return FALSE;
	}

	if( AnscEqualString(ParamName, "RemoteResolveTime", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		tunnels[index].remote_resolve_time = *pIntValue;
		return FALSE;
	}
	
    if( AnscEqualString(ParamName, "User", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		tunnels[index].user= *pIntValue;
		return FALSE;
	}
    
    if( AnscEqualString(ParamName, "Group", TRUE))
	{
        if (PSM_Set_Record_Value2(bus_handle, g_Subsystem, psmPath, ccsp_string, strValue) != CSSP_SUCCESS) 
            return FALSE;
		tunnels[index].group= *pIntValue;
		return FALSE;
	}

    return FALSE;
}

