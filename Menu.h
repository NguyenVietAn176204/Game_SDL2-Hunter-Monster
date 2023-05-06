#ifndef MENU_H
#define MENU_H

#include"BaseObject.h"
class Menu : public BaseObject
{
 public:
      Menu();
     ~Menu();
     enum TextColor
     {
         RED_TEXT = 0,
         WHITE_TEXT = 1,
         BLACK_TEXT = 2,
     };
     void SetText(const std::string& str){p_text = str;}
     void SetColor(const int& type);
     void CreateMenu(TTF_Font* font,SDL_Renderer* des);
 private:
    std::string p_text;
    SDL_Color Text_clor;
};
#endif

