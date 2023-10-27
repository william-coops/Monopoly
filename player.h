#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class player //this class stores all the infomation about each player. therefore many setters and getters are required
{

    private:
        //game info
        int money=2000;
        int no_of_properties=0;
        int position=0;
        std::string name;

        bool bankrupt=false;

        bool passed_go=false;

        bool jailed=false;
        int goes_in_jail=0;

        //property managment
        int train_stations_owned=0;
        int companies_owned=0;
        bool chance_turn=false;

        std::vector<int> stored_moves{0};

        //gui info
        sf::CircleShape shape;
        sf::Color Player_color;
        int x=900;
        int y=900;
        int property_coords[40][2]; //40 properties to move, x and y coordiantes
        
        void initPropertyCoords();
        
    public:
        player(std::string text, sf::Color player_color)
        {
            this->name=text;
            this->Player_color=player_color;
            this->shape.setPosition(sf::Vector2f(x,y)); 
            this->shape.setRadius(10);
            this->shape.setFillColor(this->Player_color);
            this->initPropertyCoords();

        };
        ~player(){};

        //functions
        //many setters and getters
        void update_position(int positions_moved);
       
        std::vector<float> return_xy_position();
        
        std::vector<int> return_stored_positions();

        void update_train_stations();
        int return_train_stations();

        void update_companies();
        int return_companies_owned();

        sf::Color return_player_color();

        void update_turns_in_jail();
    
        int return_turns_in_jail();
        void update_out_of_jail();

        void update_chance(bool yes_no);
        bool& return_chance();

        void update_into_jail();
        bool& return_jailed();

        bool& has_passed_go();
        void update_passes_go();

        int return_position();

        std::string return_name();

        int return_money();
        void update_money(int gained_or_lost);

        void render(sf::RenderTarget* target);

        bool& return_bankrupt();
        void update_bankrupt();
      

};