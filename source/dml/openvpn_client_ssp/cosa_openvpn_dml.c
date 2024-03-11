#include "ansc_platform.h"
//#include "cosa_apis_testcomponentplugin.h"
#include "ccsp_trace.h"
#include "ccsp_syslog.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

struct OpenVPNCLientData_t {
    BOOL enable;
};

struct Tunnel_t {
    BOOL persist_tun;
    BOOL persist_key;
    BOOL tls_auth_enable;
    int remote_port;
    int remote_resolve_time;
    char *device;
    char *conn_type;
    char *remote_addr_ipv4;
    char *ca_path;
    char *cert_path;
    char *key_path;
    char *ta_path;
};

OpenVPNCLientData_t client;

// Must be a dynamic array
Tunnel_t tunnels;


//Tunnel_t *clients;
//int count = 0;

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
        *pBool = client->enable;
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
        if(client->enable == bValue)
        {
            return TRUE;
        }

        client->enable = bValue;

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
    if (AnscEqualString(ParamName, "PersistTUN", TRUE))
    {
        *pBool = tunnels->persist_tun;
        return TRUE;
    }

    if (AnscEqualString(ParamName, "PersistKey", TRUE))
    {
        *pBool = tunnels->persist_key;
        return TRUE;
    }
 
    if (AnscEqualString(ParamName, "TLS-AuthEnabled", TRUE))
    {
        *pBool = tunnels->tls_auth_enable;
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
    if (AnscEqualString(ParamName, "RemotePort", TRUE))
    {
        *pInt = tunnels->remote_port;
        return TRUE;
    }

    if (AnscEqualString(ParamName, "RemoteResolveTime", TRUE))
    {
        *pInt = tunnels->remote_resolve_time;
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
    if( AnscEqualString(ParamName, "Device", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->device);
        return 0;
    }

    if( AnscEqualString(ParamName, "ConnectionType", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->conn_type);
        return 0;
    }

    if( AnscEqualString(ParamName, "RemoteAddressIPv4", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->remote_addr_ipv4);
        return 0;
    }

    if( AnscEqualString(ParamName, "CertificateAuthority", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->ca_path);
        return 0;
    }

    if( AnscEqualString(ParamName, "PublicKey", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->cert_path);
        return 0;
    }

    if( AnscEqualString(ParamName, "PrivateKey", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->key_path);
        return 0;
    }

    if( AnscEqualString(ParamName, "TAKey", TRUE))
    {
        snprintf(pValue,*pUlSize,"%s",tunnels->ta_path);
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
    if (AnscEqualString(ParamName, "PersistTUN", TRUE))
    {
        if(tunnels.persist_tun == bValue)
        {
            return TRUE;
        }

        tunnels.persist_tun = bValue;

        return TRUE;
    }

    if (AnscEqualString(ParamName, "PersistKey", TRUE))
    {
        if(global_wifi_config->global_parameters.persist_key == bValue)
        {
            return TRUE;
        }

        tunnels.persist_key = bValue;

        return TRUE;
    }

    if (AnscEqualString(ParamName, "TLS-AuthEnabled", TRUE))
    {
        if(global_wifi_config->global_parameters.tls_auth_enable == bValue)
        {
            return TRUE;
        }

        tunnels.tls_auth_enable = bValue;

        return TRUE;
    }

    return FALSE;
}
