#ifndef THREAT_MONSTER_H
#define THREAT_MONSTER_H
#include "BaseObject.h"

#define MONSTER_AMT 8
class Monster : public BaseObject
{
 public:
 Monster();
// ~Monster();

 void handleMove(const int& x,const int& y);
 void ShowMonster(SDL_Renderer* des);
 void  set_xval(const int& val){x_val = val;};
 void set_yval(const int& val){y_val = val;};

 int get_x_val() const {return x_val;};
 int get_y_val()const {return y_val;};
 void SetAnimation();
 bool LoadImg(std::string path,SDL_Renderer* des);//Load tam anh
 void Show1(std::string path,SDL_Renderer* des);//show frame ra man hinh
 int get_width_frame(){return width_monster;}
int get_height_frame(){return height_monster;}
private :
    SDL_Rect frame_monster[8];
    int width_monster;
    int height_monster;
    int x_val;
    int y_val;
    int frame;

};
#endif // THREAT_OBJECT_H
