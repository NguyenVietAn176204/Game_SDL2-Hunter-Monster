#include "MainObject.h"
#include "renderWindow.h"
MainObject::MainObject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = -1;
    input_type.left_ = 0;
    input_type.right_ = 0;
    input_type.jump_ = 0;
    input_type.down_ = 0;
    input_type.up_ = 0;
    map_x_ = 0;
    map_y_ = 0;
    on_ground = false;
    input_type.jump_=0;
    CheckSoundJump = 1;

}
bool MainObject::LoadIMG(std::string path,SDL_Renderer* screen)
{
    bool test = BaseObject::LoadIMG(path,screen);
    //Debug
    if(test == true)
    {
        width_frame = rect_.w/4;
        height_frame = rect_.h/4;
    }
}
void MainObject::MainAnimation()
{
for(int i = 0; i < 4;i++)
{
    frame_clip[i].x = i*width_frame;
    frame_clip[i].y = 0;
    frame_clip[i].w = width_frame;
    frame_clip[i].h = height_frame;
}
for(int i = 0; i < 4;i++)
{
    frame_clip[i+4].x = i*width_frame;
    frame_clip[i+4].y = height_frame;
    frame_clip[i+4].w = width_frame;
    frame_clip[i+4].h = height_frame;
}for(int i = 0; i < 4;i++)
{
    frame_clip[i+8].x = i*width_frame;
    frame_clip[i+8].y = 2*height_frame;
    frame_clip[i+8].w = width_frame;
    frame_clip[i+8].h = height_frame;
}for(int i = 0; i < 4;i++)
{
    frame_clip[i+12].x = i*width_frame;
    frame_clip[i+12].y = 3*height_frame;
    frame_clip[i+12].w = width_frame;
    frame_clip[i+12].h = height_frame;
}
}
void MainObject::ShowFrame(SDL_Renderer* des)
{
    if(status == WALK_LEFT)
    {
        LoadIMG("res/GunterLeft.png"  ,des);
    }
    else
    {
        LoadIMG("res/GunterRight.png",des);
    }
    if(input_type.left_ == 1||input_type.right_ == 1)
    {
        frame++;
        if(frame == 16)frame = 0;
    }
    else frame = 0;
    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;
    SDL_Rect* currentclip = &frame_clip[frame];

    SDL_Rect renderQuad = {rect_.x,rect_.y,width_frame,height_frame};

    SDL_RenderCopy(des,p_object_,currentclip,&renderQuad);
}
void MainObject::HandleInputAction(SDL_Event events , SDL_Renderer* screen,Mix_Chunk* player[3])
{
     if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status =WALK_RIGHT;
                input_type.right_=1;
                input_type.left_=0;
            }
            break;
        case SDLK_LEFT:
            {
                status  =WALK_LEFT;
                input_type.left_=1;
                input_type.right_=0;
            }
            break;
        case SDLK_UP:
            {
                input_type.jump_=1;

            }
            break;
        }
    } else if (events.type==SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type.right_=0;

            }
            break;
        case SDLK_LEFT:
            {
                input_type.left_=0;
            }
            break;
        }

    }
    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
                Bullet* bullet = new Bullet;
                bullet->LoadIMG("res/GunMain.png",screen);
                if(status == WALK_LEFT){
                    bullet->SetType(Bullet::LEFT_TYPE);
                    bullet->SetRect(rect_.x,rect_.y +height_frame*0.3);
                    Mix_PlayChannel(-1,player[2],0);
                }
                else
                {
                 bullet->SetType(Bullet::RIGHT_TYPE);
                bullet->SetRect(rect_.x+width_frame-10,rect_.y +height_frame*0.3);
                 Mix_PlayChannel(-1,player[2],0);}
                bullet->SetX(20);
                bullet->SetMove(true);
                bullet_list.push_back(bullet);

        }
    }
    }

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for(int i = 0; i < bullet_list.size();i++)
    {
        Bullet* bullet = bullet_list[i];
        bullet->LoadImg("res/GunMain.png",des);
        bullet->SetAnimation();
        if(bullet != NULL)
       {    float Bullet_Zone = rect_.x  - bullet->GetRect().x;
       if(abs(Bullet_Zone) < 100)
       {

            bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
             Mix_PlayChannel(1,g_sound_gun,0);
            bullet->Show("res/GunMain.png",des);
        }
        else
        {
            bullet_list.erase(bullet_list.begin()+i);
            delete bullet;
            bullet = NULL;
            }

        }
    }
}
    void MainObject::Player(Map& map_data,Mix_Chunk* p_player[3])
       {
if(CheckMenu1 == 0)
{
    x_val = 0;
    y_val += 1.2;
    /** \brief
     *
     * \param 1 input_type.left_ ==
     *
     */
    if(input_type.left_ == 1)
        {
            x_val -= PLAY_SPEED;

        }
        else
        if(input_type.right_ == 1)
        {
            x_val += PLAY_SPEED;
        }
        else
        if(input_type.jump_ == 1)
        { if(on_ground == true)
            {   Mix_PlayChannel(-1,p_player[0],0);
                y_val = - PLAYER_JUMP;
            CheckSoundJump = 1;
            on_ground = false;
            ;}
            input_type.jump_ = 0;
        }
CheckMap(map_data, p_player);
EnTiTyonMap(map_data);
    }
    if(CheckMenu1 > 0)
    {
        CheckMenu1 --;
        if(x_pos > 250)x_pos = x_pos - 250;
        y_pos = 0;
        x_val = 0;
        y_val = 0;
    }
       }
void MainObject::EnTiTyonMap(Map& map_data)
{
    map_data.start_x_ = x_pos - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0)map_data.start_x_ = 0;
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }
   map_data.start_y_ = y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y_  < 0)
    {
        map_data.start_y_ = 0;
    }
    else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}
    void MainObject::CheckMap(Map& map_data,Mix_Chunk* p_player[3])
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

     int height_min;
        if(height_frame <= TILE_SIZE)height_min = height_frame;
        else height_min = TILE_SIZE;
    //checkchieungang
    x1 = (x_pos+ x_val-2)/TILE_SIZE;
    x2 = (x_pos+x_val+width_frame)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 =  (y_pos -1 + height_min)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 &&y2 < MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
            {
                x_pos = (x2)*TILE_SIZE;
                x_pos -= width_frame;
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

   if(width_frame <= TILE_SIZE)width_min = width_frame;
   else width_min = TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos  + width_min-1)/TILE_SIZE;

    y1 =(y_pos  + y_val)/TILE_SIZE;
    y2 =(y_pos + y_val  + height_frame-1)/TILE_SIZE;


        if(y_val > 0)
        {
        if(map_data.tile[y2][x1]!= 0|| map_data.tile[y2][x2] != 0)
        {
            y_pos = y2*TILE_SIZE;
            y_pos = y_pos-(height_frame);// De cho vua voi map
            y_val = 0;
            on_ground = true;
             if(CheckSoundJump == 1)
            {
                Mix_PlayChannel(-1,p_player[1],0);
                CheckSoundJump = 0;
            }
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
      x_pos = map_data.max_x_- width_frame -1;
  }
  if(y_pos > (map_data.max_y_-60))
  {
      SetCheckMenu(40);
  }
}
void MainObject::RemoveBullet(int &x)
{
    int CheckSizeBullet = bullet_list.size();
    if(CheckSizeBullet > 0)
    {
        Bullet* p_bullet = bullet_list.at(x);
    bullet_list.erase(bullet_list.begin()+x);
    delete  p_bullet;
    }
}
