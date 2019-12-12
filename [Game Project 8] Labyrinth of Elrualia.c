#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Settings */
    /* Prototyping */
int PLAYING = 1;
void init();
void events();
void draw();

void select_map();
void load_map(int map[20][20]);

void draw_map();
void status();

void player_movement();
void win_condition();

int player_collide();
void border_map(int width, int height, int map[width][height]);

void generate_map(int width, int height, int map[width][height]);
int *generate_position(int min_width, int min_height, int max_width, int max_height);
void generate_treasure(int object_1, int object_2, int object_3, int width, int height, int map[width][height]);

/* 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster */
    /* Game Settings */
char PROJECT_TITLE[] = "Labyrinth of Elrualia";
int MAP_WIDTH = 20;
int MAP_HEIGHT = 20;

    /* Global Variables */
int player_position[] = {0, 0};
int player_health       = 10;
int count_grass = 0;
int count_flower = 0;
int count_coin = 0;
int count_key = 0;
int count_kill = 0;

    /* Temporary */
int main_map[20][20];

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

int map_002[20][20];
int map_003[20][20];


/* ------------------------------ */

/* ----- Main Functions ----- */

/* ------------------------------ */
int main()
{
    init();
    while (PLAYING==1)
    {
        events();
        draw();
    }
}

void init()
{
    srand(time(NULL));
    select_map();
    draw_map();
}

void events()
{
    player_movement();
    win_condition();
}

void draw()
{
    draw_map();
    status();
}


/* ------------------------------ */

/* ----- Initialization Functions ----- */

/* ------------------------------ */
void select_map()
{
    int l; int c;
    int map_selection;

    printf("Select a Map (1/2/3 or 4: Random): ");
    scanf("%d", &map_selection);

    switch(map_selection)
    {
    case 1:
        load_map(map_001);
        break;

    case 2:
        load_map(map_002);
        border_map(MAP_WIDTH, MAP_HEIGHT, main_map);
        break;

    case 3:
        load_map(map_003);
        break;

	case 4:
		generate_map(20, 20, main_map);
		load_map(main_map);
		break;

    default:
        printf("Please select a correct map\n");
        select_map();
    }
}

void load_map(int map[20][20])
{
    int l; int c;
    for (l=0; l<20; l++)
    {
        for (c=0; c<20; c++)
        {
            main_map[l][c] = map[l][c];
        }
    }
    printf("\n");
}



/* ------------------------------ */

/* ----- Draw Functions ----- */

/* ------------------------------ */
void draw_map()
{
    int index_l; int index_c;
    for (index_l=0; index_l<20; index_l++)
    {
        for (index_c=0; index_c<20; index_c++)
        {
            if (index_l != player_position[0] || index_c != player_position[1])
            {
                printf("%d ", main_map[index_l][index_c]);
            }
            else
            {
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("\n");
}



/* ------------------------------ */

/* ----- Events Functions ----- */

/* ------------------------------ */
void status()
{
    printf("Health: %d\n", player_health);
    printf("Coin(s): %d / 10\n", count_coin);
    printf("Key(s): %d\n", count_key);
    printf("\n");

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
            player_position[1]--;
            if (player_collide() == 0)
            {
                player_position[1]++;
                printf("You cannot move to the left.\n");
            }
            break;

        /* Right */
        case 6:
            player_position[1]++;
            if (player_collide() == 0)
            {
                player_position[1]--;
                printf("You cannot move to the right.\n");
            }
            break;

        /* Bot */
        case 2:
            player_position[0]++;
            if (player_collide() == 0)
            {
                player_position[0]--;
                printf("You cannot move to the bot.\n");
            }
            break;

        /* Top */
        case 8:
            player_position[0]--;
            if (player_collide() == 0)
            {
                player_position[0]++;
                printf("You cannot move to the top.\n");
            }
            break;

        case 0:
            printf("Shutting down the game...\n");
            PLAYING = 0;
            break;

        default:
            printf("Invalid move command...\n");
    }
    printf("\n");
}

void win_condition()
{
    if (count_coin >= 10)
    {
        printf("You've win! Game Over!\n");
        PLAYING = 0;
    }

    if (player_health <= 0)
    {
        printf("You've died! Game Over!\n");
        PLAYING = 0;
    }
}



/* ------------------------------ */

/* ----- Gameplay Functions ----- */

/* ------------------------------ */
int player_collide()
{
    /* Out of Bounds */
    if (player_position[0] < 0 || player_position[0] >= 20 || player_position[1] < 0 || player_position[1] >= 20)
    {
        return 0;
    }

    /* 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster */
    int p_p = main_map[player_position[0]][player_position[1]];
    if (p_p == 0)
    {
        printf("You walked on Grass.\n");
	count_grass++;
        return 1;
    }

    if (p_p == 1)
    {
        printf("You walked on a Flower.\n");
	count_flower++;
        return 1;
    }

    if (p_p == 2)
    {
        printf("You can't walk through a Tree!\n");
        return 0;
    }

    if (p_p == 3)
    {
        printf("You can't walk through a Rock!\n");
        return 0;
    }

    if (p_p == 4)
    {
        main_map[player_position[0]][player_position[1]]= 0;
        printf("You found a Key on the ground!\n");
        count_key++;
        return 1;
    }

    if (p_p == 5)
    {
        main_map[player_position[0]][player_position[1]]= 0;
        printf("You found a Coin on the ground!\n");
        count_coin++;
        return 1;
    }

    if (p_p == 6)
    {
        printf("You found a Lock on your way!\n");
        if (count_key > 0)
        {
            main_map[player_position[0]][player_position[1]]= 0;
            printf("You've used a Key to open the Lock!");
            count_key--;
            return 1;
        }
        else
        {
            printf("You don't have any Key to open the Lock!\n");
            return 0;
        }
    }

    if (p_p == 7)
    {
        main_map[player_position[0]][player_position[1]]= 0;
        printf("You stepped on a trap!\nYou lost 1 HP!\n");
        player_health--;
        return 1;
    }

    if (p_p == 8)
    {
        main_map[player_position[0]][player_position[1]]= 0;
        printf("You met a monster on your way!\nYou lost 1 HP by fighting him!\n");
        player_health--;
        return 1;
    }
}



void border_map(int width, int height, int map[width][height])
{
	int l; int c;

	for (l=0; l<height; l++)
	{
		for (c=0; c<width; c++)
		{
			if ((l%height==0) || (c%width==0) || (l==height-1) || (c==width-1))
			{
				map[l][c] = 2;
			}
		}
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

    g_pos = generate_position(0, 0, width, height);
    player_position[0] = *g_pos;
    player_position[1] = *(g_pos+1);

	while (g_flower < 2)
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
        generate_treasure(5, 6, 2, width, height, map);
        g_lock++; g_coin++;
	}

	while (g_coin < 10)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 5;
        g_coin++;
	}

	while (g_trap < 10)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 7;
        g_trap++;
	}

	while (g_monster < 5)
	{
        g_pos = generate_position(0, 0, width, height);
        map[*g_pos][*(g_pos+1)] = 8;
        g_monster++;
	}
}

int *generate_position(int min_width, int min_height, int max_width, int max_height)
{
    static int pos[2];

    do{
        do{ pos[0] = rand() % max_width;;
        } while (pos[0] < min_width);

        do{ pos[1] = rand() % max_height;
        } while (pos[1] < min_height);

    } while (main_map[pos[0]][pos[1]] != 0);

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
