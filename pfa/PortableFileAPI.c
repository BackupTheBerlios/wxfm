#include "PortableFileAPI.h"

/************************************************************************/
/*                      solaris                                         */
/************************************************************************/

#ifdef solaris

#include <sys/types.h>
#include <sys/stat.h>

/*long PFA_GetFileSize (const char * path)
{
	struct stat buf;

	return lstat(path, &buf) ? -1 : buf.st_size;
}*/

long long PFA_GetFileSize (const char * path)
{
	struct stat64 buf;

	return lstat64(path, &buf) ? -1 : buf.st_size;
}

int PFA_GetFileType (const char * path)
{
	struct stat64 buf;

	return lstat64(path, &buf) ? PFA_ERROR : (buf.st_mode & S_IFDIR ? PFA_DIR : PFA_FILE);
}

#endif /* solaris */

/************************************************************************/
/*                        WIN32                                         */
/************************************************************************/

#ifdef WIN32

#include <windows.h>
#include <sys/stat.h>
__int64 PFA_GetFileSize (const char * path)
{
	struct _stati64 si64;

	return _stati64(path, &si64) ? -1 : si64.st_size;
}

int PFA_GetFileType (const char * path)
{
	struct _stati64 buf;

	return _stati64(path, &buf) ? PFA_ERROR : (buf.st_mode & S_IFDIR ? PFA_DIR : PFA_FILE);
}

int PFA_GetFileTime (const char * path, time_t * created, time_t * modified, time_t * accessed)
{
	struct _stati64 buf;

	if (_stati64(path, &buf)) return PFA_ERROR;

	if (created) *created = buf.st_ctime;
	if (modified) *modified = buf.st_mtime;
	if (accessed) *accessed = buf.st_atime;

	return 0;
}

#endif /* win32 */
