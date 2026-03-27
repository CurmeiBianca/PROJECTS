#include <sys/socket.h> 
#include <string.h> 
#include <unistd.h> 
#include "utils.h" 
#include "protocol.h" 

int send_message (int sock, const char *msg)
{
    char tmp[BUFFER_SIZE]; 
    memset (tmp, 0, BUFFER_SIZE); 

    if (msg != NULL)
        strncpy (tmp, msg, BUFFER_SIZE - 1);

    return send (sock, tmp, BUFFER_SIZE, 0);
}

int recv_message (int sock, char *buffer)
{
    memset (buffer, 0, BUFFER_SIZE); 

    return recv (sock, buffer, BUFFER_SIZE, 0);
}

void trim_whitespace (char *str)
{
    if (str == NULL)
        return;

    int len = strlen(str);

    while (
        len > 0 && 
        (
            str[len - 1] == ' ' || 
            str[len - 1] == '\n' || 
            str[len - 1] == '\r' || 
            str[len - 1] == '\t'
        )
    )
    {
        str[len - 1] = '\0';
        len --;
    }
}