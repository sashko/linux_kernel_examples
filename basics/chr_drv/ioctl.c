#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)


int main()
{
	char buf[1024];
	int fd = -1;

	if ((fd = open("/dev/chrpooldev", O_RDWR)) < 0) {
		perror("device opening");
		return -1;
	}

	if (ioctl(fd, WRITE_IOCTL, "hello, linux kernel newbies! how are you doing?") < 0) {
		perror("WRITE_IOCTL,");
		return -1;
	}

	if (ioctl(fd, READ_IOCTL, buf) < 0) {
		perror("READ_IOCTL");
		return -1;
	}

	printf("message: %s\n", buf);

	return 0;
}
