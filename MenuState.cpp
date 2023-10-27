#include "State.h"
#include "Button.h"

#include<iostream>

#include "MenuState.h"


void menu_state::init_title_and_background()
{
    this->shape.setPosition(sf::Vector2f(0,0));
    this->shape.setSize(sf::Vector2f(1300, 1000));
    this->shape.setFillColor(sf::Color(213, 232, 212, 255));
    this->title.setFont(this->font);
    this->title.setString("MONOPOLY");
    this->title.setFillColor(sf::Color::Black);
    this->title.setCharacterSize(190);
    this->title.setPosition(120, 150);
}

//Public functions

void menu_state::end_state()
{
    std::cout<<"ending menu state"<<std::endl;
}

void menu_state::update()
{
    if(sf::Mouse::isButtonPressed)
    {
        //creates buttons to progress the menu
        std::unique_ptr<Button> play_button(new Button(500, 500, 150, 50, &this->font, "Play Game",
        sf::Color(70,70,70,200)));
        std::unique_ptr<Button> two_player_button(new Button(500, 600, 150, 50, &this->font, "2 Players",
        sf::Color(70,70,70,200)));

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

        //find where the mouse was upon mouse click
        play_button->update(mouse_pos_f);
        two_player_button->update(mouse_pos_f);

        //functionality after mouse press
        if(two_player_button->isPressed()==true)
        {
            this->players_selected=true;
            std::cout<<"2 players selected!"<<std::endl;
            this->number_of_players=2;
        }else if(play_button->isPressed()==true) //starts the game
        {
            if(players_selected==true) //only if number of players has been selected
            {
                std::cout<<"Game Started!"<<std::endl;
                this->quit=true; //quits the menu state->loads game state
            }else //if not, returns error message
            {
                std::cout<<"Please select number of players"<<std::endl;
            }
        }
    }
    
}
void menu_state::render(sf::RenderTarget* target)
{
    //catch
    if(!target)
        target = this->window;

    //draws all the buttons
    target->draw(this->shape);
    std::unique_ptr<Button> play_button(new Button(500, 500, 150, 50, &this->font, "Play Game",
        sf::Color(70,70,70,200)));
    play_button->render(target);

    std::unique_ptr<Button> two_player_button(new Button(500, 600, 150, 50, &this->font, "2 Players",
        sf::Color(70,70,70,200)));
    two_player_button->render(target);

    target->draw(this->title);
}