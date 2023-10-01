#include <stdio.h>
#include <assert.h>
#include <imago2.h>

int main( int argc, char *argv[])
{
    assert(argc == 2);
    char* input = argv[1];
    struct img_pixmap *img = img_create();
    int i = img_load(img, input);
    
    if(i == -1){
        printf("img-format: cannot load \"%s\"\n", input);
        return 1;
    }

    int is_grey_scale = img_is_greyscale(img);
    int is_float = img_is_float(img);
    int is_alpha = img_has_alpha(img);

    printf("\"%s\": ", input);

    if(is_grey_scale){
        printf("grayscale "); 
    }else{
        printf("RGB ");
    }

    if(is_float){
        printf("16 bits image ");
    }else{
        printf("8 bits image ");
    }

    if(is_alpha){
        printf("with alpha channel\n");
    }else{
        printf("without alpha channel\n");
    }

    return 0;
}