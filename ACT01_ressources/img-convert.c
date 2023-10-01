#include <stdio.h>
#include <assert.h>
#include <imago2.h>

int main( int argc, char *argv[])
{
    assert(argc == 3);

    char* input = argv[1];
    char* output = argv[2];

    struct img_pixmap *img = img_create();
    int i = img_load(img, input);
    assert(i != -1);
    int j = img_save(img, output);
    assert(j != -1);
    img_free(img);

    return 0;
}