#include "Threartttt.h"

Monster :: Monster()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y =  SCREEN_HEIGHT/2;
    rect_.w = 32;
    rect_.h = 32;

    x_val = 0;
    y_val = 0;
    width_monster = 0;
    height_monster = 0;
}
bool Monster::LoadImg(std::string path,SDL_Renderer* des)
{
    BaseObject::LoadIMG(path,des);
    width_monster = rect_.w/8;
    height_monster = rect_.h;
}
void Monster::SetAnimation()
{
for(int i = 0; i < 8;i++)
{
    frame_monster[i].x = i*width_monster;
    frame_monster[i].y = 0;
    frame_monster[i].w = width_monster;
    frame_monster[i].h = height_monster;
}
}
void Monster::handleMove(const int& x,const int& y)
{
    srand((int)time(0));
    rect_.x -= x_val;
    if(rect_.x < 0)
    {rect_.x = x;
     int rand_y = (rand()%10+1)*50;
    if(rand_y > SCREEN_HEIGHT){rand_y =rand_y -SCREEN_HEIGHT*0.3;}
    rect_.y = rand_y;}
}
void Monster::ShowMonster(SDL_Renderer* des)
{
     frame++;
    if(frame>=8)frame = 0;
    SDL_Rect* clip = &frame_monster[frame];
    SDL_Rect rendQuad = {rect_.x,rect_.y,width_monster,height_monster};
    SDL_RenderCopy(des,p_object_,clip,&rendQuad);
}





