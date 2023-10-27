#include "Leaderboard.h"

//private functions
void leaderboard::init_gui_player_vec()
{
    player_text.push_back(player1_name);
    player_text.push_back(player1_budget);
    player_text.push_back(player2_name);
    player_text.push_back(player2_budget);
    /*player_text.push_back(player3_name);
    player_text.push_back(player3_budget);
    player_text.push_back(player4_name);
    player_text.push_back(player4_budget);*/
}

void leaderboard::init_tex_string(){
    text_string.push_back("Player 1 (RED)");
    text_string.push_back("Player 1 Budget: 2000");
    text_string.push_back("Player 2 (BLUE)");
    text_string.push_back("Player 2 Budget: 2000");
    /*text_string.push_back("Player 3");
    text_string.push_back("Player 3 Budget: 2000");
    text_string.push_back("Player 4");
    text_string.push_back("Player 4 Budget: 2000");*/
}
void leaderboard::init_table(sf::Font* font)
{
    //positioning of text
    for(int i=0;i<number_of_players*2;i++)
    {
        static int x=1000;
        static int y=50;
        this->player_text[i].setFont(*this->font);
        this->player_text[i].setString(text_string[i]);
        this->player_text[i].setFillColor(sf::Color::Black);
        this->player_text[i].setCharacterSize(15);
        this->player_text[i].setPosition(x, y);
        y+=20; //each line is further down
    }
}

//public functions
void leaderboard::update(int player_number, int money)
{
    //uses string stream to combine string and integers
    std::stringstream ss;
    ss<<"Player "<<player_number<<" Budget: "<<money;
    //changes the appropiate line
    if(player_number==1){
        this->text_string[player_number]=ss.str();
        this->player_text[player_number].setString(ss.str());
    }else if(player_number==2){
        this->text_string[3]=ss.str();
        this->player_text[3].setString(ss.str());
    }

}
void leaderboard::render(sf::RenderTarget* target)
{
    //only render the number of player lines needed
    for(int i =0;i<number_of_players*2;i++)
    {
        target->draw(this->player_text[i]);
    }
}
