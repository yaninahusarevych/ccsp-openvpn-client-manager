#include "client_config_generation.h"
#include <linux/limits.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static int config_append_if_config_endpoint(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValueLocalEndpoint = "";
        const char *defaultValueRemoteEndpoint = "";

        // get IFConfigLocalEndpoint
        // get IFConfigRemoteEndpoint

        fprintf(file, "ifconfig %s %s\n", defaultValueLocalEndpoint, 
                        defaultValueRemoteEndpoint);

        return 0;
}

static int config_append_group(FILE *file, int index)
{
        if (!file)
                return -1;

        const uint32_t defaultValueGroupID = getgid();

        // get Group
        
        fprintf(file, "group %d\n", defaultValueGroupID);
        
        return 0;
}

static int config_append_user(FILE *file, int index)
{
        if (!file)
                return -1;

        const uint32_t defaultValueUserID = getuid();

        // get User 
        
        fprintf(file, "user %d\n", defaultValueUserID);

        return 0;
}

static int config_append_TLS_auth(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValuePathToTAKey = "";
        const int defaultValueTLSAuthEnabled = 0;

        // get pathToTAKey 
        // get TLS-Auth-Enabled
        
        fprintf(file, "tls-auth %s %d\n", defaultValuePathToTAKey, defaultValueTLSAuthEnabled);
        
        return 0;
}

static int config_append_path_to_private_key(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValue = "";

        // get pathToPrivateKey
        
        fprintf(file, "key %s\n", defaultValue);
        
        return 0;
}

static int config_append_path_to_public_key(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValue = "";

        // get pathToPublicKey
        
        fprintf(file, "cert %s\n", defaultValue);
        
        return 0;
}

static int config_append_path_to_ca(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValue = "";

        // get pathToCA
        
        fprintf(file, "ca %s\n", defaultValue);
        
        return 0;
}

static int config_append_persist_key(FILE *file, int index)
{
        if (!file)
                return -1;

        const int defaultValue = 0;

        // get persistKey
        
        fprintf(file, "persist-key %d\n", defaultValue);
        
        return 0;
}

static int config_append_persist_TUN(FILE *file, int index)
{
        if (!file)
                return -1;

        const int defaultValue = 0;

        // get persistTUN
        
        fprintf(file, "persist-tun %d\n", defaultValue);
        
        return 0;
}

static int config_append_remote_resolve_time(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValue = "infinite";

        // get remoteResoveTime
        
        fprintf(file, "resolv-retry %s\n", defaultValue);
        
        return 0;
}

static int config_append_remote_connection(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValueAddress = "";
        const uint32_t defaultValuePort = 0;
        const char *defaultValueProto = "udp";

        // get connection type
        // get remote addressipv4
        // get remote port

        fprintf(file, "remote %s %d %s\n", defaultValueAddress,
                                                defaultValuePort,
                                                defaultValueProto);
        
        return 0;
}

static int config_append_device(FILE *file, int index)
{
        if (!file)
                return -1;

        const char *defaultValue = "tun";

        // get Device
        
        fprintf(file, "dev %s", defaultValue);

        return 0;
}

static int config_append_mandatory(FILE *file)
{
        if (!file)
                return -1;

        /* Specify we are a client */
        fprintf(file, "client\n");
        /* Set log file verbosity */
        fprintf(file, "verb 3\n");
        /* Select cryptographic cipher */
        fprintf(file, "cipher AES-256-GCM\n"
                        "auth SHA256\n"
                        "key-direction 1\n");

        return 0;
}

int generate_client_configuration(int index)
{
        if (index < 0)
                return -1;

        char filePath[PATH_MAX + 1];
        memset(filePath, 0, PATH_MAX + 1);
        sprintf(filePath, "/etc/openvpn/client%d.ovpn", index);

        FILE *file = fopen(filePath, "w");

        if (!file) 
        {
                return -1;
        }

        if (config_append_mandatory(file) < 0)
                return -1;
        if (config_append_device(file, index) < 0)
                return -1;
        if (config_append_remote_connection(file, index) < 0)
                return -1;
        if (config_append_remote_resolve_time(file, index) < 0)
                return -1;
        if (config_append_persist_TUN(file, index) < 0)
                return -1;
        if (config_append_persist_key(file, index) < 0)
                return -1;
        if (config_append_path_to_ca(file, index) < 0)
                return -1;
        if (config_append_path_to_public_key(file, index) < 0)
                return -1;
        if (config_append_path_to_private_key(file, index) < 0)
                return -1;
        if (config_append_TLS_auth(file, index) < 0)
                return -1;
        if (config_append_user(file, index) < 0)
                return -1;
        if (config_append_group(file, index) < 0)
                return -1;
        if (config_append_if_config_endpoint(file, index) < 0)
                return -1;

        return 0;
}

