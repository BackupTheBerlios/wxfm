#include "PortableFileAPI.h"

/************************************************************************/
/*                               unix                                   */
/************************************************************************/

#ifdef unix

#include <sys/types.h>
#include <sys/stat.h>

int64 PFA_stat (const char * path, PFA_STAT * st)
{
	struct stat64 buf;

	if (stat64(path, &buf) != 0)
	{
		return -1;
	}

	
}

#endif /* solaris */

/************************************************************************/
/*                                WIN32                                 */
/************************************************************************/

#ifdef WIN32

#include <sys/stat.h>

int64 PFA_stat (const char * path, PFA_STAT * st)
{
	struct _stati64 si64;

	if (_stati64(path, &si64) != 0)
	{
		return -1;
	}

	st->st_dev = si64.st_dev;
	st->st_ino = si64.st_ino;
	st->st_mode = si64.st_mode;
	st->st_nlink = si64.st_nlink;
	st->st_uid = si64.st_uid;
	st->st_gid = si64.st_gid;
	st->st_rdev = si64.st_rdev;
	st->st_size = si64.st_size;
	st->st_atime = si64.st_atime;
	st->st_mtime = si64.st_mtime;
	st->st_ctime = si64.st_ctime;

	return 0;
}

#endif /* WIN32 */
