#include"Bullet.h"
#include "BaseObject.h"

Bullet::Bullet()
{
    x_val = 0;
    y_val = 0;
    Move = false;
    frame = 0;
}
Bullet::~Bullet()
{

};
bool Bullet::LoadImg(std::string path,SDL_Renderer* des)
{
    bool test = BaseObject::LoadIMG(path,des);
    //Debug
    if(test == false){std::cout << "Fale MainObject";}
    if(test == true)
    {
        width_bullet = rect_.w/5;
        height_bullet = rect_.h;
    }
}
void Bullet::SetAnimation()
{
    for(int i = 0; i < 5;i++)
{
    frame_bullet[i].x = i*width_bullet;
    frame_bullet[i].y = 0;
    frame_bullet[i].w = width_bullet;
    frame_bullet[i].h = height_bullet;
}
}
void Bullet::Show(std::string path,SDL_Renderer* des)
{
    frame++;
   if(frame >= 5)frame = 0;
    SDL_Rect* Clip = &frame_bullet[frame];
    SDL_Rect RenderQuad = {rect_.x,rect_.y,width_bullet,height_bullet};
    SDL_RenderCopy(des,p_object_,Clip,&RenderQuad);
}
void Bullet::HandleMove(const int& X,const int& Y)//Xu li toa do cua vien dan
{
    if(type == RIGHT_TYPE&&Move == true)
    {
    rect_.x = rect_.x+ x_val;

    if(rect_.x > X)
    {
        Move = false;
    }}
    else
    {
        rect_.x= rect_.x-x_val;
        if(rect_.x <0)
        {
            Move = false;
        }
    }
    //Xu li ban dan theo huong di chuyen
}
