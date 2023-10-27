#include "game_info.h"

//private functions
void game_info::init_text_game()
{
    game_info_text_vec.push_back(line_player);
    game_info_text_vec.push_back(line1);
    game_info_text_vec.push_back(line2);
    game_info_text_vec.push_back(line3);
    game_info_text_vec.push_back(line4);
}

void game_info::init_string_game()
{
    text_string.push_back("Player 1 turn");
    text_string.push_back("Game started!");
    text_string.push_back("");
    text_string.push_back("");
    text_string.push_back("");
}

void game_info::init_box()
{
    for(int i=0;i<5;i++)
    {
        //positioning of text
        static int x=980;
        static int y=750;
        this->game_info_text_vec[i].setFont(*this->font);
        this->game_info_text_vec[i].setString(text_string[i]);
        this->game_info_text_vec[i].setFillColor(sf::Color::Black);
        this->game_info_text_vec[i].setCharacterSize(12);
        this->game_info_text_vec[i].setPosition(x, y);
        y+=25; //each line is further down
    }
}

//public functions
void game_info::update_turn(std::string turn)
{
    //changes player turn line
    text_string[0]=(turn);
    game_info_text_vec[0].setString(turn);

}

void game_info::update(std::string info)
{
    //pushes down each line before adding new one
    //but doesnt push last line as it will throw a range error for the vector
    //last line is just written over
    for(int i=4; i>0;i--)
    {
        text_string[i]=text_string[i-1];
        game_info_text_vec[i].setString(text_string[i-1]);
        
    }
    //adds new line
    text_string[1]=info;
    game_info_text_vec[1].setString(info);
}

void game_info::render(sf::RenderTarget* target)
{
    for(int i =0;i<5;i++)
    {
        target->draw(this->game_info_text_vec[i]);
    }
}