#pragma once

#include "State.h"

#include "player.h"
#include "Button.h"
#include "Board.h"
#include "Leaderboard.h"
#include "game_info.h"

#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>

class game_state : public state
{
    private:
        //game board
        sf::Texture board_tex;
        sf::Sprite board;
        sf::RectangleShape background;

        //player information
        std::vector<std::shared_ptr<player>> player_vector;
        int player_position=1; //position on board
        int player_incriment=0; //simulates players turns by using as index for player_vector
        int number_of_players_left=0;
        
        //scores and game information to be rendered in he game
        std::unique_ptr<leaderboard> scores;
        std::shared_ptr<game_info> game_information;
        std::stringstream info; //is used to combine intergers(eg money) and string to be displayed via game_information
 
        //dice button
        std::unique_ptr<Button> dice;
        //dice
        int dice1=0;
        int dice2=0;
        bool double_roll=false;
        int number_of_double_rolls=0; //if there is more than three in a row then jail!

        bool end_turn=false; //used to create end button after player has their turn

        bool is_buyable=false; //if property is buyable->colour property/train -> owned?

        bool game_over = false;

        std::vector<std::shared_ptr<properties>> properties_vec;  //vector of base class shared pointers for properties
        std::ifstream myfile; //file full of property infomation

        //groups properties so houses can be built
        std::vector<std::vector<std::shared_ptr<properties>>> property_groups; //vector of vector of base class shared pointers of properties
        bool all_owned=false;
        //this is a 2D vector, it stores properties and the player who can buy the houses.
        std::vector<std::vector<int>> properties_available; //if one player owns all of one color then they are stored here for houses to be bought

        //these make sure only the correct player can buy the houses on their go
        bool buy_houses=false;
        bool option=true; //if player has all of one group-> they have an option to buy houses

        //private functions
        void init_property_groups(); //group properties into colors so houses can be bought

        void init_property_positions(); //gives each property a transparent 'button' to click when buying houses
    
        void init_player_vec(); //creates the number of players and adds them to vector

        void init_prop_vec(); //gets property info from file then adds it to the property vector using stringstream

        void init_board(); //load image and create background for buttons/ text

        void init_buttons(); //create dice button 

        void end_turn_option(); //called when user has no other options then end turn->allows them time to buy houses/think


    public:
        game_state(sf::RenderWindow* window) : state(window)
        {
            this->init_player_vec();
            this->init_board();
            this->init_buttons();
            this->init_prop_vec();
            this->scores= std::make_unique<leaderboard>(&this->font, number_of_players);
            this->game_information= std::make_shared<game_info>(&this->font);
            this->init_property_groups();
            this->init_property_positions();
        };
        virtual ~game_state()
        {

        };

        //functions
        void end_state();

        void if_double_roll();
 
        std::vector<int> check_owners(std::vector<std::shared_ptr<properties>> group); //check if/which properties groups are owned by one player
                                                                                        //if so then allow them to be clicked on and bought
        void update();
  
        void render(sf::RenderTarget* target);
};