#include "PortableFileAPI.h"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
	PFA_STAT st;
	int64 i = 112233445566778899ll;

	if (PFA_stat (__FILE__, &st) != 0)
	{
		fprintf (stderr, "error: PFA_stat\n");
		exit (1);
	}
	PFA_printf ("pfstat(\"%s\"):\n", __FILE__);
	PFA_printf ("pfst_dev = %u\n", st.pfst_dev);
	PFA_printf ("pfst_ino = %u\n", st.pfst_ino);
	PFA_printf ("pfst_mode = %u\n", st.pfst_mode);
	PFA_printf ("pfst_nlink = %d\n", st.pfst_nlink);
	PFA_printf ("pfst_uid = %d\n", st.pfst_uid);
	PFA_printf ("pfst_gid = %d\n", st.pfst_gid);
	PFA_printf ("pfst_rdev = %u\n", st.pfst_rdev);
	PFA_printf ("pfst_size = %q\n", st.pfst_size);
	PFA_printf ("pfst_atime = %u\n", st.pfst_atime);
	PFA_printf ("pfst_mtime = %u\n", st.pfst_mtime);
	PFA_printf ("pfst_ctime = %u\n", st.pfst_ctime);

	PFA_printf ("112233445566778899=%q\n", i);
	PFA_printf ("%10d\n", 12345);
	PFA_printf ("%*d\n", 10, 12345);
	PFA_printf ("%c%d%f\n", 'a', 1234567, 1e+10);
	PFA_printf ("%x\n", 255);

	return 0;
}

