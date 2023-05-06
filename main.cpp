#include<SDL.h>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include<stdio.h>
#include"BaseObject.h"
#include"Game_map.h"
#include"MainObject.h"
#include"Timer.h"
#include"Threartttt.h"
#include"Bullet.h"
#include"ThreartPart2.h"
#include"Menu.h"
using namespace std;
BaseObject g_Background;
TTF_Font* g_font;
bool InIt()
{
    bool suscess = true;
    if(SDL_INIT_EVERYTHING < 0||SDL_INIT_AUDIO < 0||SDL_INIT_VIDEO<0)
    {   cout <<"INIT IS FALSED";
        return false;
    }

//   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    g_Window = SDL_CreateWindow("GAMEe",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(g_Window == NULL)
    {   cout <<"Create Window IS FALED";
        suscess = false;
    }
    else {
        g_screen = SDL_CreateRenderer(g_Window,-1,SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);
         }
    if(g_screen == NULL)
    {
        suscess = false;cout << "Create Renderer FALED";
    }
    if(TTF_Init()== -1)
    {
        return false;
    }
    g_font = TTF_OpenFont("GameFont.ttf",25);
    if(g_font == NULL)
    {
        std::cout << "Load Fort failed;";
        return false;
    }
    int imgFlags = IMG_INIT_PNG;
  if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					suscess = false;
				}

				 //Initialize SDL_mixer

				if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0)
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					suscess = false;
				}

     g_sound_gun = Mix_LoadWAV("sfx/Gun.wav");
     player_sound[0] =  Mix_LoadWAV("sfx/sfx_movement_jump1.wav");
      player_sound[1] = Mix_LoadWAV("sfx/sfx_sounds_impact1 (landing).wav");
       player_sound[2] = Mix_LoadWAV("sfx/Gun.wav");
    g_menu_sound = Mix_LoadWAV("sfx/medieval-folk-loop-instrumental-flute-guitar-piano-148606.wav");

     if(g_sound_gun == NULL)
     {
         std::cout << "Load Sound Gun Failed";
     }
     return suscess;
}


bool LoadBackground()
    {
        bool ret = g_Background.LoadIMG("res/bachgroundgame.png",g_screen);
        if(ret == false){cout <<" ";return false;}
        else return true;
    }
void close()
{
    g_Background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_Window);
    g_Window = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
std::vector<Monster2*>MonsterList()
{
    std::vector<Monster2*>list_monster;
    Monster2* p_monster2 = new Monster2[30];
    for(int i = 0 ; i < 30;i++)
    {
            Monster2* p_monster2_ = (p_monster2+i);
            p_monster2_->LoadImg( "res/MonsterLeft.png" , g_screen);
            p_monster2_->SetAnimation();
            p_monster2_->SetX(200+i*400);
            p_monster2_->SetY(50);
            list_monster.push_back(p_monster2_);
            Bullet* BulletGun = new Bullet();
            p_monster2_->InitBullet(BulletGun,g_screen);
    }
    return list_monster;
}
int main(int argc,char* argv[])
    {

    Timer FPS;
    if(InIt() == false){std::cout<<"false";}
    if(LoadBackground() == false){std::cout<<"False";}


    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);


    MainObject p_player;
    p_player.LoadIMG("res/GunterLeft.png",g_screen);
    p_player.MainAnimation();
    bool is_quit = false;
  // Monster
  Monster* Threat = new Monster[NUM_THREAT];
  for(int i = 0; i < NUM_THREAT;i++)
  {
  Monster* p_monster = (Threat+i);
  bool check = p_monster->LoadImg("res/1.png",g_screen);
  p_monster->SetRect(SCREEN_WIDTH+i*300,SCREEN_HEIGHT*0.5);
  p_monster->set_xval(10);//Chim bay
  p_monster->SetAnimation();
  }//Tro ngai 1 load Animation

  std::vector<Monster2*>p_Monster2 = MonsterList();


  Monster2 BotVipMonster;
  BotVipMonster.LoadImg2("res/Ghost.png",g_screen);
  BotVipMonster.SetAnimation2();
  BotVipMonster.SetX(500);
  BotVipMonster.SetY(50);

  Monster2 Death_monster;

  bool res = Death_monster.LoadImg3("res/Death_Monster.png",g_screen);
  Death_monster.SetAnimation3();


    Mix_PlayChannel(-1,g_menu_sound,-1);
  int CheckMenu = CommonFunc::CreateMainMenu(g_screen,g_font);
    if(CheckMenu == 0)
    {
        is_quit =false;
    }
    while(!is_quit)
    {   int CheckMenu1 = 1000;
        FPS.start();
    while(SDL_PollEvent(&g_event) != 0)
    {
        if(g_event.type == SDL_QUIT)
        {
            is_quit = true;
        }
            p_player.HandleInputAction(g_event,g_screen,player_sound);
        }

          SDL_SetRenderDrawColor(g_screen, RENDER_DRAWN_COLOR,RENDER_DRAWN_COLOR,RENDER_DRAWN_COLOR,RENDER_DRAWN_COLOR);
          SDL_RenderClear(g_screen);
          g_Background.Render(g_screen,NULL);
          game_map.DrawMap(g_screen);
          Map map_data = game_map.getMap();

          p_player.HandleBullet(g_screen);
          p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
          p_player.Player(map_data,player_sound);
          p_player.ShowFrame(g_screen);


          float X = p_player.GetX();
          float Y = p_player.GetY();

          BotVipMonster.SetMapXY(map_data.start_x_,map_data.start_y_);
          BotVipMonster.Show2("res/Ghost.png",g_screen);
          BotVipMonster.BotGameVip(X,Y);
          SDL_Rect CheckBotVip;
          //Check Va chạm Con Ghost
          CheckBotVip.x = BotVipMonster.GetRect().x;
          CheckBotVip.y = BotVipMonster.GetRect().y;
          CheckBotVip.w = BotVipMonster.GetRect().w/12;
          CheckBotVip.h = BotVipMonster.GetRect().h;
          SDL_Rect p_playerCheck1;
             p_playerCheck1.x = p_player.GetRect().x;
             p_playerCheck1.y = p_player.GetRect().y;
             p_playerCheck1.w = p_player.get_width_frame();
             p_playerCheck1.h = p_player.get_height_frame();

            bool check1 = CommonFunc::CheckCollision(CheckBotVip,p_playerCheck1);
            if(check1 == true)
            {
                   int x = CommonFunc::CreateMainMenuPause(g_screen,g_font);
                    p_player.SetCheckMenu(x+1);
                if(x == 1){
               SDL_QUIT;close();}

             }
             //////////////
            game_map.SetMap(map_data);
            //Run Monster
            for(int i = 0 ;i < NUM_THREAT;i++)
            {Monster* p_monster  =  (Threat+i);
             p_monster->ShowMonster(g_screen);//Chim bay
             p_monster->handleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
             SDL_Rect p_playerCheck;
             p_playerCheck.x = p_player.GetRect().x;
             p_playerCheck.y = p_player.GetRect().y;
             p_playerCheck.w = p_player.get_width_frame();
             p_playerCheck.h = p_player.get_height_frame();
             SDL_Rect ThreatCheck;
             ThreatCheck.x = p_monster->GetRect().x;
             ThreatCheck.y = p_monster->GetRect().y;
             ThreatCheck.h = p_monster->get_height_frame();
             ThreatCheck.w = p_monster->get_width_frame();

             bool check = CommonFunc::CheckCollision(p_playerCheck,ThreatCheck);
             if(check == true)
             {
                   int x = CommonFunc::CreateMainMenuPause(g_screen,g_font);
                    p_player.SetCheckMenu(x+1);
                if(x == 1){SDL_QUIT;close();}

             }

             }
            if(p_Monster2.size()>0)
            {
            for(int i = 0; i < p_Monster2.size();i++)
            {
                Monster2* p_Monster2_ = p_Monster2.at(i);
                p_Monster2_->SetMapXY(map_data.start_x_,map_data.start_y_);
                p_Monster2_->DoPlayer(map_data);
                p_Monster2_->Show("res/MonsterLeft.png",g_screen);
                p_Monster2_->Make_Bullet(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);

             SDL_Rect CheckMonster;
             CheckMonster.x = p_Monster2_->GetRect().x;
             CheckMonster.y = p_Monster2_->GetRect().y;
             CheckMonster.w = p_Monster2_->GetRect().w/6;
             CheckMonster.h = p_Monster2_->GetRect().h;
             bool b_BLT = false;
             bool CheckMonsterCollision = false;
             CheckMonsterCollision = CommonFunc::CheckCollision(CheckMonster,p_playerCheck1);
             if(CheckMonsterCollision == true)
                     {    int x = CommonFunc::CreateMainMenuPause(g_screen,g_font);
                          p_player.SetCheckMenu(x+1);
                          if(x == 1){SDL_QUIT;close();}
                     }
             std::vector<Bullet*> T_bullet = p_Monster2_->GetBullet();
             for(int i = 0; i < T_bullet.size();i++)
             {
                 Bullet* T_bullet_ = T_bullet.at(i);
                 if(T_bullet_ != NULL)
                 {
                     b_BLT = CommonFunc::CheckCollision(p_playerCheck1,T_bullet_->GetRect());
                     if(b_BLT == true)
                     {    int x = CommonFunc::CreateMainMenuPause(g_screen,g_font);
                          p_player.SetCheckMenu(x+1);
                          if(x == 1){SDL_QUIT;close();}

                     }
                 }
             }
            }
            }

            //Check Clllistion
            std::vector<Bullet*>bullet_list = p_player.GetList();
            for(int i = 0;i < bullet_list.size();i++)
            {
                Bullet* p_bullet = bullet_list.at(i);
                    for(int t = 0; t < p_Monster2.size();t++)
                    {
                        Monster2* p_MonsterCheck  = p_Monster2.at(t);
                            SDL_Rect GetRectCollistion;
                            GetRectCollistion.x = p_MonsterCheck->GetRect().x;
                            GetRectCollistion.y = p_MonsterCheck->GetRect().y;
                            GetRectCollistion.h = p_MonsterCheck->get_height_frame();
                             GetRectCollistion.w = p_MonsterCheck->get_width_frame();

                          SDL_Rect BulletRect;
                          BulletRect.x = p_bullet->GetRect().x;
                          BulletRect.y = p_bullet->GetRect().y;
                          BulletRect.w = p_bullet->GetRect().w/5;
                          BulletRect.h = p_bullet->GetRect().h;
                          bool CheckCollistionn = CommonFunc::CheckCollision(BulletRect,GetRectCollistion);
                          if(CheckCollistionn == true)
                          {
                              float X = p_MonsterCheck->GetRect().x-80;
                              float Y = p_MonsterCheck->GetRect().y-100;
                              p_player.RemoveBullet(i);
                              p_MonsterCheck->Free();
                                Death_monster.SetRect(X,Y);
                              for(int x = 0 ;x < 12;x++)
                              {
                                  Death_monster.Setframe(x);
                                  Death_monster.Show3("res/Death_Monster.png",g_screen);

                              }
                              Mix_PlayChannel(-1,g_sound_gun,0);
                              p_Monster2.erase(p_Monster2.begin()+t);

                          }
                        }
                    }

          SDL_RenderPresent(g_screen);
          //Get FPS
          int real_time = FPS.get_tick();
          int time_frame = 1000/FRAME_PER_SECOND;
          if(real_time < time_frame)
          {
              int delay_time = time_frame - real_time;
              if(delay_time >= 0)SDL_Delay(delay_time);
          }
    }
    close();

return 1;
    }

