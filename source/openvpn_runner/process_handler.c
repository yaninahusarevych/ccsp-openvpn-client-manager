#include <fcntl.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sysexits.h>
#include "process_handler.h"

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

static int wait_for_process(pid_t pid, int *wstatus)
{

    if (waitpid(pid, wstatus, 0) == -1)
    {
        perror("waitpid()");
        return -1;
    }

    if (WIFEXITED(*wstatus))
    {
        printf("Child exited with %d\n", WEXITSTATUS(*wstatus));
    }
    else if (WIFSIGNALED(*wstatus))
    {
        printf("Child killed by signal %d\n", WTERMSIG(*wstatus));
    }

    return 0;
}

int terminate_process(pid_t pid)
{
    int wstatus;

    if (kill(pid, SIGTERM) == -1)
    {
        printf("kill() failed");
        return EX_OSERR;
    }

    if (wait_for_process(pid, &wstatus) == -1) return -1;

    return 0;
}

int execute_process(const char *path, char *const args[], pid_t *child)
{
    int pipefd[2];
    int child_exec_error = 0, ret = 0, wirite_end_flags = 0;

    if (pipe(pipefd)) 
    {
        perror("pipe() failed");
        return EX_OSERR;
    }

    if ((wirite_end_flags = fcntl(pipefd[PIPE_WRITE_END], F_GETFD)) == -1)
    {
        perror("fcntl() failed");
        ret = EX_OSERR;
        goto syserror;
    }

    if (fcntl(pipefd[PIPE_WRITE_END], F_SETFD, wirite_end_flags | FD_CLOEXEC) == -1) 
    {
        perror("fcntl() failed");
        ret = EX_OSERR;
        goto syserror;
    }

    switch (*child = fork()) 
    {
        case -1:
        {
            perror("fork() failed");
            ret = EX_OSERR;
            goto syserror;
        }

        case 0:
        {
            close(pipefd[PIPE_READ_END]);
            execv(path, args);

            if (write(pipefd[PIPE_WRITE_END], &errno, sizeof(errno)) == -1) 
            {
                perror("write() failed");
                _exit(EX_OSERR);
            }
            _exit(1);
        }

        default:
        {
            close(pipefd[PIPE_WRITE_END]);

            if (read(pipefd[PIPE_READ_END], &child_exec_error, sizeof(errno)) > 0)
            {
                fprintf(stderr, "execv() failed: %s\n", strerror(child_exec_error));
                close(pipefd[PIPE_READ_END]);
                return EX_UNAVAILABLE;
            }

            close(pipefd[PIPE_READ_END]);

        }
    }

    return child_exec_error;

syserror:

    close(pipefd[PIPE_WRITE_END]);
    close(pipefd[PIPE_READ_END]);
    return ret;
}

