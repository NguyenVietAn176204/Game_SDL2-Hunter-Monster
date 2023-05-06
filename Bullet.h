#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "BaseObject.h"
class Bullet:public BaseObject
{
  public:
      Bullet();
      ~Bullet();

      enum TypeBullet{
        RIGHT_TYPE = 20,
        LEFT_TYPE = 21,
      };
       bool LoadImg(std::string path,SDL_Renderer* des);
       void SetAnimation();
       void Show(std::string path,SDL_Renderer* des);
      void SetX(const int &x){x_val = x;}
      void SetY(const int &y){y_val = y;}

      int getX()const{return x_val;}
      int GetY()const{return y_val;}
      void SetMapXY(const int x,const int y){map_X = x;map_Y = y;}
      void SetMove(const bool & check){Move = check;}

      bool GetMove() const {return Move;}

      void HandleMove(const int& x,const int& y);

      void SetType(const unsigned int& Type){type = Type;}//Ben trai hay ben phai ype()const {return type;}

  private:
      SDL_Rect frame_bullet[5];
    int x_val;
    int y_val;
    bool Move;
    int type;
    int map_X;
    int map_Y;
    float width_bullet;
    float height_bullet;
    int frame;
};
#endif
