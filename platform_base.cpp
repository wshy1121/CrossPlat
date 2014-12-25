#include "stdafx.h"
#include "platform_base.h"

#if WIN32
#else
#include <sys/timeb.h>
#endif


namespace base
{
#if WIN32
int usleep(int micro_second)
{
	if (micro_second < 1000)
	{
		micro_second = 1000;
	}
	
	Sleep(micro_second / 1000);
	return 0;
}
int ftime(TimeB *tp)
{
	memset(tp, 0, sizeof(TimeB));
	return 0;
}

FILE *fopen(const char *path, const char *mode)
{
	FILE *fp = NULL;
	fopen_s(&fp, path, mode);
	return fp;
}


#else
int usleep(int micro_second)
{
	return ::usleep(micro_second);
}

int ftime(TimeB *tp)
{
	struct timeb timeB;
	int ret = ::ftime(&timeB);

	tp->time = timeB.time;
	tp->millitm = timeB.millitm;
	tp->timezone = timeB.timezone;
	tp->dstflag = timeB.dstflag;
	return ret;
}

FILE *fopen(const char *path, const char *mode)
{
	return ::fopen(path, mode);
}

#endif
}//base



