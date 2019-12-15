#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (640)
#define SPEED (300)
#define FPS (60)
#define TILESIZE (32)

/** 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster **/

int playing = 0;
char PROJECT_TITLE[] = "Labyrinth of Elrualia";

SDL_Window* win;
SDL_Renderer* rend;



/* ------------------------------ */

/* ----- Struct ----- */

/* ------------------------------ */
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

    int map[60][60];

    int up;
    int down;
    int left;
    int right;
} game;

struct
{
    SDL_Surface* surf;
    SDL_Texture* text;
    SDL_Rect rect;

    int pos[2];
    int health;
    int flower;
    int coin;
    int key;
    int kill;
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

void quit_game()
{
    /** Wait a few seconds **/
    SDL_Delay(1000);

    /** Clean up **/
    int i;
    for (i=0; i<9; i++)
    {
        SDL_DestroyTexture(tile[i].text);
    }
    SDL_DestroyTexture(player.text);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void update()
{
}



/* ------------------------------ */

/* ----- Initialization Functions ----- */

/* ------------------------------ */
void init()
{
    game.playing = 0;
    srand(time(NULL));
    init_SDL();

    game.tile_height = WINDOW_HEIGHT / TILESIZE;
    game.tile_width = WINDOW_WIDTH / TILESIZE;
}

int init_SDL()
{
    /** Initialization **/
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    /** Window **/
    win = SDL_CreateWindow(PROJECT_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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
    SDL_Surface* surface = IMG_Load("surface.png");
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
}

void load()
{
    load_tile(&tile[0], "data/graphics/tile_lpc_grass.png");
    load_tile(&tile[1], "data/graphics/tile_lpc_flower.png");
    load_tile(&tile[2], "data/graphics/tile_lpc_tree.png");
    load_tile(&tile[3], "data/graphics/tile_lpc_rock.png");
    load_tile(&tile[4], "data/graphics/item_raventale_loot_05_key.png");
    load_tile(&tile[5], "data/graphics/item_raventale_loot_04_coins.png");
    load_tile(&tile[6], "data/graphics/item_raventale_loot_06_chest.png");
    load_tile(&tile[7], "data/graphics/tile_lpc_trap.png");
    load_tile(&tile[8], "data/graphics/character_pipoya_enemy_04_1.png");

    player.surf = IMG_Load("data/graphics/character_pipoya_male_01_2.png");
    player.text = SDL_CreateTextureFromSurface(rend, player.surf);
    player.rect.w = TILESIZE; player.rect.h = TILESIZE;
    player.pos[0] = 0;
    player.pos[1] = 0;
    player.health = 10;
    player.flower = 0;
    player.coin = 0;
    player.key = 0;
    player.kill = 0;


    int map_001[20][20] =
        {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 5},
        {0, 1, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 8, 0, 0, 0, 0, 0, 3, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 8, 8, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 3, 3, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 5},
        {0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 3, 3, 3},
        {5, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0},
        {0, 0, 3, 0, 0, 8, 8, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 5}
        };

    load_map(map_001);
}

void load_tile(struct image *tile, char directory[])
{
    struct image t_tile;
    t_tile.surf = IMG_Load(directory);
    t_tile.text = SDL_CreateTextureFromSurface(rend, t_tile.surf);
    t_tile.rect.w = TILESIZE; t_tile.rect.h = TILESIZE;

    *tile = t_tile;
}

void load_map(int map[20][20])
{
    int l; int c;
    for (l=0; l<game.tile_height; l++)
    {
        for (c=0; c<game.tile_width; c++)
        {
            game.map[l][c] = map[l][c];
        }
    }
}



/* ------------------------------ */

/* ----- Events Functions ----- */

/* ------------------------------ */
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

        case SDL_KEYUP:
            switch(event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                player.pos[1] -= 1;
                break;

            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                player.pos[1] += 1;
                break;

            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                player.pos[0] -= 1;
                break;

            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                player.pos[0] += 1;
                break;
            }
            break;
        }
    }
}



/* ------------------------------ */

/* ----- Draw Functions ----- */

/* ------------------------------ */
void draw()
{
    /* Clear the window */
    SDL_RenderClear(rend);

    /* Draw texture */
    draw_map();

    /* Render to the window */
    SDL_RenderPresent(rend);

    /* FPS */
    SDL_Delay(1000/FPS);
}

void draw_map()
{
    int l; int c; int t;
    for (l = 0; l < game.tile_height; l++)
    {
        for (c = 0; c < game.tile_width; c++)
        {
            t = game.map[l][c];
            tile[t].rect.y = 32*l;
            tile[t].rect.x = 32*c;
            SDL_RenderCopy(rend, tile[t].text, NULL, &tile[t].rect);
        }
    }
    player.rect.x = 32 * player.pos[0];
    player.rect.y = 32 * player.pos[1];
    SDL_RenderCopy(rend, player.text, NULL, &player.rect);
}

