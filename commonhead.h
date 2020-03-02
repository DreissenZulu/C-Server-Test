// Shared header info between client and server
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
// sys/socket.h does not exist in the Windows environment
// The ifdef will use socket.h if in a UNIX environment
#ifdef _WIN32
# include <winsock2.h>
# define SYSTEM "Windows"
#else
# include <sys/socket.h>
# include <netinet/in.h>
#endif