#include "stdafx.h"
#include "defs.h"
#include "socket_base.h"

namespace base
{
#if WIN32
int close(int fd)
{
	return closesocket(fd);
}

#else
int close(int fd)
{
	return ::close(fd);
}

#endif
}//base



