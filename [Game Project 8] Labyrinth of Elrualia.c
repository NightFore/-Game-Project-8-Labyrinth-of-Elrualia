#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define SCROLL_SPEED (300)

int main(int argc, char *argv[])
{
    /** Initialization Error **/
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Hello, CS50!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    /** Winwdow Error **/
    if (!win)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /** Renderer **/
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /** Load the image into memory using SDL_image library function **/
    SDL_Surface* surface = IMG_Load("data/hello.jpg");
    if (!surface)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /** Load the image data into the graphics hardware's memory **/
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /** Animation **/
    /* Struct to hold the position and size of the sprite */
    SDL_Rect dest;

    /* Get the dimensions of the texture */
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    /* X & Y position */
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = WINDOW_HEIGHT;

    /** Animation Loop **/
    while (dest.y >= -dest.h)
    {
        /* Clear the window */
        SDL_RenderClear(rend);

        /* Y position */
        dest.y = (int) y_pos;

        /* Draw image to the window */
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

        /* Update sprite position */
        y_pos -= (float) SCROLL_SPEED / 60;

        /* 60 FPS */
        SDL_Delay(1000/60);
    }

    /** Clear the window **/
    SDL_RenderClear(rend);

    /** Draw the image to the window **/
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);

    /** Wait a few seconds **/
    SDL_Delay(5000);

    /** Clean up **/
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

