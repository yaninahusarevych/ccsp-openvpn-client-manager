#ifndef __COMMON_H__
#define __COMMON_H__
#endif // !__COMMON_H__

#include "slap_definitions.h"

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

    int process_pid;
} Tunnel_t;

Tunnel_t *tunnels_get_tunnel(int index);

#endif

