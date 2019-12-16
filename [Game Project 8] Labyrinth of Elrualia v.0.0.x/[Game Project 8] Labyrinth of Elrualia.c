#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char PROJECT_TITLE[] = "Labyrinth of Elrualia";

/** 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster **/



/* ------------------------------ */

/* ----- Struct ----- */

/* ------------------------------ */
struct
{
    int playing;

    int map[20][20];
    int map_001[20][20];
} game;

struct
{
    int pos[2];
    int health;
    int coin;
    int key;
    int kill;
} player;



/* ------------------------------ */

/* ----- Prototyping ----- */

/* ------------------------------ */
void init();
void select_map();
void load_map();

void draw();
void draw_map();

void events();
void player_movement();
int player_collide();
void status();
void win_condition();
void new_game();

void generate_map(int width, int height, int map[width][height]);
int *generate_position(int min_width, int min_height, int max_width, int max_height);
void generate_treasure(int object_1, int object_2, int object_3, int width, int height, int map[width][height]);



/* ------------------------------ */

/* ----- Main Functions ----- */

/* ------------------------------ */
int main()
{
    init();
    while (!game.playing)
    {
        events();
        draw();
    }
}


/* ------------------------------ */

/* ----- Initialization Functions ----- */

/* ------------------------------ */
void init()
{
    game.playing = 0;
    srand(time(NULL));

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
    int l; int c;
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
    draw();
}

void load_map(int map1[20][20], int map2[20][20])
{
    int l; int c;
    for (l=0; l<20; l++)
    {
        for (c=0; c<20; c++)
        {
            map1[l][c] = map2[l][c];
        }
    }
}



/* ------------------------------ */

/* ----- Draw Functions ----- */

/* ------------------------------ */
void draw()
{
    draw_map();
    status();
}

void draw_map()
{
    int index_l; int index_c;
    for (index_l=0; index_l<20; index_l++)
    {
        for (index_c=0; index_c<20; index_c++)
        {
            if (index_l != player.pos[0] || index_c != player.pos[1])
            {
                printf("%d ", game.map[index_l][index_c]);
            }
            else
            {
                printf("X ");
            }
        }
        printf("\n");
    }
}



/* ------------------------------ */

/* ----- Events Functions ----- */

/* ------------------------------ */
void events()
{
    player_movement();
}

void player_movement()
{
    int movement;
    printf("Enter a movement command [2/4/6/8] = [Down/Left/Right/Up]: ");
    scanf("%d", &movement);
    switch (movement)
    {
        /* Left */
        case 4:
            player.pos[1]--;
            if (player_collide() == 0)
            {
                player.pos[1]++;
                printf("You cannot move to the left.\n");
            }
            break;

        /* Right */
        case 6:
            player.pos[1]++;
            if (player_collide() == 0)
            {
                player.pos[1]--;
                printf("You cannot move to the right.\n");
            }
            break;

        /* Bot */
        case 2:
            player.pos[0]++;
            if (player_collide() == 0)
            {
                player.pos[0]--;
                printf("You cannot move to the bot.\n");
            }
            break;

        /* Top */
        case 8:
            player.pos[0]--;
            if (player_collide() == 0)
            {
                player.pos[0]++;
                printf("You cannot move to the top.\n");
            }
            break;

        case 0:
            printf("Shutting down the game...\n");
            game.playing = !game.playing;
            break;

        default:
            printf("Invalid move command...\n");
    }
    printf("\n");
}

int player_collide()
{
    /* Out of Bounds */
    if (player.pos[0] < 0 || player.pos[0] >= 20 || player.pos[1] < 0 || player.pos[1] >= 20) return 0;

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
        game.playing = !game.playing;
    }
}


/* ------------------------------ */

/* ----- Map Functions ----- */

/* ------------------------------ */
void generate_map(int width, int height, int map[width][height])
{
    int g_player[2];
    int g_flower = 0; int g_tree = 0; int g_rock = 0;
    int g_key = 0; int g_coin = 0; int g_lock = 0;
    int g_trap = 0; int g_monster = 0;
    int *g_pos;
    int pos[2];

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
