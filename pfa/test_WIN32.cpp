#include "PortableFileAPI.h"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	PFA_STAT st;

	if (PFA_stat (__FILE__, &st) != 0)
	{
		fprintf (stderr, "error: PFA_stat\n");
		exit (1);
	}

	printf ("stat(\"%s\"):\n", __FILE__);
	printf ("st_dev = %u\n", st.st_dev);
	printf ("st_ino = %u\n", st.st_ino);
	printf ("st_mode = %u\n", st.st_mode);
	printf ("st_nlink = %d\n", st.st_nlink);
	printf ("st_uid = %d\n", st.st_uid);
	printf ("st_gid = %d\n", st.st_gid);
	printf ("st_rdev = %u\n", st.st_rdev);
	printf ("st_size = %d\n", st.st_size);
	printf ("st_atime = %u\n", st.st_atime);
	printf ("st_mtime = %u\n", st.st_mtime);
	printf ("st_ctime = %u\n", st.st_ctime);

	return 0;
}
