#define _LARGEFILE64_SOURCE 1

#include "PortableFileAPI.h"

#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                               solaris                                */
/************************************************************************/

#ifdef solaris

#define INT64_FORMAT "%lld"

#include <sys/types.h>
#include <sys/stat.h>

int PFA_stat (const char * path, PFA_STAT * st)
{
	struct stat64 buf;
	
	if (stat64(path, &buf) != 0)
	{
		return -1;
	}
	
	st->pfst_dev = buf.st_dev;
	st->pfst_ino = buf.st_ino;
	st->pfst_mode = buf.st_mode;
	st->pfst_nlink = buf.st_nlink;
	st->pfst_uid = buf.st_uid;
	st->pfst_gid = buf.st_gid;
	st->pfst_rdev = buf.st_rdev;
	st->pfst_size = buf.st_size;
	st->pfst_atime = buf.st_atime;
	st->pfst_ctime = buf.st_ctime;
	st->pfst_mtime = buf.st_mtime;
	
	return 0;
}

#endif /* solaris */

/************************************************************************/
/*                               linux                                  */
/************************************************************************/

#ifdef linux

#define INT64_FORMAT "%lld"

#include <sys/types.h>
#include <sys/stat.h>

int PFA_stat (const char * path, PFA_STAT * st)
{
	struct stat64 buf;
	
	if (stat64(path, &buf) != 0)
	{
		return -1;
	}
	
	st->pfst_dev = buf.st_dev;
	st->pfst_ino = buf.st_ino;
	st->pfst_mode = buf.st_mode;
	st->pfst_nlink = buf.st_nlink;
	st->pfst_uid = buf.st_uid;
	st->pfst_gid = buf.st_gid;
	st->pfst_rdev = buf.st_rdev;
	st->pfst_size = buf.st_size;
	st->pfst_atime = buf.st_atime;
	st->pfst_mtime = buf.st_mtime;
	st->pfst_ctime = buf.st_ctime;
	
	return 0;
}

#endif /* linux */


/************************************************************************/
/*                                WIN32                                 */
/************************************************************************/

#ifdef WIN32

#define INT64_FORMAT "%I64d"

#include <sys/stat.h>

int PFA_stat (const char * path, PFA_STAT * st)
{
	struct _stati64 buf;
	
	if (_stati64(path, &buf) != 0)
	{
		return -1;
	}
	
	st->pfst_dev = buf.st_dev;
	st->pfst_ino = buf.st_ino;
	st->pfst_mode = buf.st_mode;
	st->pfst_nlink = buf.st_nlink;
	st->pfst_uid = buf.st_uid;
	st->pfst_gid = buf.st_gid;
	st->pfst_rdev = buf.st_rdev;
	st->pfst_size = buf.st_size;
	st->pfst_atime = buf.st_atime;
	st->pfst_mtime = buf.st_mtime;
	st->pfst_ctime = buf.st_ctime;
	
	return 0;
}

#endif /* WIN32 */


/************************************************************************/
/*                                common                                */
/************************************************************************/

#define PFA_printf1c(argument_type, converted_value)\
{\
	converted_value x = (converted_value) va_arg(ap, argument_type);\
	if (i)\
	{\
		sprintf (s, fmt, i, x);\
	}\
		else\
	{\
		sprintf (s, fmt, x);\
	}\
	break;\
}

#define PFA_printf1(argument_type)\
{\
	if (i)\
	{\
		sprintf (s, fmt, i, va_arg(ap, argument_type));\
	}\
		else\
	{\
		sprintf (s, fmt, va_arg(ap, argument_type));\
	}\
	break;\
}


int PFA_printf(const char *format, ...)
{
	char out[1024], *f = out, s[128], fmt[128], q;
	va_list ap;
	const char *p = format;
	int i;
	
	va_start (ap, format);
	
	while (*p)
	{
		while (*p && *p != '%')
		{
			*f++ = *p++;
		}
		
		if (*p == '%')
		{
			if (p != format && (*(p-1) == '%' || *(p-1) == '\\'))
			{
                *f++ = *p++;
				continue;
			}
			
			fmt[0] = *p++;
			i = strspn (p, "+-# 0123456789*.");
			if (p[i] == 0)
			{
				break;
			}
			
			strncpy (fmt + 1, p, i + 2);
			fmt[i + 2] = 0;
			p += i;
			
			if (strchr(fmt, '*'))
			{
				i = va_arg(ap, int);
			}
			else
			{
				i = 0;
			}
			
			if (*p == 'h' || *p == 'l' || *p == 'L')
			{
				q = *p++;
			}
			else
			{
				q = ' ';
			}
			
			switch (*p)
			{
				case 'c':
					switch (q)
					{
						case ' ': PFA_printf1c(int, unsigned char);
						case 'l': PFA_printf1c(wint_t, wchar_t *);
						default: return -1;
					}
					break;

				case 'd':
				case 'i':
					switch (q)
					{
						case ' ': PFA_printf1c(int, int);
						case 'h': PFA_printf1c(int, short);
						case 'l': PFA_printf1c(long, long);
						default: return -1;
					}
					break;

				case 'e':
				case 'E':
				case 'f':
				case 'F':
				case 'g':
				case 'G':
					switch (q)
					{
						case ' ': PFA_printf1c(double, double);
						case 'l':
						case 'L': PFA_printf1c(long double, long double);
						default: return -1;
					}
					break;
				
				case 'n':
					switch (q)
					{
						case ' ': PFA_printf1(int *);
						case 'h': PFA_printf1(short *);
						case 'l': PFA_printf1(long *);
						default: return -1;
					}
					break;

				case 'o':
				case 'u':
				case 'x':
				case 'X':
					switch (q)
					{
						case ' ': PFA_printf1c(int, int);
						case 'h': PFA_printf1c(int, short);
						case 'l': PFA_printf1c(long, long);
						default: return -1;
					}
					break;

				case 'p':
					switch (q)
					{
						case ' ': PFA_printf1c(void *, void *);
						default: return -1;
					}
					break;

				case 's':
					switch (q)
					{
						case ' ': PFA_printf1(char *);
						case 'l': PFA_printf1(wchar_t *);
						default: return -1;
					}
					break;
						
				case 'q':
					sprintf (s, INT64_FORMAT, va_arg(ap, int64));
					break;
			}
			
            strcpy (f, s);
			f += strlen (s);
			p++;
		}
	}
	
	*f = 0;
	
	return printf ("%s", out);
}
