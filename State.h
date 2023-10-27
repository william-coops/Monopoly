#pragma once

#include<iostream>
#include<stack>
#include<map>

//the SFML files
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class state
{
    protected:
        sf::RenderWindow* window;
        bool quit=false;
        int number_of_players=2;

        //font
        //this is he font used for the whole project
        sf::Font font;
        void init_font();

    public:
        state(sf::RenderWindow* window)
        {
            this->window =window; //renders on window initilaised in the state class
            this->init_font();
        };
        virtual ~state(){};

        const bool& get_quit() const; //check if the state was quite
        
        //virtual functions
        virtual void end_state()=0; //returns string saying state has been ended
        virtual void update()=0;
        virtual void render(sf::RenderTarget* target=nullptr)=0;
};