#ifndef PortableFileAPI_h
#define PortableFileAPI_h

#ifdef __cplusplus
extern "C" {
#endif

#define _LARGEFILE64_SOURCE 1

#include <stdarg.h>

/* 64 bit integer type */
#ifdef WIN32
typedef __int64		int64;
#else
typedef long long	int64;
#endif

/* printf extension for int64 (format specifier is "%q") */
int PFA_printf(const char *format, /* args*/ ...);

/* file stat structure */
typedef struct {
	int64			pfst_dev;
	int64			pfst_ino;
	int64			pfst_mode;
	int64			pfst_nlink;
	int64			pfst_uid;
	int64			pfst_gid;
	int64			pfst_rdev;
	int64			pfst_size;
	int64			pfst_atime;
	int64			pfst_mtime;
	int64			pfst_ctime;
} PFA_STAT;

/* file stat function */
int PFA_stat (const char * path, PFA_STAT * st);

#ifdef __cplusplus
}
#endif

#endif /* PortableFileAPI_h */
