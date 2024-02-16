#ifndef _CLIENT_CONFIG_GENERATION_H
#define _CLIENT_CONFIG_GENERATION_H

/*
 * Function generates openvpn client configuration.
 * int index: index of a tunnel on path Device.X_RDK_OpenVPNClient.Tunnel.{i}.
 * Goal: Generate openvpn client configuration file
 * Returns 0 on success, -1 on failure
 */
int generate_client_configuration(int index);

#endif // !_CLIENT_CONFIG_GENERATION_H

