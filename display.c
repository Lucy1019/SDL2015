#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>


struct display{
    int height,width,imagewidth, imageheight;
    SDL_Surface *surface;
    SDL_Window *window;
    SDL_Surface *image[128];
    SDL_Event *event;
};

typedef struct display display;

void drawEnity(display *d,int what,int x, int y);
void drawFrame(display *d);
static void SDL_Fail(char *s);
static void loadImage(display *d, int what, char *filename);
static void loadAllImages(display *d);
void QuitGame(display *d);

int main(void)
{
    
    display *d=malloc(sizeof(display));
    d->height=600;
    d->width=400;
    
    /*Did not initialise these because the size was not working*/
    /*int h=d->height*8;
    int w=d->width*9;
    */
    int result=SDL_Init(SDL_INIT_VIDEO);
    if (result<0) {
        SDL_Fail("Bad SDL");
    }
    d->window=SDL_CreateWindow("niconiconi", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 400,SDL_WINDOW_SHOWN);
    if (d->window==NULL) {
        SDL_Fail("Could not create window");
    }
    d->surface=SDL_GetWindowSurface(d->window);
    if (d->surface==NULL) {
        SDL_Fail("Could not create surface");
    }
    loadAllImages(d);
    d->event=malloc(sizeof(SDL_Event));
    /*drawEnity(d,3,0,0);
    drawFrame(d);
    SDL_FreeSurface(d->surface);*/
    drawEnity( d,1, 0, 0);
    drawEnity( d,2, 0, 150);
    drawFrame(d);
    QuitGame(d);
    free(d);
    free(d->event);
    return 0;
}



static void loadImage(display *d, int what, char *filename){
    /* char path[100];*/
    /*  strcpy(filename);*/
    SDL_Surface *image=SDL_LoadBMP(filename);
    if (image==NULL) {
        SDL_Fail("Bad image file");
    }
    if (image->w!=d->imagewidth) {
        SDL_Fail("Bad image size");
    }
    if (image->h!=d->imageheight) {
        SDL_Fail("Bad image size");
    }
    
    d->image[what]=image;
}

static void loadAllImages(display *d){
    loadImage(d,1,"Restuarant.bmp");
    loadImage(d,2,"ball.bmp");
    loadImage(d,3,"image.bmp");
}

void drawFrame(display *d){
    int r=SDL_UpdateWindowSurface(d->window);
    if (r<0) {
        SDL_Fail("Bad window repaint");
        SDL_Delay(20);
    }
}

void QuitGame(display *d){
    SDL_Delay(15000);
    SDL_Quit();
}

void drawEnity( display *d,int what,int x, int y){
    int px=x*d->imagewidth;
    int py=y*d->imageheight;
    int h=d->height*8;
    int w=d->width*9;
    
    SDL_Surface *image=d->image[what];
    if (image==NULL) {
        SDL_Fail("No image");
    }
    
    SDL_Rect box_structure={x,y,d->imagewidth,d->imageheight};
    SDL_Rect *box=&box_structure;
    int r=SDL_BlitSurface(image,NULL,d->surface,box);
    if (r<0) {
        SDL_Fail("Bad image display");
    }
}

static void SDL_Fail(char *s) {
    fprintf(stderr,"%s %s \n",s,SDL_GetError());
    SDL_Quit();
    exit(1);
}
