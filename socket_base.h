#ifndef __SOCKET_BASE_H
#define __SOCKET_BASE_H
#ifdef WIN32
#include "winsock2.h"
#else
#endif
#include "stdafx.h"
#include <stdio.h>

namespace base
{
int close(int fd);
}//base



#endif //__THREAD_BASE_H

