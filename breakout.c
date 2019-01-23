#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int SCREEN_HEIGHT = 3;
int SCREEN_WIDTH = 5;

int ball_dirx = 1;
int ball_diry = 1;

int ball_posx = 3;
int ball_posy = 2;

void draw_box(int x, int w, int width, int height)
{

}

void draw_pixel(int x, int y, int color)
{
	
}

void game_loop(void)
{
	int delta;

	while (1)
	{
		if (ball_posx > SCREEN_WIDTH)
		{
			ball_dirx = -1;
		}
		else if (ball_posx < 1)
		{
			ball_dirx = 1; 
		}

		if (ball_posy > SCREEN_HEIGHT)
		{
			ball_diry = -1;
		} else if (ball_posy < 1)
		{
			ball_diry = 1;
		}

		ball_posx += ball_dirx;
		ball_posy += ball_diry;


		printf("ball direction x: %d, ball direction y: %d\n", ball_dirx, ball_diry);
		sleep(1);
	}
}

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

	game_loop();

	return (0);
}
