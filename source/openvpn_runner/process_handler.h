#pragma once

#include <sys/types.h>

int execute_process(const char *path, char *const args[], pid_t *child);

int terminate_process(pid_t pid);
