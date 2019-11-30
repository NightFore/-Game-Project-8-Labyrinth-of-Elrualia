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
int LAYER_WALL = 1;
int LAYER_ITEMS = 1;
int LAYER_PLAYER = 2;
int LAYER_MOB = 2;
int LAYER_SWORD = 3;
int LAYER_EFFECTS = 4;



void init()
{
    GRIDWIDTH = WIDTH/TILESIZE; GRIDHEIGHT = HEIGHT / TILESIZE;

    printf("%s\n", PROJECT_TITLE);
    printf("%d\n", GRIDWIDTH);
}



int main()
{
    init();
    printf("Test: %d\n", test);
    printf("Project Title: %s\n", PROJECT_TITLE);
    printf("%d %d\n", WIDTH, HEIGHT);
    printf("%d\n", TILESIZE);
    printf("%d\n", GRIDWIDTH);
}

