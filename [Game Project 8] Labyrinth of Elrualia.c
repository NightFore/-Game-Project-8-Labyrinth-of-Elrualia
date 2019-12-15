#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define SPEED (300)

int playing = 0;


/* ------------------------------ */

/* ----- Main Functions ----- */

/* ------------------------------ */
int main(int argc, char *argv[])
{
    /** Start Game **/
    init();
    while (!playing)
    {
        events();
        draw();
    }

    return 0;
}

void init()
{
    srand(time(NULL));
    init_SDL();
}

void events()
{
}

void draw()
{
}

int init_SDL()
{
    /** Initialization **/
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Hello, CS50!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    /** Winwdow **/
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

    /** Surface **/
    SDL_Surface* surface = IMG_Load("data/hello.jpg");
    if (!surface)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /** Texture **/
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
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
    dest.w /= 4;
    dest.h /= 4;

    /* X & Y position */
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;

    /* X & Y Velocity */
    float x_vel = 0;
    float y_vel = 0;

    /* Input */
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    /** Animation Loop **/
    while (!playing)
    {
        /* Events */
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                playing = 1;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;

                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;

                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;

            case SDL_KEYUP:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;

                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;

                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }

        /* Determine velocity */
        x_vel = y_vel = 0;
        if (up && !down) y_vel = -SPEED;
        if (down && !up) y_vel = SPEED;
        if (left && !right) x_vel = -SPEED;
        if (right && !left) x_vel = SPEED;

        /* Update position */
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        /* Collision with bounds */
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
        if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;

        /* Set position in the struct */
        dest.x = (int) x_pos;
        dest.y = (int) y_pos;

        /* Clear the window */
        SDL_RenderClear(rend);

        /* Draw image to the window */
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

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

