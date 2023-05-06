#ifndef MAIN_OFJECT_H
#define MAIN_OBJECT_H
#include<vector>
#include "renderWindow.h"
#include "BaseObject.h"
#include "Bullet.h"
#include<bits/stdc++.h>
using namespace std;

#define  GRAVITY_SPEED 10
#define MAX_FALL_SPEED 5
#define MAX_SPEED 4
#define PLAY_SPEED 4
#define PLAYER_JUMP 16
class MainObject : public BaseObject
{
public:
   MainObject();
// ~MainObject();
    enum Walk_type{
    WALK_RIGHT = 0,
    WALK_LEFT = 1,
};
    bool LoadIMG(std::string path,SDL_Renderer* screen);
    void ShowFrame(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events,SDL_Renderer* screen,Mix_Chunk* player[3]);

    void MainAnimation();
    void Player(Map& map_data,Mix_Chunk* p_player[3]);
    void CheckMap(Map& map_data,Mix_Chunk* p_player[3]);

    int get_width_frame(){return width_frame;}
    int get_height_frame(){return height_frame;}
    void SetMapXY(const int map_x,const int map_y){map_x_ = map_x;map_y_ = map_y;};
    void EnTiTyonMap(Map& map_data);
    void Set_list_bullet(std::vector<Bullet*>bullet_list_)
    {
        bullet_list = bullet_list_;
    }

    vector<Bullet*>GetList()const{return bullet_list;}

   void HandleBullet(SDL_Renderer* des);

   void RemoveBullet(int &x);

    float GetX(){return x_pos;}
   float GetY(){return y_pos;}

  void SetCheckMenu(int x) { CheckMenu1 = x;}

private:
    float x_val;//luu vi tri cua anh khi an trai va phai
    float y_val;//luu vi tri cua anh khi an len xuong

    float x_pos;//luu vi tri hien tai cua anh
    float y_pos;

    int width_frame;//kich thuoc cua 1 frame
    int height_frame;

    SDL_Rect frame_clip [PlayerPicture];

    InPutMainObject input_type;
    int frame;
    int status;
    bool on_ground ;

    int CheckSoundJump;
    int map_x_;
    int map_y_;

    int CheckMenu1;
    std::vector<Bullet*>bullet_list;
};

#endif // MAIN_OFJECT_H

