#ifndef PortableFileAPI_h
#define PortableFileAPI_h

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

/* 64 bit integer type */
#ifdef WIN32
typedef __int64		int64;
#else
typedef long long	int64;
#endif

/* file stat structure */
typedef struct {
	unsigned int	st_dev;
	unsigned short	st_ino;
	unsigned short	st_mode;
	short			st_nlink;
	short			st_uid;
	short			st_gid;
	unsigned int	st_rdev;
	int64			st_size;
	time_t			st_atime;
	time_t			st_mtime;
	time_t			st_ctime;
} PFA_STAT;

/* file stat function */
int64 PFA_stat (const char * path, PFA_STAT * st);

#ifdef __cplusplus
}
#endif

#endif /* PortableFileAPI_h */
