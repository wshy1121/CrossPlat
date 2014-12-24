#include "stdafx.h"
#include "string_base.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

namespace base
{
#ifdef WIN32
char *strncpy(char *dest, const char *src, size_t n)
{
	strcpy_s(dest, n, src);
	return dest;
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	return vsnprintf_s(str, size, _TRUNCATE, format, ap);
}

int snprintf(char *str, size_t size, const char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	int ret = vsnprintf_s(str, size, _TRUNCATE, format, ap);
	va_end(ap);
	return ret;
}
#else
char *strncpy(char *dest, const char *src, size_t n)
{
	return ::strncpy(dest, src, n);
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	return ::vsnprintf(str, size, format, ap);
}

int snprintf(char *str, size_t size, const char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	int ret = ::vsnprintf(str, size, format, ap);
	va_end(ap);
	return ret;
}
#endif
}//base



