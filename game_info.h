#pragma once

//#include <<sstream>
#include <sstream>
#include <SFML/Graphics.hpp>
class game_info
{
    private:

        //lines to update game info
        sf::Font* font;
        sf::Text line_player; //this line will always contain the player turn
        sf::Text line1;
        sf::Text line2;
        sf::Text line3;
        sf::Text line4;

         //vector of text, needs text applying and a string set to it
        std::vector<sf::Text> game_info_text_vec;
        void init_text_game();

         //vector of the strings to add to the text to be rendered
        std::vector<std::string> text_string;
        void init_string_game();

        //initalise the psoitioning of the text
        void init_box();

    public:
        game_info(sf::Font* font)
        {
            this->init_text_game();
            this->init_string_game();
            this->font = font;
            this->init_box();
        };
        ~game_info(){};                                   

        void update_turn(std::string turn);

        void update(std::string info);

        void render(sf::RenderTarget* target);
        
};