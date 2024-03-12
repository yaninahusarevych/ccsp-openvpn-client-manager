#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "process_handler.h"

#define OPENVPN_BIN_PATH "/usr/sbin/openvpn"
#define OPENVPN_CONFIG_PATH "/tmp/client.conf"

static pid_t child;

static void exit_cleanup(int ret, pid_t child)
{
    terminate_process(child);
    exit(ret);
}

static void signal_handler(int sig)
{
    exit_cleanup(0, child);
}

int main(void)
{
    signal(SIGINT, signal_handler);

    char *const args[] = { OPENVPN_BIN_PATH, "--config", OPENVPN_CONFIG_PATH, NULL };

    if (execute_process(OPENVPN_BIN_PATH, args, &child) != 0)
    {
        goto exit;
    }

    while (1) sleep(10);

exit:
    exit_cleanup(1, child);
}