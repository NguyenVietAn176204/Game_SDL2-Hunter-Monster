#ifndef THREAT_MONSTER2_H
#define THREAT_MONSTER2_H
#include "BaseObject.h"
#include"Bullet.h"
#define MONSTER_AMT 8
#define THREATS_SPEED 2.5
class Monster2 : public BaseObject
{
 public:
 Monster2();
 ~Monster2();

 void  set_xval(const int& val){x_val = val;};
 void set_yval(const int& val){y_val = val;};

 int get_x_val() const {return x_val;};
 int get_y_val()const {return y_val;};
 bool LoadImg(std::string path,SDL_Renderer* des);//Load tam anh
 bool LoadImg2(std::string path,SDL_Renderer* des);//Load tam anh
 bool LoadImg3(std::string path,SDL_Renderer* des);
 void SetX(const float& x){x_pos = x;}
 void SetY(const float& y){y_pos = y;}
 float GetX()const {return x_pos;}
 float GetY()const {return y_pos;}
 void SetMapXY(const int x,const int y){map_x = x;map_y = y;}//Lay Du lieu Map cho
 void SetAnimation();//Load frame
 void SetAnimation2();
 void SetAnimation3();
 void Show(std::string path,SDL_Renderer* des);//show frame ra man hinh
 void Show2(std::string path,SDL_Renderer* des);//show frame ra man hinh
 void Show3(std::string path,SDL_Renderer* des);
 int get_width_frame()const {return width_monster;}//Lay chieu dai
 int get_height_frame()const {return height_monster;}//Lay chieu rong
 void DoPlayer(Map&gMap);
 void BotGameVip(float main_x, float main_y);//Duoi theo nhan vatt
 void CheckToMap(Map&map_data);//Check va cham cua Bot va ban do
 std::vector<Bullet*>GetBullet()const {return Bullet_list;}//Lay danh sach dan
 void SetBullet(std::vector<Bullet*>X){Bullet_list = X;}//Set dan cho sung

 void InitBullet(Bullet* p_bullet,SDL_Renderer* screen);
 void Make_Bullet(SDL_Renderer* screen,const int& X,const int& Y);

 void Setframe(int x){frame = x;};

private :
    SDL_Rect frame_monster[6];
    SDL_Rect frame_monster2[10];
    SDL_Rect frame_monster3[12];
    int width_monster;
    int height_monster;
    int x_val;
    int y_val;
    bool on_ground;
    float x_pos;
    float y_pos;
    int map_x;
    int map_y;
    int frame;

    int Back;
    std::vector<Bullet*>Bullet_list;

};
#endif // THREAT_OBJECT_H

