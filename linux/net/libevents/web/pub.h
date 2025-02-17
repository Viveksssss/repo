#ifndef _PUB_
#define _PUB_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif
    const char *get_mine_type(const char *name);
    int get_line(int sock, char *buf, int size);
    int hexit(char c);
    void strencode(char *to, size_t tosize, const char *from);
    void strdecode(char *to, char *from);

#ifdef __cplusplus
}


#endif

#endif