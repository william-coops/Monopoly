#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
class leaderboard
{
    private:
        sf::Font* font;
        //sf::Text text;

        int number_of_players=2;

        //gui player info
        sf::Text player1_name;
        sf::Text player1_budget;
        sf::Text player2_name;
        sf::Text player2_budget;
        /*sf::Text player3_name;
        sf::Text player3_budget;
        sf::Text player4_name;
        sf::Text player4_budget;*/

        //vector of text, needs text applying and a string set to it
        std::vector<sf::Text> player_text;
        void init_gui_player_vec();

        //vector of the strings to add to the text to be rendered
        std::vector<std::string> text_string;
        void init_tex_string();

        //initalise the psoitioning of the text
        void init_table(sf::Font* font);


    public:
        leaderboard(sf::Font* font, int number_players)
        {
            this->number_of_players=number_players;
            this->init_gui_player_vec();
            this->init_tex_string();
            this->font = font;
            this->init_table(font);

        };
        ~leaderboard(){};

        void update(int player_number, int money);

        void render(sf::RenderTarget* target);

};