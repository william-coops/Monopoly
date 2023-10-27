#pragma once

#include "State.h"
#include "Button.h"

class menu_state : public state
{
    private:
        //background of the menu
        sf::Texture background_tex;
        sf::Sprite background;
        sf::RectangleShape shape;

        //name if project, the title
        sf::Text title;

        //player count bool to allow play to be pressed
        bool players_selected= false;

        void init_title_and_background();

    public:
        menu_state(sf::RenderWindow* window) : state(window)
        {
            this->init_title_and_background();
        };
        virtual ~menu_state(){};

        //functions

        void end_state();

        void update();
  
        void render(sf::RenderTarget* target);
};

