#ifndef MISC_H
#define MISC_H

extern void misc_inv(unsigned char *channel, int width, int height);
extern void misc_av_threshold(unsigned char *channel, int width, int height);
extern void misc_multiply(unsigned char *channel, unsigned char *arg, int width, int height);

#endif  /* MISC_H */
