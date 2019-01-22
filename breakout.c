#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main(int ac, char **av)
{
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	char *fbp = 0;
	long int screensize = 0;

	fbfd = open("/dev/fb0", O_RDWR);

	if (fbfd == -1) {
		printf("Error: can't open framebuffer");
		return (1);
	}

	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable screen info. \n");
	}

	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reafing fixed screen info. \n");
	}

	screensize = finfo.smem_len;

	fbp = (char *) mmap(0,
			screensize, 
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fbfd, 0);

	if ((int) fbp == -1) {
		printf("Failed to mmap. \n");
	} else {
		
	}

	munmap(fbp, screensize);
	close(fbfd);

	return (0);
}
