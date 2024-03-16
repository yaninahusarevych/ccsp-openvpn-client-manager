#include "utils.h"

void openvpnmgr_log(const char* format, ...) 
{
    FILE* file = fopen("/tmp/openvpnmgr.txt", "a");
    if (file) {
        va_list args;
        va_start(args, format);
        vfprintf(file, format, args);
        fprintf(file, "\n");
        va_end(args);
        fclose(file);
    }
}