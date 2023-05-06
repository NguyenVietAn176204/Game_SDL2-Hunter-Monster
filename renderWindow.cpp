#include"renderWindow.h"
#include"Menu.h"
#include"BaseObject.h"
bool CommonFunc::CheckMenu(int& x,int& y,const SDL_Rect& rect)
{
    if(x >= rect.x && x<= rect.x+rect.w && y >= rect.y && y <= rect.y+rect.h)
    return true;
    return false;
}

bool CommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}
int CommonFunc::CreateMainMenu(SDL_Renderer* des,TTF_Font* font)
{
//  if(MainMenu == NULL){std::cout << "Main Menu Failed";return 0;}
  int Res = 2;
  SDL_Rect pos[Res];
  pos[0].x = 500;
  pos[0].y = 350;


  pos[1].x = 500;
  pos[1].y = 400;

 Menu p_menu[Res];
  p_menu[0].SetText("Play");
  p_menu[0].SetColor(Menu::BLACK_TEXT);
  p_menu[0].SetRect(pos[0].x,pos[0].y);

   p_menu[1].SetText("Exit");
  p_menu[1].SetColor(Menu::BLACK_TEXT);
  p_menu[1].SetRect(pos[1].x,pos[1].y);

  bool sellected[Res] = {0,0};

  int xMouse;
  int yMouse;
   BaseObject g_Menu;
   bool res =g_Menu.LoadIMG("res/s.png",des);
  SDL_Event m_event;
while(true)
{  SDL_SetRenderDrawColor(des, RENDER_DRAWN_COLOR,RENDER_DRAWN_COLOR,RENDER_DRAWN_COLOR,RENDER_DRAWN_COLOR);
          SDL_RenderClear(des);
   g_Menu.Render(des);
for(int i = 0;i < Res;i++)
{
    p_menu[i].CreateMenu(font,des);
    p_menu[i].Render(des);
}
while(SDL_PollEvent(&m_event))
{
    switch(m_event.type)
    {
    case SDL_QUIT:
        return 1;
        break;
    case SDL_MOUSEMOTION:
        xMouse = m_event.motion.x;
        yMouse = m_event.motion.y;
     for(int i = 0;i  < Res;i++)
     {
         if(CheckMenu(xMouse,yMouse,p_menu[i].GetRect()))
         {
             if(sellected[i] == false)
             {
                 sellected[i] = 1;
                 p_menu[i].SetColor(Menu::RED_TEXT);

             }
         }
         else
         {
              if(sellected[i] == true)
             {
                 sellected[i] = 0;
                 p_menu[i].SetColor(Menu::BLACK_TEXT);
         }
     }
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
        xMouse = m_event.button.x;
        yMouse = m_event.button.y;
    for(int i = 0; i < 2;i++)
    {
        if(CheckMenu(xMouse,yMouse,p_menu[i].GetRect()))
        {
            return i;
        }
    }
    break;
    case SDL_KEYDOWN:
        if(m_event.key.keysym.sym == SDLK_ESCAPE)
        {
            return 1;
        }
    default:
        break;
}
}
SDL_RenderPresent(des);
}
IMG_Quit();
SDL_Quit();
return 1;
}
int CommonFunc::CreateMainMenuPause(SDL_Renderer* des,TTF_Font* font)
{
//  if(MainMenu == NULL){std::cout << "Main Menu Failed";return 0;}
  int Res = 2;
  SDL_Rect pos[Res];
  pos[0].x = 500;
  pos[0].y = 350;


  pos[1].x = 500;
  pos[1].y = 400;

 Menu p_menu[Res];
  p_menu[0].SetText("Continue");
  p_menu[0].SetColor(Menu::BLACK_TEXT);
  p_menu[0].SetRect(pos[0].x,pos[0].y);

   p_menu[1].SetText("Exit");
  p_menu[1].SetColor(Menu::BLACK_TEXT);
  p_menu[1].SetRect(pos[1].x,pos[1].y);

  bool sellected[Res] = {0,0};

  int xMouse;
  int yMouse;
  SDL_Event m_event;
  for(int i = 0;i < Res;i++)
{
    p_menu[i].CreateMenu(font,des);
    p_menu[i].Render(des);
}
while(true)
{
    while(SDL_PollEvent(&m_event))
{
    switch(m_event.type)
    {
    case SDL_QUIT:
        return 1;
        break;
    case SDL_MOUSEMOTION:
        xMouse = m_event.motion.x;
        yMouse = m_event.motion.y;
     for(int i = 0;i  < Res;i++)
     {
         if(CheckMenu(xMouse,yMouse,p_menu[i].GetRect()))
         {
             if(sellected[i] == false)
             {
                 sellected[i] = 1;
                 p_menu[i].SetColor(Menu::RED_TEXT);

             }
         }
         else
         {
              if(sellected[i] == true)
             {
                 sellected[i] = 0;
                 p_menu[i].SetColor(Menu::BLACK_TEXT);
         }
     }
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
        xMouse = m_event.button.x;
        yMouse = m_event.button.y;
    for(int i = 0; i < 2;i++)
    {
        if(CheckMenu(xMouse,yMouse,p_menu[i].GetRect()))
        {
            return i;
        }
    }
    break;
    case SDL_KEYDOWN:
        if(m_event.key.keysym.sym == SDLK_ESCAPE)
        {
            return 1;
        }
    default:
        break;
}
}
SDL_RenderPresent(des);
}
IMG_Quit();
SDL_Quit();
return 1;
}
