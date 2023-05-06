#include"ThreartPart2.h"

Monster2 :: Monster2()
{
    rect_.x =   0;
    rect_.y =  0;
    rect_.w = 0;
    rect_.h = 0;

    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_monster = 0;
    height_monster = 0;
    Back =0;
}
Monster2::~Monster2()
{

}
bool Monster2::LoadImg(std::string path,SDL_Renderer* des)
{
    bool test = BaseObject::LoadIMG(path,des);
    if(test == true)
    {
        width_monster = rect_.w/6;
        height_monster = rect_.h;
    }
    return test;
}
bool Monster2::LoadImg2(std::string path,SDL_Renderer* des)
{
    bool test = BaseObject::LoadIMG(path,des);
    if(test == true)
    {
        width_monster = rect_.w/10;
        height_monster = rect_.h;
    }
}
bool Monster2::LoadImg3(std::string path,SDL_Renderer* des)
{
    bool test = BaseObject::LoadIMG(path,des);
    if(test == true)
    {
        width_monster = rect_.w/12;
        height_monster = rect_.h;
    }
}
void Monster2::SetAnimation()
{
    for(int i = 0; i < 6;i++)
{
    frame_monster[i].x = i*width_monster;
    frame_monster[i].y = 0;
    frame_monster[i].w = width_monster;
    frame_monster[i].h = height_monster;
}
}
void Monster2::SetAnimation2()
{
    for(int i = 0; i < 10;i++)
{
    frame_monster2[i].x = i*width_monster;
    frame_monster2[i].y = 0;
    frame_monster2[i].w = width_monster;
    frame_monster2[i].h = height_monster;
}
}void Monster2::SetAnimation3()
{
    for(int i = 0; i < 12;i++)
{
    frame_monster3[i].x = i*width_monster;
    frame_monster3[i].y = 0;
    frame_monster3[i].w = width_monster;
    frame_monster3[i].h = height_monster;
}
}
void Monster2::Show(std::string path,SDL_Renderer* des)
{
    if(Back == 0)
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        frame ++;
    }
    if(frame >=6)frame = 0;
    SDL_Rect* Clip = &frame_monster[frame];
    SDL_Rect RenderQuad = {rect_.x,rect_.y,width_monster,height_monster};
    SDL_RenderCopy(des,p_object_,Clip,&RenderQuad);
}
void Monster2::Show2(std::string path,SDL_Renderer* des)
{

     rect_.x = x_pos-map_x;
     rect_.y = y_pos-map_y;
        frame ++;
    if(frame >=10)frame = 0;
    SDL_Rect* Clip = &frame_monster2[frame];
    SDL_Rect RenderQuad = {rect_.x,rect_.y,width_monster,height_monster};
    SDL_RenderCopy(des,p_object_,Clip,&RenderQuad);
}
void Monster2::Show3(std::string path,SDL_Renderer* des)
{
    SDL_Rect* Clip = &frame_monster3[frame];
    std::cout << frame << std::endl;
    SDL_Rect render_Quad = {rect_.x,rect_.y,width_monster,height_monster};
    render_Quad.w = Clip->w;
    render_Quad.h = Clip->h;
    std::cout << p_object_;
    SDL_RenderCopy(des,p_object_,Clip,&render_Quad);
}
void Monster2::DoPlayer(Map& gMap)
{
    if(Back == 0)
    {
        x_val = 0;
        y_val +=1.2;
        CheckToMap(gMap);
    }
    if(Back > 0)
    {
        Back --;
        if(Back == 0)
        {
            x_val = 0;
            y_val = 0;
            if(x_pos > 256)
            {
              x_pos -= 256;
            }
            else x_pos = 0;
        }
        y_pos = 0;
    }
    Back = 0;
}
//void Monster2::GetBattle()
//{
//
//}
void Monster2::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

     int height_min;
        if(height_monster <= TILE_SIZE)height_min = height_monster;
        else height_min = TILE_SIZE;
    //checkchieungang
    x1 = (x_pos+ x_val-2)/TILE_SIZE;
    x2 = (x_pos+x_val+width_monster)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 =  (y_pos -1 + height_min)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 &&y2 < MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
            {
                x_pos = (x2)*TILE_SIZE;
                x_pos -= width_monster;
                x_val = 0;
            }
        }
        else if(x_val < 0)
        {
            if(map_data.tile[y1][x1] != 0 && map_data.tile[y2][x1] != 0)
            {
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }


    //ktra di chuyen len
    int width_min;

   if(width_monster <= TILE_SIZE)width_min = width_monster;else width_min = TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos  + width_min-1)/TILE_SIZE;

    y1 =(y_pos  + y_val)/TILE_SIZE;
    y2 =(y_pos + y_val  + height_monster-1)/TILE_SIZE;


        if(y_val > 0)
        {
        if(map_data.tile[y2][x1]!= 0|| map_data.tile[y2][x2] != 0)
        {
            y_pos = y2*TILE_SIZE;
            y_pos = y_pos-(height_monster);// De cho vua voi map
            y_val = 0;
            on_ground = true;
        }
        else on_ground = false;
    }
    else if(y_val < 0)
    {
        if(map_data.tile[y1][x1] != 0|| map_data.tile[y1][x2]!=0)
        {
            y_pos = (y1+1)*TILE_SIZE;//cong 1 de la vi tri o ben duoi anh
            y_val = 0;//roi tu do
        }
    }
     x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
 if(x_pos  > map_data.max_x_)
  {
      x_pos = map_data.max_x_- width_monster -1;
  }
}
void Monster2::BotGameVip(float player_x, float player_y)
{

        float c=sqrt((player_x-x_pos)*(player_x-x_pos)+(player_y-y_pos)*(player_y-y_pos));
             float a = (player_y- y_pos)/(player_x- x_pos);
             float b = (player_y-a*player_x);

           if (x_pos < player_x)
               {
                    float l=0,r=THREATS_SPEED;
                    float m=0,res = 0,kc=0;
                    while (fabs(r-l)>0.0001)
                    {
                        m=(l+r)/2;
                        res=a*(x_pos+m)+b;
                        kc=sqrt(m*m+(res-y_pos)*(res-y_pos));
                        if (kc<THREATS_SPEED) l=m;
                          else if (kc>THREATS_SPEED) r=m; else
                        {
                            break;
                        }
                    }
                    x_pos+=m;
                    y_pos=a*(x_pos)+b;
               } else
               {
                   float l=-THREATS_SPEED;
                    float m=0,res=0,kc=0,r=0;
                    while (fabs(r-l)>0.0001)
                    {
                        m=(l+r)/2;
                        res=a*(x_pos+m)+b;
                        kc=sqrt(m*m+(res-y_pos)*(res-y_pos));
                        if (kc<THREATS_SPEED) r=m;
                          else if (kc>THREATS_SPEED) l=m; else
                        {
                            break;
                        }
                    }
                    x_pos+=m;
                    y_pos=a*(x_pos)+b;

               }
        }
void Monster2::InitBullet(Bullet* p_bullet,SDL_Renderer* screen)
{

    bool ret = p_bullet->LoadIMG("res/Gunn.png",screen);
    p_bullet->SetType(Bullet::LEFT_TYPE);
    p_bullet->SetRect(rect_.x,rect_.y);

    p_bullet->SetX(7);
    p_bullet->SetMove(true);
    Bullet_list.push_back(p_bullet);

}
void Monster2::Make_Bullet(SDL_Renderer* screen,const int& X,const int& Y)
{
    for(int i = 0; i < Bullet_list.size();i++)
    {
        Bullet* BulletCheck = Bullet_list.at(i);
   if(BulletCheck != NULL)
   {   if(BulletCheck->GetMove())
   {     float Bullet_Zone = rect_.x  - BulletCheck->GetRect().x;
         if(Bullet_Zone < 75)
         {
        BulletCheck->HandleMove(X,Y);
        BulletCheck->Render(screen);
         }

      else {BulletCheck->SetMove(true);
    BulletCheck->SetRect(rect_.x,rect_.y);}}
   }
    }

}

