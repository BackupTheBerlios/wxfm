#ifndef PortableFileAPI_h
#define PortableFileAPI_h

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#define PFA_ERROR  -1
#define PFA_FILE    1
#define PFA_DIR     2

/* file stat functions */

/* returns -1 on error */
#ifdef unix
long long PFA_GetFileSize (const char * path);
#endif
#ifdef WIN32
__int64 PFA_GetFileSize (const char * path);
#endif

int PFA_GetFileType (const char * path);

int PFA_GetFileTime (const char * path, time_t * created, time_t * modified, time_t * accessed);

#ifdef __cplusplus
}
#endif

#endif /* PortableFileAPI_h */
