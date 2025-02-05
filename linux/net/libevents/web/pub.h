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

char *get_mine_type(char *name);
int get_line(int sock, char *buf, int size);
int hexit(char c);
void strencode(char *to, size_t tosize, const char *from);
void strdecode(char *to, char *from);

#endif