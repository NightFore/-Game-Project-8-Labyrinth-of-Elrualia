#include <stdio.h>
#include <stdlib.h>

/* Settings */
    /* Prototyping */
int PLAYING = 1;
void init();
void events();
void player_movement();
void init_map();
void draw();
void draw_map();
void status();
int player_collide();

    /* Game Settings */
char PROJECT_TITLE[] = "Labyrinth of Elrualia";


    /* Player Settings*/
int PLAYER_HEALTH       = 10;
int PLAYER_COIN         = 0;
int PLAYER_KEY          = 0;


    /* Global Variables */
int player_position[] = {0, 0};


    /* Temporary */
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
    draw_map();
}

void events()
{
    player_movement();
}

void draw()
{
    draw_map();
    status();
}



/* ------------------------------ */

/* ----- Secondary Functions ----- */

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
                printf("%d ", map_001[index_l][index_c]);
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



void status()
{
    printf("Health: %d\n", PLAYER_HEALTH);
    printf("Coin(s): %d / 10\n", PLAYER_COIN);
    printf("Key(s): %d\n", PLAYER_KEY);
    printf("\n");

    if (PLAYER_COIN >= 10)
    {
        printf("You've win! Game Over!\n");
        PLAYING = 0;
    }

    if (PLAYER_HEALTH <= 0)
    {
        printf("You've died! Game Over!\n");
        PLAYING = 0;
    }
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


int player_collide()
{
    /* Out of Bounds */
    if (player_position[0] < 0 || player_position[0] >= 20 || player_position[1] < 0 || player_position[1] >= 20)
    {
        return 0;
    }


    /* 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster */
    int p_p = map_001[player_position[0]][player_position[1]];
    if (p_p == 0)
    {
        printf("You walked on Grass.\n");
        return 1;
    }

    if (p_p == 1)
    {
        printf("You walked on a Flower.\n");
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
        map_001[player_position[0]][player_position[1]]= 0;
        printf("You found a Key on the ground!\n");
        PLAYER_KEY++;
        return 1;
    }

    if (p_p == 5)
    {
        map_001[player_position[0]][player_position[1]]= 0;
        printf("You found a Coin on the ground!\n");
        PLAYER_COIN++;
        return 1;
    }

    if (p_p == 6)
    {
        printf("You found a Lock on your way!\n");
        if (PLAYER_KEY > 0)
        {
            map_001[player_position[0]][player_position[1]]= 0;
            printf("You've used a Key to open the Lock!");
            PLAYER_KEY--;
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
        map_001[player_position[0]][player_position[1]]= 0;
        printf("You stepped on a trap!\nYou lost 1 HP!\n");
        PLAYER_HEALTH--;
        return 1;
    }

    if (p_p == 8)
    {
        map_001[player_position[0]][player_position[1]]= 0;
        printf("You met a monster on your way!\nYou lost 1 HP by fighting him!\n");
        PLAYER_HEALTH--;
        return 1;
    }


}
