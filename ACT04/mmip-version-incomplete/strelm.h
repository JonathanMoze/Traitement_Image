#ifndef STRELM_H
#define STRELM_H


extern unsigned char strelm_disk_getmin(unsigned char *channel, int width, int height,
					int ip, int jp, int radius);

extern unsigned char strelm_disk_getmax(unsigned char *channel, int width, int height,
					int ip, int jp, int radius);

extern unsigned char strelm_rect_getmin(unsigned char *channel, int width, int height,
					int ip, int jp, int radius, int mode);

extern unsigned char strelm_rect_getmax(unsigned char *channel, int width, int height,
					int ip, int jp, int radius, int mode);


extern void strelm_disk_trace(unsigned char *channel, int width, int height,
			      int ip, int jp, int radius);


#endif  /* STRELM_H */
