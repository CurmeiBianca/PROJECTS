#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> 

void trim_whitespace (char *str);
int recv_message (int sock, char *buffer);
int send_message (int sock, const char *msg);

#endif
