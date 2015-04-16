#ifndef _DEFS_H_
#define _DEFS_H_
#ifdef WIN32
#include<ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int SOCKET;
extern const int SERVER_PORT;
extern const int INVALID_SOCKET;
extern const int SOCKET_ERROR;
#endif
#include "trace_worker.h"
#endif

