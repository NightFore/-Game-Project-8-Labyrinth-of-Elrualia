#include <stdio.h>
#include <stdlib.h>

/* Settings */
    /* Prototyping */
int PLAYING = 1;
void init();
void init_new();
void run();
void events();
void player_movement();
void init_map();
void draw();
void draw_map();
void player_status();
int player_collide();

    /* Game Settings */
char PROJECT_TITLE[] = "Labyrinth of Elrualia";
int WIDTH = 800; int HEIGHT = 600;
int FPS = 60;
int TILESIZE = 32;
int GRIDWIDTH;
int GRIDHEIGHT;


    /* Player Settings*/
char PLAYER_IMG[]       = "character_pipoya_male_01_2.png";
int PLAYER_INDEX        = 1;
int PLAYER_HIT_RECT[]   = {0, 0, 35, 35};
int PLAYER_HEALTH       = 3;
int PLAYER_SPEED        = 300;
int PLAYER_COIN         = 0;
int PLAYER_KEY          = 0;



    /* Mob Settings */
char MOB_IMG[]          = "Mobs_enemy_04_1.png";
int MOB_HIT_RECT[]      = {0, 0, 30, 30};
int MOB_HEALTH          = 2;
int MOB_SPEED           = 125;
int MOB_DAMAGE          = 1;
int MOB_KNOCKBACK       = 20;
int MOB_RADIUS          = 30;
int MOB_DETECT_RADIUS   = 300;


    /* Sword Settings */
char SWORD_IMG[]        = "Sword_PixelHole_x2.png";
int SWORD_HIT_RECT[]    = {0, 0, 30, 30};
int SWORD_SPEED         = 50;
int SWORD_DAMAGE        = 1;
int SWORD_KNOCKBACK     = 20;
int SWORD_LIFETIME      = 300;
int SWORD_RATE          = 500;
/* int SWORD_OFFSET[] = vec(20, 0); */


    /* Tweening */
int BOB_RANGE = 10;
int BOB_SPEED = 0.3;


    /* Layer Settings */
int LAYER_WALL      = 1;
int LAYER_ITEMS     = 1;
int LAYER_PLAYER    = 2;
int LAYER_MOB       = 2;
int LAYER_SWORD     = 3;
int LAYER_EFFECTS   = 4;


    /* Item Directories */
/* ITEM_IMAGES[] = {"heart": ["items_beyonderboy_heart_1.png"], "coin": ["items_beyonderboy_coin_1.png", "items_beyonderboy_coin_2.png", "items_beyonderboy_coin_3.png", "items_beyonderboy_coin_4.png", "items_beyonderboy_coin_5.png", "items_beyonderboy_coin_6.png"]}*/
char ITEM_DROPS[][100] = { {"heart"}, {"coin"} };
char IMAGE_HEART[]  = "items_beyonderboy_heart.png";
char IMAGE_COIN[]   = "items_beyonderboy_coin.png";


    /* Item Settings */
int HEART_AMOUNT = 1;
int COIN_AMOUNT = 1;


    /* Effect Settings*/
/* EFFECT_IMAGES   = {"pick_up": ["effect_beyonderboy_pick_up_item_1.png", "effect_beyonderboy_pick_up_item_2.png", "effect_beyonderboy_pick_up_item_3.png", "effect_beyonderboy_pick_up_item_4.png", "effect_beyonderboy_pick_up_item_5.png", "effect_beyonderboy_pick_up_item_6.png"]} */


    /* Sound Directories */
char BG_MUSIC[]                 = "music_aaron_krogh_310_world_map.mp3";
char SOUNDS_PICK_UP[]           = "sfx_maoudamashii_system23.wav";
char SOUNDS_SWORD_ATTACK[][100] = {"Battle_Slash_battle01.wav", "Battle_Slash_battle03.wav", "Battle_Slash_battle17.wav"};
char VOICE_PLAYER_ATTACK[][100] = {"voice_wingless_seraph_jakigan_07_attack.wav", "voice_wingless_seraph_jakigan_08_attack.wav"};
char VOICE_PLAYER_DAMAGE[][100] = {"voice_wingless_seraph_jakigan_14_damage.wav", "voice_wingless_seraph_jakigan_15_damage.wav", "voice_wingless_seraph_jakigan_16_damage.wav"};


    /* Colors */
int RED[]           = {255, 0,   0};
int C_GREEN[]       = {0,   255, 0};
int C_DARKGREEN[]   = {60,  210, 120};
int C_BLUE[]        = {0,   0,   255};
int C_LIGHTBLUE[]   = {140, 205, 245};
int C_YELLOW[]      = {255, 255, 0};
int C_CYAN[]        = {0,  255,  255};
int C_GREY[]        = {150, 170, 210};
int C_LIGHTGREY[]   = {100, 100, 100};
int C_BLACK[]       = {0,   0,   0};
int C_WHITE[]       = {255, 255, 255};
int C_BGCOLOR[]     = {200, 200, 200};
int C_INTERFACE[]   = {140, 205, 245};


    /* Global Variables */
int player_position[] = {10, 3};


    /* Temporary */
int map_1[20][20] =
    {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 5},
    {0, 1, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
    init_new();
    run();
}

void init()
{
    draw_map();

    GRIDWIDTH   = WIDTH/TILESIZE;
    GRIDHEIGHT  = HEIGHT / TILESIZE;
}

void init_new()
{

}

void run()
{
    while (PLAYING==1)
    {
        events();
        draw();
    }
}

void events()
{
    player_movement();
}


void draw()
{
    draw_map();
    player_status();
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
                printf("%d ", map_1[index_l][index_c]);
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



void player_status()
{
    printf("Health: %d\n", PLAYER_HEALTH);
    printf("Coin(s): %d\n", PLAYER_COIN);
    printf("Key(s): %d\n", PLAYER_KEY);
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


int player_collide()
{
    /* Out of Bounds */
    if (player_position[0] < 0 || player_position[0] >= 20 || player_position[1] < 0 || player_position[1] >= 20)
    {
        return 0;
    }


    /* 0: Grass | 1: Flower | 2: Tree | 3: Rock | 4: Key | 5: Coin | 6: Lock | 7: Trap | 8: Monster */
    int p_p = map_1[player_position[0]][player_position[1]];
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
        map_1[player_position[0]][player_position[1]]= 0;
        printf("You found a Key on the ground!\n");
        PLAYER_KEY++;
        return 1;
    }

    if (p_p == 5)
    {
        map_1[player_position[0]][player_position[1]]= 0;
        printf("You found a Coin on the ground!\n");
        PLAYER_COIN++;
        return 1;
    }

    if (p_p == 6)
    {
        printf("You found a Lock on your way!\n");
        if (PLAYER_KEY > 0)
        {
            map_1[player_position[0]][player_position[1]]= 0;
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
        map_1[player_position[0]][player_position[1]]= 0;
        printf("You stepped on a trap!\nYou lost 1 HP!\n");
        PLAYER_HEALTH--;
        return 1;
    }

    if (p_p == 8)
    {
        map_1[player_position[0]][player_position[1]]= 0;
        printf("You met a monster on your way!\nYou lost 1 HP by fighting him!\n");
        PLAYER_HEALTH--;
        return 1;
    }


}
