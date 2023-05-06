#include"Menu.h"
#include"BaseObject.h"
Menu::Menu()
{

}
Menu::~Menu()
{
}
void Menu::SetColor(const int& type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color= {255,0,0};
        Text_clor = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color= {255,255,255};
        Text_clor = color;
    }
    else
    {
        SDL_Color color= {0,0,0};
        Text_clor = color;
    }
}
void Menu::CreateMenu(TTF_Font* font, SDL_Renderer* des)
{
Free();
SDL_Surface* textSurface = TTF_RenderText_Solid(font,p_text.c_str(),Text_clor);
SDL_Texture* texture = NULL;
	if (textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		//Tạo texture text từ surface
		SDL_SetColorKey(textSurface,SDL_TRUE,SDL_MapRGB(textSurface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
		texture = SDL_CreateTextureFromSurface(des,textSurface);
		if (texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		 if(texture != NULL)
 {
     rect_.w = textSurface->w;
     rect_.h = textSurface->h;
 }
    SDL_FreeSurface(textSurface);
    p_object_ = texture;
}
}

