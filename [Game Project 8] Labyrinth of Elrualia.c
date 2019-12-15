#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (640)
#define SPEED (300)
#define FPS (60)
#define TILESIZE (32)

int playing = 0;
char PROJECT_TITLE[] = "Labyrinth of Elrualia";

SDL_Window* win;
SDL_Renderer* rend;
SDL_Surface* surface;
SDL_Texture* tex;

struct image
{
    SDL_Surface* surf;
    SDL_Texture* text;
    SDL_Rect rect;
} tile[9];

struct
{
    int playing;

    int tile_width;
    int tile_height;

    int up;
    int down;
    int left;
    int right;
} game;

struct
{
    float x_pos;
    float y_pos;

    float x_vel;
    float y_vel;
} player;

SDL_Rect dest;



/* ------------------------------ */

/* ----- Main Functions ----- */

/* ------------------------------ */
int main(int argc, char *argv[])
{
    init();
    load();
    while (!game.playing)
    {
        events();
        update();
        draw();
    }

    quit_game();
    return 0;
}

void init()
{
    game.playing = 0;
    srand(time(NULL));
    init_SDL();

    game.tile_width = WINDOW_WIDTH / TILESIZE;
    game.tile_height = WINDOW_HEIGHT / TILESIZE;

    /* Get the dimensions of the texture */
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;

    /* X & Y position */
    player.x_pos = (WINDOW_WIDTH - dest.w) / 2;
    player.y_pos = (WINDOW_HEIGHT - dest.h) / 2;

    /* X & Y Velocity */
    player.x_vel = 0;
    player.y_vel = 0;
}

void load_tile(struct image *tile, char directory[])
{
    struct image t_tile;
    t_tile.surf = IMG_Load(directory);
    t_tile.text = SDL_CreateTextureFromSurface(rend, t_tile.surf);
    t_tile.rect.w = TILESIZE; t_tile.rect.h = TILESIZE;

    *tile = t_tile;
}

void load()
{
    load_tile(&tile[0], "data/tilesheet/dirt.png");
}

void events()
{
    /* Events */
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            game.playing = 1;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                game.up = 1;
                break;

            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                game.down = 1;
                break;

            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                game.left = 1;
                break;

            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                game.right = 1;
                break;
            }
            break;

        case SDL_KEYUP:
            switch(event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                game.up = 0;
                break;

            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                game.down = 0;
                break;

            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                game.left = 0;
                break;

            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                game.right = 0;
                break;
            }
            break;
        }
    }
}

void update()
{
    /* Determine velocity */
    player.x_vel = player.y_vel = 0;
    if (game.up && !game.down) player.y_vel = -SPEED;
    if (game.down && !game.up) player.y_vel = SPEED;
    if (game.left && !game.right) player.x_vel = -SPEED;
    if (game.right && !game.left) player.x_vel = SPEED;

    /* Update position */
    player.x_pos += player.x_vel / FPS;
    player.y_pos += player.y_vel / FPS;

    /* Collision with bounds */
    if (player.x_pos <= 0) player.x_pos = 0;
    if (player.y_pos <= 0) player.y_pos = 0;
    if (player.x_pos >= WINDOW_WIDTH - dest.w) player.x_pos = WINDOW_WIDTH - dest.w;
    if (player.y_pos >= WINDOW_HEIGHT - dest.h) player.y_pos = WINDOW_HEIGHT - dest.h;

    /* Set position in the struct */
    dest.x = (int) player.x_pos;
    dest.y = (int) player.y_pos;
}

void draw()
{
    /* Clear the window */
    SDL_RenderClear(rend);
    draw_map();

    /* Draw image to the window */
    SDL_RenderCopy(rend, tex, NULL, &dest);
    SDL_RenderPresent(rend);

    /* 60 FPS */
    SDL_Delay(1000/FPS);
}

void quit_game()
{
    /** Wait a few seconds **/
    SDL_Delay(1000);

    /** Clean up **/
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int init_SDL()
{
    /** Initialization **/
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow(PROJECT_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    /** Window **/
    if (!win)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /** Renderer **/
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /** Surface **/
    surface = IMG_Load("surface.png");
    if (!surface)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    /** Texture **/
    tex = SDL_CreateTextureFromSurface(rend, surface);
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
}



void draw_map()
{
    int i; int j;
    for (i = 0; i < game.tile_width; i++)
    {
        for (j = 0; j < game.tile_height; j++)
        {
            tile[0].rect.x = 32*i;
            tile[0].rect.y = 32*j;
            SDL_RenderCopy(rend, tile[0].text, NULL, &tile[0].rect);
        }
    }
}

