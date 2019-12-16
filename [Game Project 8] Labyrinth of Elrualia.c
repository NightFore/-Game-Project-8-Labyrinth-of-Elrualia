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
#define TILENUMBER (9)

char PROJECT_TITLE[] = "Labyrinth of Elrualia";

/** 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster **/



/* ------------------------------ */

/* ----- Struct ----- */

/* ------------------------------ */
struct image
{
    SDL_Surface* surf;
    SDL_Texture* text;
    SDL_Rect rect;
} tile[TILENUMBER];

struct
{
    int playing;

    SDL_Window* win;
    SDL_Renderer* rend;

    int tile_width;
    int tile_height;

    int map[20][20];
    int map_001[20][20];
} game;

struct
{
    SDL_Surface* surf;
    SDL_Texture* text;
    SDL_Rect rect;

    int pos[2];
    int health;
    int coin;
    int key;
    int kill;
} player;



/* ------------------------------ */

/* ----- Prototyping ----- */

/* ------------------------------ */
void quit_game();

int init_SDL();
void init();
void select_map();
void load_tile(struct image *tile, char directory[]);
void load_map(int map1[20][20], int map2[20][20]);

void events();
void status();
void win_condition();
void new_game();
int player_collide();

void draw();
void draw_map();
void generate_map(int width, int height, int map[width][height]);
int *generate_position(int min_width, int min_height, int max_width, int max_height);
void generate_treasure(int object_1, int object_2, int object_3, int width, int height, int map[width][height]);



/* ------------------------------ */

/* ----- Main Functions ----- */

/* ------------------------------ */
int main(int argc, char *argv[])
{
    init_SDL();
    init();
    while (!game.playing)
    {
        events();
        draw();
    }
    return 0;
}

void quit_game()
{
    /** Wait a few seconds **/
    SDL_Delay(1000);

    /** Clean up **/
    int i;
    for (i=0; i<TILENUMBER; i++)
    {
        SDL_DestroyTexture(tile[i].text);
    }
    SDL_DestroyTexture(player.text);
    SDL_DestroyRenderer(game.rend);
    SDL_DestroyWindow(game.win);
    SDL_Quit();
}

/* ------------------------------ */

/* ----- Initialization Functions ----- */

/* ------------------------------ */
int init_SDL()
{
    /** Initialization **/
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    /** Window **/
    game.win = SDL_CreateWindow(PROJECT_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!game.win)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /** Renderer **/
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    game.rend = SDL_CreateRenderer(game.win, -1, render_flags);
    if (!game.rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(game.win);
        SDL_Quit();
        return 1;
    }

    /** Surface **/
    SDL_Surface* surface = IMG_Load("surface.png");
    if (!surface)
    {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game.rend);
        SDL_DestroyWindow(game.win);
        SDL_Quit();
        return 1;
    }

    /** Texture **/
    SDL_Texture* tex = SDL_CreateTextureFromSurface(game.rend, surface);
    SDL_FreeSurface(surface);
    if (!tex)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(game.rend);
        SDL_DestroyWindow(game.win);
        SDL_Quit();
        return 1;
    }
    return 0;
}



void init()
{
    game.playing = 0;
    srand(time(NULL));

    game.tile_height = WINDOW_HEIGHT / TILESIZE;
    game.tile_width = WINDOW_WIDTH / TILESIZE;

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
    player.text = SDL_CreateTextureFromSurface(game.rend, player.surf);
    player.rect.w = TILESIZE; player.rect.h = TILESIZE;
    player.pos[0] = 0;
    player.pos[1] = 0;
    player.health = 10;
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
    load_map(game.map_001, map_001);

    select_map();
}

void select_map()
{
    int map_selection;

    printf("Select a Map (0: Normal or 1: Random): ");
    scanf("%d", &map_selection);

    switch(map_selection)
    {
    case 0:
        load_map(game.map, game.map_001);
        break;

    case 1:
		generate_map(20, 20, game.map);
		break;

    default:
        printf("Please type a correct number\n");
        select_map();
    }
}

void load_tile(struct image *tile, char directory[])
{
    struct image t_tile;
    t_tile.surf = IMG_Load(directory);
    t_tile.text = SDL_CreateTextureFromSurface(game.rend, t_tile.surf);
    t_tile.rect.w = t_tile.rect.h = TILESIZE;

    *tile = t_tile;
}

void load_map(int map1[20][20], int map2[20][20])
{
    int l; int c;
    for (l=0; l<game.tile_height; l++)
    {
        for (c=0; c<game.tile_width; c++)
        {
            map1[l][c] = map2[l][c];
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
                player.pos[0]--;
                if (!player_collide())
                {
                    player.pos[0]++;
                    printf("You cannot move to the top.\n");
                }
                status();
                break;

            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                player.pos[0]++;
                if (!player_collide())
                {
                    player.pos[0]--;
                    printf("You cannot move to the bot.\n");
                }
                status();
                break;

            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                player.pos[1]--;
                if (!player_collide())
                {
                    player.pos[1]++;
                    printf("You cannot move to the left.\n");
                }
                status();
                break;

            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                player.pos[1]++;
                if (!player_collide())
                {
                    player.pos[1]--;
                    printf("You cannot move to the right.\n");
                }
                status();
                break;
            }
            break;

        }
    }
}

void status()
{
    printf("\n");
    printf("Health: %d\n", player.health);
    printf("Coin(s): %d / 10\n", player.coin);
    printf("Key(s): %d\n", player.key);
    printf("Kill(s): %d\n", player.kill);
    printf("\n");

    win_condition();
}

void win_condition()
{
    if (player.coin >= 10)
    {
        printf("You've win! Game Over!\n");
        draw();
        new_game();
    }

    if (player.health <= 0)
    {
        printf("You've died! Game Over!\n");
        new_game();
    }
}

void new_game()
{
    int input;
    printf("Do you want to play again? Type 0 to continue: ");
    scanf("%d", &input);
    if (input == 0)
    {
        init();
    }
    else
    {
        quit_game();
    }
}

int player_collide()
{
    /* Out of Bounds */
    if (player.pos[0] < 0 || player.pos[0] >= game.tile_height || player.pos[1] < 0 || player.pos[1] >= game.tile_width) return 0;

    int map_tile = game.map[player.pos[0]][player.pos[1]];
    if (map_tile == 0)
    {
        printf("You walked on Grass.\n");
        return 1;
    }

    if (map_tile == 1)
    {
        printf("You walked on a Flower.\n");
        return 1;
    }

    if (map_tile == 2)
    {
        printf("You can't walk through a Tree!\n");
        return 0;
    }

    if (map_tile == 3)
    {
        printf("You can't walk through a Rock!\n");
        return 0;
    }

    if (map_tile == 4)
    {
        game.map[player.pos[0]][player.pos[1]]= 0;
        printf("You found a Key on the ground!\n");
        player.key++;
        return 1;
    }

    if (map_tile == 5)
    {
        game.map[player.pos[0]][player.pos[1]]= 0;
        printf("You found a Coin on the ground!\n");
        player.coin++;
        return 1;
    }

    if (map_tile == 6)
    {
        printf("You found a Lock on your way!\n");
        if (player.key > 0)
        {
            game.map[player.pos[0]][player.pos[1]]= 0;
            printf("You've used a Key to open the Lock!\n");
            player.key--;
            return 1;
        }
        else
        {
            printf("You don't have any Key to open the Lock!\n");
            return 0;
        }
    }

    if (map_tile == 7)
    {
        printf("You stepped on a trap!\nYou lost 1 HP!\n");
        player.health--;
        return 1;
    }

    if (map_tile == 8)
    {
        game.map[player.pos[0]][player.pos[1]]= 0;
        printf("You met a monster on your way!\nYou lost 1 HP by fighting him!\n");
        player.kill++;
        player.health--;
        return 1;
    }
    return 1;
}



/* ------------------------------ */

/* ----- Draw Functions ----- */

/* ------------------------------ */
void draw()
{
    /* Clear the window */
    SDL_RenderClear(game.rend);

    /* Draw texture */
    draw_map();

    /* Render to the window */
    SDL_RenderPresent(game.rend);

    /* FPS */
    SDL_Delay(1000/FPS);
}

void draw_map()
{
    /* Map Tile */
    int l; int c; int t;
    for (l = 0; l < game.tile_height; l++)
    {
        for (c = 0; c < game.tile_width; c++)
        {
            t = game.map[l][c];
            tile[t].rect.y = 32*l;
            tile[t].rect.x = 32*c;
            SDL_RenderCopy(game.rend, tile[t].text, NULL, &tile[t].rect);
        }
    }

    /* Player */
    player.rect.x = 32 * player.pos[1];
    player.rect.y = 32 * player.pos[0];
    SDL_RenderCopy(game.rend, player.text, NULL, &player.rect);
}



/* ------------------------------ */

/* ----- Map Functions ----- */

/* ------------------------------ */
void generate_map(int width, int height, int map[width][height])
{
    int g_flower = 0; int g_tree = 0; int g_rock = 0;
    int g_key = 0; int g_coin = 0; int g_lock = 0;
    int g_trap = 0; int g_monster = 0;
    int *g_pos;

	while (g_flower < 5)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 1;
        g_flower++;
	}

	while (g_tree < 5)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 2;
        g_tree++;
	}

	while (g_rock < 5)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 3;
        g_rock++;
	}

	while (g_key < 1)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 4;
        g_key++;
	}

	while (g_lock < 1)
	{
        generate_treasure(5, 6, 3, width, height, map);
        g_lock++; g_coin++;
	}

	while (g_coin < 10)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 5;
        g_coin++;
	}

	while (g_trap < 5)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 7;
        g_trap++;
	}

	while (g_monster < 10)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 8;
        g_monster++;
	}

    g_pos = generate_position(0, 0, width, height);
    player.pos[0] = *g_pos;
    player.pos[1] = *(g_pos+1);
}

int *generate_position(int min_width, int min_height, int max_width, int max_height)
{
    static int pos[2];

    do{
        do{ pos[0] = rand() % max_width;;
        } while (pos[0] < min_width);

        do{ pos[1] = rand() % max_height;
        } while (pos[1] < min_height);

    } while (game.map[pos[0]][pos[1]] != 0);

    return pos;
}

void generate_treasure(int object_1, int object_2, int object_3, int width, int height, int map[width][height])
{
    /** 1: Treasure / 2: Lock / 3: Obstacle **/

    int i; int j;
    int *g_pos = generate_position(1, 1, width-1, height-1);
    int x = *g_pos; int y = *(g_pos+1);
    int pos[2];

    /* Direction */
    if (abs(x-width/2) > abs(y-height/2))
        {
            if (x > (width)/2)
            {
                pos[0] = x+1; pos[1] = y;
            }
            else
            {
                pos[0] = x-1; pos[1] = y;
            }
        }
        else
        {
            if (y > (height)/2)
            {
                pos[0] = x; pos[1] = y+1;
            }
            else
            {
                pos[0] = x; pos[1] = y-1;
            }
        }

    /* Generate Object */
    map[x][y] = object_2;

    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                map[pos[0]+i][pos[1]+j] = object_1;
            }

            if (abs(i) != abs(j) && map[pos[0]+i][pos[1]+j] != object_2)
            {
                map[pos[0]+i][pos[1]+j] = object_3;
            }
        }
    }
}
