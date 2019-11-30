#include <stdio.h>
#include <stdlib.h>

/* Settings */
    /* Game Settings */
char PROJECT_TITLE[] = "Labyrinth of Elrualia";
int WIDTH = 800; int HEIGHT = 600;
int FPS = 60;
int TILESIZE = 32;
int GRIDWIDTH;
int GRIDHEIGHT;


    /* Player Settings*/
char PLAYER_IMG[] = "character_pipoya_male_01_2.png";
int PLAYER_INDEX = 1;
int PLAYER_HIT_RECT[] = {0, 0, 35, 35};
int PLAYER_HEALTH = 3;
int PLAYER_SPEED = 300;


    /* Mob Settings */
char MOB_IMG[] = "Mobs_enemy_04_1.png";
int MOB_HIT_RECT[] = {0, 0, 30, 30};
int MOB_HEALTH = 2;
int MOB_SPEED = 125;
int MOB_DAMAGE = 1;
int MOB_KNOCKBACK = 20;
int MOB_RADIUS = 30;
int MOB_DETECT_RADIUS = 300;


    /* Sword Settings */
char SWORD_IMG[] = "Sword_PixelHole_x2.png";
int SWORD_HIT_RECT[] = {0, 0, 30, 30};
int SWORD_SPEED = 50;
int SWORD_DAMAGE = 1;
int SWORD_KNOCKBACK = 20;
int SWORD_LIFETIME = 300;
int SWORD_RATE = 500;
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
char BG_MUSIC[] = "music_aaron_krogh_310_world_map.mp3";
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








void init()
{
    GRIDWIDTH = WIDTH/TILESIZE; GRIDHEIGHT = HEIGHT / TILESIZE;

    printf("%s\n", PROJECT_TITLE);
    printf("%d\n", GRIDWIDTH);
}



int main()
{
    init();
    printf("Project Title: %s\n", PROJECT_TITLE);
    printf("%d %d\n", WIDTH, HEIGHT);
    printf("%d\n", TILESIZE);
    printf("%d\n", GRIDWIDTH);
    printf("%d\n", C_INTERFACE[0]);
}

