#ifndef RENDER_WINDOW_H_
#define RENDER_WINDOW_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "BaseObject.h"

static SDL_Window* g_Window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Surface* MainMenu;
static Mix_Chunk* g_menu_sound;
static Mix_Chunk* g_sound_gun = NULL;
static Mix_Chunk* player_sound[3];
static Mix_Chunk* g_sound_boom = NULL;
//screen
const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 448;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAWN_COLOR = 0xff;

const int NUM_THREAT = 2;


#define BLANK_TILE 0
#define TILE_SIZE 32
#define MAX_MAP_X 512
#define MAX_MAP_Y 14
#define PlayerPicture 16
typedef struct InPutMainObject
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int jump_1;
    int jump_2;
    int jump_3;
};

 struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name_;
};
namespace CommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int CreateMainMenu(SDL_Renderer* des,TTF_Font* font);
   int CreateMainMenuPause(SDL_Renderer* des,TTF_Font* font);
    bool CheckMenu(int& x,int& y,const SDL_Rect& rect);
}
#endif // COMMONFUNC_H_INCLUDED
