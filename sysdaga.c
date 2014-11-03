#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "sysdaga.h"

int sysdagad()
{
	int maxfd, fd;

	switch(fork()) {
	case -1:
		return -1;
	/* Become child of init */
	case 0:
		break;
	default:
	/* Parent exits */
		_exit(EXIT_SUCCESS);
	}

	/* Start a new session */
	if (setsid() == -1)
		return -1;

	/* Clear file mode creation mask to ensure having the needed permissions. */
	umask(0);

	/* Change to root directory.
	 * The file system cannot be unmounted if at shutdown the daemon isn't there.
	 * We can also move the daemon to a place where the file system isn't needed
	 * to be unmounted.
     */
	chdir("/");

	/* Close (all) the unused fds. */
	maxfd = sysconf(_SC_OPEN_MAX);
	/* If the limit is unknown make a guess,
	 * since my /proc/sys/fs/file-max shows 386361, choose that.*/
	if (maxfd == -1)
		maxfd = SYSDAGA_MAX_FD;
	for (fd = 0; fd < maxfd; fd++)
		close(fd);

	/* Set fds 0, 1 and 3 to /dev/null */
	fd = open("/dev/null", O_RDWR);

	if (fd != STDIN_FILENO) /* We must have STDIN. */
		return -1;
	if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
		return -1;
	if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
		return -1;

	return 0;
}

int main(int argc, char *argv[])
{
	sysdagad();
	sleep(30);
	exit(EXIT_SUCCESS);
}
