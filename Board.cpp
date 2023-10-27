#include "Board.h"

//properties class
//public functions
//setters and getters
void properties::update_int_position(int position){this->position_on_board=position;}
int properties::return_int_position(){return this->position_on_board;}
bool& properties::is_property_buyable(){return this->buyable;}
std::string properties::get_name(){return this->name;}

//property area functions
void properties::update_x(int x_coord){this->x=x_coord;}
void properties::update_y(int y_coord){this->y=y_coord;}
int properties::return_x(){return this->x;}
int properties::return_y(){return this->y;}
void properties::make_area()
{
    //the area is the exact size of each property
    property_area.setPosition(sf::Vector2f(x,y));
    property_area.setSize(sf::Vector2f(70,160));
    property_area.setOrigin(sf::Vector2f(70/2,160/2));
    property_area.setFillColor(sf::Color::Transparent);//dont want to see them, just want to 'click' the property
    if((position_on_board>=10 && position_on_board<=20) ||(position_on_board>=30 && position_on_board<=40)){
        property_area.rotate(90);
    } 
}
sf::RectangleShape properties::return_shape(){return this->property_area;}
void properties::render_position_boxes(sf::RenderTarget* target){target->draw(this->property_area);}

//buyable properties class
//public functions

void buyable_properties::update_all_owned() //update land on price
{
    if(all_owned_by_one_player==false){
        this->all_owned_by_one_player=true;
        this->landed_on_price=landed_on_price+landed_on_price;
        std::cout<<"all owned price "<<landed_on_price<<std::endl;
    }
}

int buyable_properties::price_to_pay(){return this->landed_on_price;}

bool& buyable_properties::is_owned(){return this->owned;}
void buyable_properties::update_owned(std::shared_ptr<player> Player)////////////
{
    this->owned=true;
    owned_by = Player->return_name(); //the property is now owned by this player

    //get player number by getting digit from string name
    for(int i=0; i<owned_by.length();i++){
        if(isdigit(owned_by[i]))
            board_player=owned_by[i]-48-1;//ASC11 code, digits start from 48, then minus on for array/vector reasons
    }

    //owner colour displayed on property
    float x = (Player->return_xy_position())[0];
    float y = (Player->return_xy_position())[1];
    owned_color_shape.setPosition(sf::Vector2f(this->x, this->y));
    owned_color_shape.setSize(sf::Vector2f(50, 5));
    owned_color_shape.setOrigin(sf::Vector2f(50/2, 5/2-50));
    owned_color_shape.setFillColor(Player->return_player_color());
    
    //makes sure it is the correct rotation on board
    if((position_on_board>=10 && position_on_board<=20)){
        owned_color_shape.rotate(90);
    } else if(position_on_board>=20 && position_on_board<=30)
        owned_color_shape.rotate(180);
    else if(position_on_board>=30 && position_on_board<=40)
        owned_color_shape.rotate(-90);
}

void buyable_properties::render_house_owner(sf::RenderTarget* target){target->draw(this->owned_color_shape);}

int buyable_properties::return_price(){return this->price;}

int buyable_properties::return_player_owner(){return this->board_player;}

//color properties
//private functions
void color_properties::init_houses()
{
    //store houses in vector
    houses.push_back(property_house_1);
    houses.push_back(property_house_2);
    houses.push_back(property_house_3);
    houses.push_back(property_house_4);
    for(int i =0;i<houses.size();i++)
    {
        houses[i].setSize(sf::Vector2f(10,10));
        houses[i].setPosition(sf::Vector2f(-10,-10));//hides them
        houses[i].setFillColor(sf::Color::Magenta);//very visible against colour properties
    }
}
//public functions
bool color_properties::house_bought()
{
    //house position in respect to which property
    int pos_x = this->return_x() + 27;
    int pos_y = this->return_y() - 75;

    //how many house can be bought
    if(houses_bought<=max_houses-1)//max 4
    {
        houses[houses_bought].setPosition(sf::Vector2f(pos_x-(19*houses_bought), pos_y));
        houses_bought++;
 
        this->landed_on_price=(int)landed_on_price*(2.7); //increases price for each house
        return true;
    }else
        return false;
}
void color_properties::render_houses(sf::RenderTarget* target)
{
    for(int i =0;i<4; i++){
        target->draw(this->houses[i]);
    }
}
int color_properties::return_house_price(){
    return this->house_cost;
}

void color_properties::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    std::cout<<"You have landed on "<<this->name<<std::endl;
    info<<"You have landed on "<<this->name;
    game_information->update(info.str());
    info.str("");
    if(owned==true){ //checks ownership
        if(this->return_player_owner()==player_landed) //own property
        {
            game_information->update("You own this property");
        } else {
            //else pay, owner gets your money
            players[board_player]->update_money(landed_on_price);
            players[player_landed]->update_money(-landed_on_price);


            std::cout<<"owned by: "<<owned_by<<std::endl;
            std::cout<<"You owe"<<landed_on_price<<std::endl;

            info<<"Owned buy: Player "<<this->return_player_owner()+1;
            game_information->update(info.str());
            info.str("");
            info<<"You owe: "<<this->price_to_pay();
            game_information->update(info.str());
            info.str("");
        }
    }
}  

//train station
//public functions
void train_stations::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    //same as an ordinary property, but the more stations one player owns, the greater the land on price
    std::cout<<"You have landed on "<<this->name<<std::endl;
    info<<"You have landed on "<<this->name;
    game_information->update(info.str());
    info.str("");
    if(owned==true){
        players[board_player]->update_money(landed_on_price*players[board_player]->return_train_stations());
        players[player_landed]->update_money(-landed_on_price*players[board_player]->return_train_stations());
    
        if(this->return_player_owner()==player_landed)
        {
            std::cout<<"you own it"<<std::endl;
            game_information->update("You own this property");
        } else {
            //increase rent by 50 for each station owned
            std::cout<<"owned by: "<<owned_by<<std::endl;
            std::cout<<"You owe"<<landed_on_price*players[board_player]->return_train_stations()<<std::endl;
            info<<"Owned buy: Player "<<this->return_player_owner()+1;
            game_information->update(info.str());
            info.str("");
            info<<"You owe: "<<this->landed_on_price*players[board_player]->return_train_stations();
            game_information->update(info.str());
            info.str("");
        }
    }
} 

//companies
//public functions
void companies::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    std::cout<<"You have landed on "<<this->name<<std::endl;
    info<<"You have landed on "<<this->name;
    game_information->update(info.str());
    info.str("");
    if(owned==true){
        if(this->return_player_owner()==player_landed)
        {
            std::cout<<"you own it"<<std::endl;
            game_information->update("You own this property");
        } else{
            info<<"Owned buy: Player "<<this->return_player_owner()+1;
            game_information->update(info.str());
            info.str("");

            int n = players[player_landed]->return_stored_positions().size();
            int dice_roll=players[player_landed]->return_stored_positions()[n-1] - players[player_landed]->return_stored_positions()[n-2];
            std::cout<<dice_roll<<std::endl;
            
            //landed on price depends on dice roll, and more properties = more
            if(players[board_player]->return_companies_owned()==1)
            {
                info<<"You owe: "<<dice_roll;
                game_information->update(info.str());
                info.str("");
            } else if(players[board_player]->return_companies_owned()==2){

                info<<"You owe: "<<dice_roll*10;
                game_information->update(info.str());
                info.str("");
            }
        }
    }
}

//special properties
//public functions
void special_property::passed(std::shared_ptr<player> player){player->update_money(reward);}

void special_property::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    //makes sure the text is appropiate for the property landed on
    if(reward>=0){
        std::cout<<"Landed on "<<this->name<<" . Get "<<reward<<std::endl;
        info<<"landed on "<<this->name<<" . Get "<<reward;
        game_information->update(info.str());
        
    }else if(reward<=0){
        std::cout<<"Landed on "<<this->name<<" . Lose "<<reward<<std::endl;
        info<<"landed on "<<this->name<<" . Lose "<<reward;
        game_information->update(info.str());
    }
    info.str("");
    players[player_landed]->update_money(reward);
}

//cards
//private functions
void cards::init_chance() //get instructions from files
{
    this->chancefile.open("Chance.txt");
    if(!chancefile){
        std::cout<<"No file found!"<<std::endl;
    }
    std::string line;

    //loops through lines of file
    while(chancefile>>std::ws, std::getline(chancefile, line))
    {
        //get postions from each line
        size_t last_index = line.find_last_not_of("0123456789");
        std::string result = line.substr(last_index+1);
        chance_position.push_back(std::stoi(result));

        //get text from each line
        line.pop_back();
        line.pop_back();
        chance_text.push_back(line);
    }
    chancefile.close();
}
void cards::init_chest() //get instructions from files
{
    this->chest_file.open("Chest.txt");
    if(!chest_file){
        std::cout<<"No file found!"<<std::endl;
    }
    std::string line;

    while(chest_file>>std::ws, std::getline(chest_file, line))
    {
        //get postions from each line
        size_t last_index = line.find_last_not_of("0123456789-");
        std::string result = line.substr(last_index+1);
        chest_money.push_back(std::stoi(result));

        //get text from each line
        line.pop_back();
        line.pop_back();
        line.pop_back();
        line.pop_back();
        chest_string.push_back(line);
    }
    chancefile.close();
}
//public functions
void cards::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    std::cout<<"Landed on "<<this->name<<std::endl;
    info<<"landed on "<<this->name;
    game_information->update(info.str());
    info.str("");

    if(this->name == "Chance"){

        std::cout<<chance_text[chance_count]<<std::endl;
        game_information->update(chance_text[chance_count]);

        int move_positions=chance_position[chance_count] - players[player_landed]->return_position();

        if(move_positions<=0 && chance_position[chance_count]!=30)//not jail. dont pass go
        {
            move_positions = 40+move_positions; //make sure player goes past go
            
        }
        players[player_landed]->update_position(move_positions);

        players[player_landed]->update_chance(true);

        chance_count++;

        if(chance_count>=chance_text.size())
            chance_count=0;

    } else if (this->name=="Community Chest")
    {
        std::cout<<chest_string[chest_count]<<std::endl;
        game_information->update(chest_string[chest_count]);

        std::cout<<chest_money[chest_count]<<std::endl;

        players[player_landed]->update_money(chest_money[chest_count]);

        chest_count++;

        if(chest_count>=chest_string.size())
            chest_count=0;
    }
}

//goy to jail
//public function
void go_to_jail::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    std::cout<<"Landed on "<<this->name<<std::endl;
    info<<"Landed on "<<this->name<<". Go to Jail!!";
    game_information->update(info.str());
    info.str("");

    //move position to jail and player function bool
    players[player_landed]->update_into_jail();
    players[player_landed]->update_position(10-(players[player_landed]->return_position()));
}

//other special properties
//public function
void basic_property::landed_on(std::vector<std::shared_ptr<player>> players, int player_landed, std::shared_ptr<game_info> game_information)
{
    std::cout<<"Landed on "<<this->name<<std::endl;
    info<<"Landed on "<<this->name;
    game_information->update(info.str());
    info.str("");
}




