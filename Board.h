#pragma once

#include<iostream>
#include<stack>
#include<map>
#include <fstream>
#include <memory>

#include "Leaderboard.h"
#include "game_info.h"
#include "player.h"


class properties
{
    protected:
        std::string name;

        bool buyable = false;

        int position_on_board=0;

        std::stringstream info; //to update game information

        //property 'button' to click to buy houses
        int x=0;
        int y=0;
        sf::RectangleShape property_area;

    public:
        properties(std::string Name){this->name=Name;};
        virtual ~properties(){};

        //functions
        //getters and setters
        void update_int_position(int position);
        int return_int_position();
        bool& is_property_buyable();
        std::string get_name();

        //property area function
        void update_x(int x_coord);
        void update_y(int y_coord);
        int return_x();
        int return_y();
        void make_area();
        sf::RectangleShape return_shape();
        void render_position_boxes(sf::RenderTarget* target);

        //each property needs a function for when a player lands on it, atleast display the property name
        virtual void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)=0;

};

class buyable_properties : public properties
{
    protected:
        //prices
        int price=0;
        int landed_on_price=0;

        //ownership
        bool owned = false;
        int board_player=-1;
        std::string owned_by;
        sf::RectangleShape owned_color_shape;
        bool all_owned_by_one_player=false;

    public:
        buyable_properties(int Price, std::string prop_name, int land_on_price) : properties(prop_name)
        {
            this->price=Price;
            this->landed_on_price=land_on_price;
            this->buyable=true;            
        };
        ~buyable_properties(){};

        //functions
        void update_all_owned(); //update land on price

        int price_to_pay();

        bool& is_owned();
        void update_owned(std::shared_ptr<player> Player);

        void render_house_owner(sf::RenderTarget* target);

        int return_price();
        int return_player_owner();
};
class color_properties : public buyable_properties
{
    private:
        //houses
        int max_houses=4;
        int houses_bought=0;
        int house_cost=100;
        sf::RectangleShape property_house_1;
        sf::RectangleShape property_house_2;
        sf::RectangleShape property_house_3;
        sf::RectangleShape property_house_4;
        std::vector<sf::RectangleShape> houses;

        void init_houses();

    public:
        color_properties(int Price, std::string prop_name, int land_on_price) : buyable_properties(Price, prop_name, land_on_price)
        {
            this->init_houses();
        };
        ~color_properties(){};

        //functions
        bool house_bought();

        void render_houses(sf::RenderTarget* target);

        int return_house_price();

        void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information); 

};
class train_stations : public buyable_properties
{
    public:
        train_stations(int Price, std::string prop_name, int land_on_price) : buyable_properties(Price, prop_name, land_on_price)
        {

        };
        ~train_stations(){};

        void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information);     

};

class companies : public buyable_properties
{
    public:
        companies(int Price, std::string prop_name, int land_on_price) : buyable_properties(Price, prop_name, land_on_price)
        {

        };
        ~companies(){};

        //functions
        void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information);
};

class special_property : public properties //GO, tax properties
{
    private:
        //reward can be nagative for tax properties
        int reward;
        bool is_passed=false;

    public:
        special_property(std::string prop_name, int money) : properties(prop_name)
        {
            this->reward=money;
        };
        ~special_property(){};

        //functions
        void passed(std::shared_ptr<player> player);//{player->update_money(reward);}

        void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information);
};

class cards :public properties
{
private:
    //chance cards
    //chnace cards are only position move cards
    std::vector<std::string> chance_text;
    std::vector<int> chance_position;
    std::ifstream chancefile;
    int chance_count=0;

    //chest cards
    //chest cards are only payment type cards
    std::vector<std::string> chest_string;
    std::vector<int> chest_money;
    std::ifstream chest_file;
    int chest_count=0;
    
    //open files containting promptts for chance and chest
    //get instructions from files
    void init_chance();
    void init_chest();

public:
    cards(std::string prop_name) : properties(prop_name)
    {
        this->init_chance();
        this->init_chest();
    };
    ~cards(){};

    //functions
    void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information);
};

class go_to_jail : public properties
{
    public:
        go_to_jail(std::string name) : properties(name){};
        ~go_to_jail(){};

        //functions
        void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information);
};

class basic_property : public properties //such as free parking, jail
{
    public:
        basic_property(std::string name) : properties(name){};
        ~basic_property(){};

        //fucntions
        void landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information);
};
