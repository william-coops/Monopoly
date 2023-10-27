#include "player.h"

//private function

void player::initPropertyCoords() //tells the shape where to move itself when dice is rolled
{
    for (int pos = 0; pos < 40; pos++) //40 properties to move, x and y coordiantes
    {
        if(pos<=9)
        {
            if(pos==0){ //corner properties are larger, therefore require more precise positions
                property_coords[pos][1] =900;
                property_coords[pos][0] =900;
            }else{
                property_coords[pos][0] = 785 -(75*(pos-1));
                property_coords[pos][1] = 900;
            }
        }else if(pos<=19){
            if(pos==10){
                
                property_coords[pos][0] = 40;
                property_coords[pos][1] = 920;
                
            }else{
                property_coords[pos][0] = 63;
                property_coords[pos][1] = 780 - (75*(pos-11));
            }
        }else if(pos<=29){
            if(pos==20){
                property_coords[pos][0] = 75;
                property_coords[pos][1] = 65;
            }else{
                property_coords[pos][0] = 185 + (75*(pos-21));
                property_coords[pos][1] = 65;
            }
        }else{
            if(pos==30){
                property_coords[pos][0] = 910;
                property_coords[pos][1] = 65;

            }else{
                property_coords[pos][0] = 905;
                property_coords[pos][1] = 175 + (75*(pos-31));
            }
        }
    }
}

//public function
void player::update_position(int positions_moved)
{
    int temp = position;
    if((position+=positions_moved)<=39)
    {
        //normal
    }else{ //only 40 properties so reset
        position=position-40;
        //if last go was on go, dont give extra 200
        if(this->stored_moves[this->stored_moves.size()-1]){
            passed_go=false;
        }else{
            std::cout<<"passed"<<std::endl;
            passed_go=true;
        }
    }
    //position on board
    if(this->jailed==false)
        this->shape.setPosition(sf::Vector2f(property_coords[position][0],property_coords[position][1]));       
    else
        this->shape.setPosition(sf::Vector2f(100, 850)); //set to inside the jail, not the outside
    this->stored_moves.push_back(this->position);
    //std::cout<<stored_moves[stored_moves.size()-1]<<std::endl;
}
std::vector<float> player::return_xy_position()
{
    float x = this->shape.getPosition().x;
    float y = this->shape.getPosition().y;

    std::vector<float> positions;
    positions.push_back(x);
    positions.push_back(y);

    return positions;
}
std::vector<int> player::return_stored_positions(){return this->stored_moves;}

void player::update_train_stations(){this->train_stations_owned++;}
int player::return_train_stations(){return this->train_stations_owned;}

void player::update_companies(){this->companies_owned++;}
int player::return_companies_owned(){return this->companies_owned;}

sf::Color player::return_player_color(){return this->Player_color;}

void player::update_turns_in_jail()
{
    goes_in_jail++;
    if(goes_in_jail==3){
        update_out_of_jail();
    }
}
int player::return_turns_in_jail(){return this->goes_in_jail;}
void player::update_out_of_jail()
{
    this->jailed=false;
    goes_in_jail=0;
}

void player::update_chance(bool yes_no){this->chance_turn=yes_no;}
bool& player::return_chance(){return this->chance_turn;}

void player::update_into_jail(){this->jailed=true;}
bool& player::return_jailed(){return this->jailed;}

bool& player::has_passed_go(){return this->passed_go;}
void player::update_passes_go(){this->passed_go=false;}

int player::return_position(){return this->position;}

std::string player::return_name(){return this->name;}

int player::return_money(){return this->money;}
void player::update_money(int gained_or_lost){this->money+=gained_or_lost;}

void player::render(sf::RenderTarget* target){target->draw(this->shape);   }

bool& player::return_bankrupt(){return this->bankrupt;}
void player::update_bankrupt()
{
    if(this->money<=-1)
    {
        this->bankrupt=true;
        //std::cout<<this->name<<" is Bankrupt!!"<<std::endl;
    }
}