#include "GameState.h"

//private functions

void game_state::init_property_groups()//every colour group where houses can be bought
{
    std::vector<std::shared_ptr<properties>> brown;
    std::vector<std::shared_ptr<properties>> blue;
    std::vector<std::shared_ptr<properties>> pink;
    std::vector<std::shared_ptr<properties>> orange;
    std::vector<std::shared_ptr<properties>> red;
    std::vector<std::shared_ptr<properties>> yellow;
    std::vector<std::shared_ptr<properties>> green;
    std::vector<std::shared_ptr<properties>> dark_blue;

    brown.push_back(properties_vec[1]);
    brown.push_back(properties_vec[3]);
    property_groups.push_back(brown);

    blue.push_back(properties_vec[6]);
    blue.push_back(properties_vec[8]);
    blue.push_back(properties_vec[9]);
    property_groups.push_back(blue);

    pink.push_back(properties_vec[11]);
    pink.push_back(properties_vec[13]);
    pink.push_back(properties_vec[14]);
    property_groups.push_back(pink);

    orange.push_back(properties_vec[16]);
    orange.push_back(properties_vec[18]);
    orange.push_back(properties_vec[19]);
    property_groups.push_back(orange);

    red.push_back(properties_vec[21]);
    red.push_back(properties_vec[23]);
    red.push_back(properties_vec[24]);
    property_groups.push_back(red);

    yellow.push_back(properties_vec[26]);
    yellow.push_back(properties_vec[27]);
    yellow.push_back(properties_vec[29]);
    property_groups.push_back(yellow);

    green.push_back(properties_vec[31]);
    green.push_back(properties_vec[32]);
    green.push_back(properties_vec[34]);
    property_groups.push_back(green);

    dark_blue.push_back(properties_vec[37]);
    dark_blue.push_back(properties_vec[39]);
    property_groups.push_back(dark_blue);
}
void game_state::init_property_positions() //each property has a transparent 'button' to click when buying houses
{
    for (int pos = 0; pos < 40; pos++)
    {
        if(pos<=9)
        {
            if(pos==0){
                properties_vec[pos]->update_x(900);
                properties_vec[pos]->update_y(900);
            }else{
                properties_vec[pos]->update_x(785 -(75*(pos-1)));
                properties_vec[pos]->update_y(900);
            }
        }else if(pos<=19){
            if(pos==10){
                
                properties_vec[pos]->update_x(60);
                properties_vec[pos]->update_y(900);
                
            }else{
                properties_vec[pos]->update_x(63);
                properties_vec[pos]->update_y(777 - (75*(pos-11)));
            }
        }else if(pos<=29){
            if(pos==20){
                properties_vec[pos]->update_x(70);
                properties_vec[pos]->update_y(65);
            }else{
                properties_vec[pos]->update_x(185 + (75*(pos-21)));
                properties_vec[pos]->update_y(65);
            }
        }else{
            if(pos==30){
                properties_vec[pos]->update_x(910);
                properties_vec[pos]->update_y(65);

            }else{
                properties_vec[pos]->update_x(905);
                properties_vec[pos]->update_y(175 + (75*(pos-31)));
            }
        }
        properties_vec[pos]->make_area();
    }
}

void game_state::init_player_vec() //createsthe number of players and adds them to vector
{ 
    if(number_of_players==2){
        this->player_vector.push_back(std::make_shared<player>("Player 1", sf::Color::Red));
        this->player_vector.push_back(std::make_shared<player>("Player 2", sf::Color::Blue));
        number_of_players_left=number_of_players;
    }
}
void game_state::init_prop_vec()
{
    //get file properties info
    this->myfile.open("properties.txt");
    if(!myfile){
        std::cout<<"no file found"<<std::endl;
    }

    std::string line;

    std::vector<int> prices;
    std::vector<std::string> names;
    std::vector<int> rents;

    while(std::getline(myfile, line))
    {
        //use a stringstream to split each line of file into componets
        std::stringstream ss(line);
        int price;
        std::string name;
        int rent;
        if(ss >> price >> name >> rent){
            prices.push_back(price);
            names.push_back(name);
            rents.push_back(rent);
        }
    }
    myfile.close();
    int offset=0;//not every property is in file so this offsets reading the file to not go over files range
    //loop add every property into vector of base class shared pointers
    for(int prop=0; prop<40; prop++)
    {
        if(prop==0){
            this->properties_vec.push_back(std::make_shared<special_property>("Go", 200));
            offset++;
        }else if(prop==4){
            this->properties_vec.push_back(std::make_shared<special_property>("Income Tax", -100));
            offset++;
        }else if(prop==38){
            this->properties_vec.push_back(std::make_shared<special_property>("Super Tax", -200));
            offset++;
        }else if(prop==2 || prop==17 || prop==33){
            this->properties_vec.push_back(std::make_shared<cards>("Community Chest"));
            offset++;
        }else if(prop==7 || prop==22 ||prop==36){
            this->properties_vec.push_back(std::make_shared<cards>("Chance"));
            offset++;
        }else if(prop==10){
            this->properties_vec.push_back(std::make_shared<basic_property>("Jail"));
            offset++;
        }else if(prop==20){
            this->properties_vec.push_back(std::make_shared<basic_property>("Free-Parking"));
            offset++;
        }else if(prop==30){
            this->properties_vec.push_back(std::make_shared<go_to_jail>("Go to Jail"));
            offset++;
        }else if(prop==5 || prop==15 || prop==25 || prop==35){
            this->properties_vec.push_back(std::make_shared<train_stations>(prices[prop-offset], names[prop-offset], rents[prop-offset]));
        }else if(prop==12 || prop ==28){
            this->properties_vec.push_back(std::make_shared<companies>(prices[prop-offset], names[prop-offset], rents[prop-offset]));
        }else{
            this->properties_vec.push_back(std::make_shared<color_properties>(prices[prop-offset], names[prop-offset], rents[prop-offset]));
        }
        this->properties_vec[prop]->update_int_position(prop); //gives position on board to each property
    }
}
void game_state::init_board() //load image and create background for buttons/ text
{
    if(!this->board_tex.loadFromFile("board_final.jpg"))
        std::cout<<"Error coudnt load texture"<<std::endl;
    this->board.setTexture(this->board_tex);

    this->background.setPosition(sf::Vector2f(970, 0));//970 toi create black border around board
    this->background.setSize(sf::Vector2f(336, 964));
    this->background.setFillColor(sf::Color(213, 232, 212, 255));
}
void game_state::init_buttons() //so user can roll the dice
{
    this->dice= std::make_unique<Button>(1000, 380, 150, 50, &this->font, "Roll Dice",
    sf::Color(70,70,70,200));
}

void game_state::end_turn_option() //called when user has no other options then end turn->allows them time to buy houses/think
{
    end_turn=true;
    player_vector[player_incriment]->update_chance(false);
}



//public functions

void game_state::end_state(){std::cout<<"ending game state"<<std::endl;}

void game_state::if_double_roll() //allows player to re-roll
{
    if(double_roll==true)
    {
        player_incriment--;
        double_roll=false;
    }
}
std::vector<int> game_state::check_owners(std::vector<std::shared_ptr<properties>> group) //check owners of one property group
{
    int number_in_group=group.size();
    std::vector<int> properties_available;

    int total_properties=0;
    int properties_checked=0; //make sure all properties are owned by same player
    int failed=0; //if one 'fails', not owned by the same player then cant buy houses

    for(int i=0; i<number_in_group;i++)
    {
        total_properties++;
        if(i+1<=number_in_group-1){
            //checks if each property is owned by the same player
            if(dynamic_cast<buyable_properties *>(group[i].get())->return_player_owner() == dynamic_cast<buyable_properties *>(group[i+1].get())->return_player_owner() 
            && dynamic_cast<buyable_properties *>(group[i].get())->is_owned()==true && dynamic_cast<buyable_properties *>(group[i+1].get())->is_owned()==true)
            {
                properties_checked++;
                if(player_incriment == dynamic_cast<buyable_properties *>(group[i].get())->return_player_owner() && total_properties==properties_checked && failed==0 && i==number_in_group-2)
                {
                        for(int x=0;x<number_in_group;x++)
                        {
                            properties_available.push_back(group[x]->return_int_position()); //adds all properties that houses can be bought so they can be clicked

                            all_owned=true;
                            for(int i=0; i<number_in_group;i++)
                            {
                                dynamic_cast<buyable_properties *>(group[i].get())->update_all_owned();
                            }
                        }
                }   
            } else{
                failed++;
            }
        }
    }
    return properties_available;
}

void game_state::update()
{
    //make sure incriment does not go over number of players othewwise when used as
    //an index for player_vector it will give a range error
    if(player_incriment>=number_of_players)
    {
        player_incriment=0;
    }

    //updates each player to check if they have less than 0 money
    for(int i=0; i<number_of_players;i++)
    {
        this->player_vector[i]->update_bankrupt();
    }

    //if a player is bankrupt, skip there go and change numbers of players left
    if(this->player_vector[player_incriment]->return_bankrupt()==true)
    {
        std::cout<<"Player "<<player_incriment+1<< " is bankrupt!"<<std::endl;
        player_incriment++;
        option=true;
    }

    //after updating which players turn it is display whos turn it is
    info<<"Player "<<player_incriment+1<<" turn";
    this->game_information->update_turn(info.str());
    info.str("");

    //update number of players left
    number_of_players_left=0;
    for(int i=0; i<number_of_players;i++)
    {
        if(this->player_vector[i]->return_bankrupt()==false)
        {
            number_of_players_left++;
        }
    }

    //if only one player is left then end the game, close the window
    if(number_of_players_left<=1 && game_over==false)
    {
        this->game_over=true;
        std::cout<<"GAME OVER!"<<std::endl;
        this->game_information->update("GAME OVER");
        
        for(int i=0; i<number_of_players;i++)
        {
            if(this->player_vector[i]->return_bankrupt()==false)
            {
                std::cout<<player_vector[i]->return_name()<<" has won"<<std::endl;

                info<<player_vector[i]->return_name()<<" has won"<<std::endl;
                this->game_information->update(info.str());
                info.str("");

                player_incriment = 0; 
            }
        }

        std::cout<<"Press escape or close window to exit game"<<std::endl;
        this->game_information->update("Press escape or close window to exit game");
    }

    //if player owns all of on house colour, makes sure only ran once per turn
    if(option==true){
        properties_available.resize(number_of_players, std::vector<int>(37));//properties available for purchase
        for(int i=0;i<property_groups.size();i++)//option to buy house after dice rolled on their turn
        {
            check_owners(property_groups[i]);//checks each group
            //if owner of property the same player
            if(all_owned==true){
                std::cout<<"you can buy houses"<<std::endl;//try specify color
                this->game_information->update("you can buy houses");
                for(int x=0; x<property_groups[i].size(); x++)
                {
                    properties_available[player_incriment][check_owners(property_groups[i])[x]] = check_owners(property_groups[i])[x];
                    option=false;
                }
            all_owned=false;
            }
        }

        for(int i =0; i<properties_available[player_incriment].size();i++) 
        {
            if(properties_available[player_incriment][i]!=0){
                this->buy_houses=true;
                //std::cout<<"prop"<<properties_available[player_incriment][i]<<std::endl;
            }
        }
    }

    //button updates
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || player_vector[player_incriment]->return_chance()==true)//bypass mouse click after chance to give option to buy/pay owner
    {
        //get mouse position in window
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
        sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
            static_cast<float>(mouse_pos.y));

        //update position of mouse in button class
        this->dice->update(mouse_pos_f);

        if(dice->isPressed()==true || player_vector[player_incriment]->return_chance()==true) //bypass rolling dice when rolled on chance
        {
            this->dice->remove_button(); //remove dice so the player has to make decision to buy/pass/end turn
            
            if(player_vector[player_incriment]->return_chance()==false){//if rolled on chnace dont reroll
                std::cout<<"Dice rolled!"<<std::endl;
                this->game_information->update("Dice rolled!");

                std::random_device rd;//obtain random number from hardware
                std::mt19937 gen(rd());// A Mersenne Twister pseudo-random generator of 32 bit numbers
                std::uniform_int_distribution<> distr1(1, 6); //define range
                std::uniform_int_distribution<> distr2(1, 6); 

                //randomlly generate two numbers fo the dice roll
                dice1=distr1(gen); 
                dice2=distr2(gen);
                //can manipulate dice rolls to test functionality
                //dice1 = 0;
                //dice2 = 1;

                //output the dice rolls
                std::cout<<dice1<<" "<<dice2<<std::endl;
                info<<"You rolled a "<<dice1<<" and a "<<dice2;
                this->game_information->update(info.str());
                info.str("");

                //if double roll
                if(dice1==dice2)
                {
                    std::cout<<"double rolled"<<std::endl;
                    this->game_information->update("Double rolled!");
                    double_roll=true;

                    //get out jail if in jail
                    if(player_vector[player_incriment]->return_jailed()==true){
                        this->player_vector[player_incriment]->update_out_of_jail();
                        std::cout<<"Double rolled, out of Jail"<<std::endl;
                        this->game_information->update("Double rolled, out of Jail!");
                    }

                    this->number_of_double_rolls++; //in a row

                }else{
                    this->number_of_double_rolls=0; //not in a row
                }
            }

            //skips players turn if in jail
            if(player_vector[player_incriment]->return_jailed()==false)
            {

                //if three doubles rolled in a row then jail
                if(number_of_double_rolls==3){
                    player_vector[player_incriment]->update_into_jail();
                    this->player_vector[player_incriment]->update_position(10-(player_position));//go to jail position
                    number_of_double_rolls=0;
                }else{
                    if(player_vector[player_incriment]->return_chance()==false)
                        this->player_vector[player_incriment]->update_position((dice1+dice2));
                }

                //Player get money for passing go
                if(this->player_vector[player_incriment]->has_passed_go()==true && player_vector[player_incriment]->return_position()!=0)
                {
                    dynamic_cast<special_property *>(this->properties_vec[0].get())->passed(this->player_vector[player_incriment]);
                    
                    this->game_information->update("Player passed go, get $200");
                    this->scores->update(player_incriment+1, (this->player_vector[player_incriment]->return_money()));
                    this->player_vector[player_incriment]->update_passes_go();
                }

                //get players position whilst their turn happens
                player_position = this->player_vector[player_incriment]->return_position();

                //displays what they have landed on, and the functionality that happens
                //if(player_vector[player_incriment]->return_chance()==false) // if landed on chance dont call this
                    this->properties_vec[player_position]->landed_on(player_vector, player_incriment, game_information);
                 //   player_vector[player_incriment]->update_chance(false);//after chance it resets

                //updates scores after they have rolled, if they owned money etc
                this->scores->update(player_incriment+1, (this->player_vector[player_incriment]->return_money()));

                if(this->properties_vec[player_position]->is_property_buyable()==true){ //for all house/train/company properties

                    //if it is owned by a player
                    if(dynamic_cast<buyable_properties*>(this->properties_vec[player_position].get())->is_owned()==true)//dynamic cast converts pointer to classes up/down/along the inheritance hierachy
                    {
                        //what they owe(unless its theirs)
                        this->scores->update(player_incriment+1, player_vector[player_incriment]->return_money());
                        int owner=0; //temp owner store
                        owner=dynamic_cast<buyable_properties *>(this->properties_vec[player_position].get())->return_player_owner();

                        this->scores->update(owner+1, player_vector[owner]->return_money());

                        this->end_turn_option(); //when the player has nothing more to do it presents the option to end their turn

                        std::cout<<"--------------"<<std::endl;
                    }else if(dynamic_cast<buyable_properties *>(this->properties_vec[player_position].get())->is_owned()==false){
                        //give option to buy because it is not owned
                        std::cout<<"you can buy me"<<std::endl;
                        std::cout<<"costs: "<<dynamic_cast<buyable_properties *>(properties_vec[player_position].get())->return_price()<<std::endl;
                        is_buyable=true; //can now render buy buttons

                        info<<"You can buy this property. Costs: "<<dynamic_cast<buyable_properties *>(this->properties_vec[player_position].get())->return_price();
                        this->game_information->update(info.str());
                        info.str("");

                        player_vector[player_incriment]->update_chance(false);//after chance it resets
                    }
                }else if(this->properties_vec[player_position]->is_property_buyable()==false){ //for all other properties

                    int temp_pos = player_position;

                    if(temp_pos !=7 && temp_pos!=22)//if previously landed on chance don't show end button
                        this->end_turn_option();

                    temp_pos=0;
                }
            }else{
                //if in jail make sure they get out in three turns
                player_vector[player_incriment]->update_turns_in_jail();
                if(player_vector[player_incriment]->return_turns_in_jail()==3){
                    this->game_information->update("3 turns in Jail, free next turn");
                    std::cout<<"3 turns in Jail, free next turn"<<std::endl;
                }
                this->end_turn_option();
            }
        }
        if(is_buyable==true){
            //create buttons
            std::unique_ptr<Button> buy_btn(new Button(1000, 455, 150, 50, &this->font, "Buy property",
            sf::Color(70,70,70,200)));
            std::unique_ptr<Button> pass_btn(new Button(1000, 530, 150, 50, &this->font, "Pass Property",
            sf::Color(70,70,70,200)));
            //get position when pressed
            buy_btn->update(mouse_pos_f);
            pass_btn->update(mouse_pos_f);
            if(buy_btn->isPressed()==true)
            {
                //Buyer has to have enough money
                if((this->player_vector[player_incriment]->return_money())>=(dynamic_cast<buyable_properties *>(this->properties_vec[player_position].get())->return_price()))
                {
                    //marker to show which player bought it on the property
                    std::cout<<"Bought!!"<<std::endl;

                    //these properties have effects when multiples of one type are bought (like houses)
                    if(properties_vec[player_position]->return_int_position()== 5 || properties_vec[player_position]->return_int_position()== 15
                        || properties_vec[player_position]->return_int_position()== 25 || properties_vec[player_position]->return_int_position()== 35)//sus
                    {
                        player_vector[player_incriment]->update_train_stations();
                    }

                    if(properties_vec[player_position]->return_int_position()==12 || properties_vec[player_position]->return_int_position()==28)
                    {
                        player_vector[player_incriment]->update_companies();
                    }

                    //gives property an owner
                    dynamic_cast<buyable_properties *>(this->properties_vec[player_position].get())->update_owned(this->player_vector[player_incriment]);
                    this->game_information->update("Bought!");

                    //deduct price of property from player
                    this->player_vector[player_incriment]->update_money(-(dynamic_cast<buyable_properties *>(this->properties_vec[player_position].get())->return_price()));
                    std::cout<<this->player_vector[player_incriment]->return_name()<<" budget: "<< this->player_vector[player_incriment]->return_money()<<std::endl;
                    is_buyable=false;
                    this->scores->update(player_incriment+1, player_vector[player_incriment]->return_money()); //updae leaderboard
                    
                    for(int i=0;i<property_groups.size();i++)//makes sure as soon as player buys the next person to land pays new price
                    {
                        int length =0;
                        length = (property_groups[i]).size();

                        if(length==2)
                        {
                            if(dynamic_cast<buyable_properties *>((property_groups[i])[0].get())->return_player_owner()==player_incriment && dynamic_cast<buyable_properties *>((property_groups[i])[1].get())->return_player_owner()==player_incriment
                            && dynamic_cast<buyable_properties *>((property_groups[i])[0].get())->return_player_owner()>=0)
                            {
                                dynamic_cast<buyable_properties *>((property_groups[i])[0].get())->update_all_owned();
                                dynamic_cast<buyable_properties *>((property_groups[i])[1].get())->update_all_owned();
                            }
                        }else if(length==3){    
                            if(dynamic_cast<buyable_properties *>((property_groups[i])[0].get())->return_player_owner()==player_incriment && dynamic_cast<buyable_properties *>((property_groups[i])[1].get())->return_player_owner()==player_incriment
                            && dynamic_cast<buyable_properties *>((property_groups[i])[2].get())->return_player_owner()==player_incriment && dynamic_cast<buyable_properties *>((property_groups[i])[0].get())->return_player_owner()>=0)
                            {
                                dynamic_cast<buyable_properties *>((property_groups[i])[0].get())->update_all_owned();
                                dynamic_cast<buyable_properties *>((property_groups[i])[1].get())->update_all_owned();
                                dynamic_cast<buyable_properties *>((property_groups[i])[2].get())->update_all_owned();
                            }
                        }
                    }
                    
                    this->end_turn_option();

                }else{
                    std::cout<<"Cannot afford property"<<std::endl;
                    this->game_information->update("Cannot afford property");
                }
            }else if(pass_btn->isPressed()==true){
                //if player doesnt want the property
                std::cout<<"Passed"<<std::endl;
                this->game_information->update("Passes property");
                is_buyable=false;
                
                std::cout<<this->player_vector[player_incriment]->return_name()<<" budget: "<< this->player_vector[player_incriment]->return_money()<<std::endl;
                std::cout<<"--------------"<<std::endl;

                this->end_turn_option();
            }
        }
        if(buy_houses==true){ //if player has option to buy houses
            
            for(int i =0; i<properties_available[player_incriment].size();i++)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
                sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x),
                static_cast<float>(mouse_pos.y));
                
                if(properties_available[player_incriment][i]!=0){ //property has to be in the list of houses to buy
                    if(properties_vec[i]->return_shape().getGlobalBounds().contains(mouse_pos_f)) //if player presses on property
                    {
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            //player has enough money for house
                            if(this->player_vector[player_incriment]->return_money()>=dynamic_cast<color_properties *>(properties_vec[i].get())->return_house_price()){
                                if(dynamic_cast<color_properties *>(properties_vec[i].get())->house_bought()==true){ //buy a house
                                    std::cout<<"House bought on "<<properties_vec[i]->get_name()<<std::endl;
                                    info<<"House bought on "<<properties_vec[i]->get_name();
                                    this->game_information->update(info.str());
                                    info.str("");
                                    player_vector[player_incriment]->update_money(-(dynamic_cast<color_properties *>(properties_vec[i].get())->return_house_price()));                                 
                                    this->scores->update(player_incriment+1, player_vector[player_incriment]->return_money());
                                }
                            }else{
                                std::cout<<"Cannot afford house"<<std::endl;
                                this->game_information->update("Cannot afford house");
                            }
                        }
                    }
                }
            }
        }
        if(end_turn==true){ //at the end of their go end button is created
            std::unique_ptr<Button> end_turn_btn(new Button(1000, 605, 150, 50, &this->font, "End Turn",
            sf::Color(70,70,70,200)));

            end_turn_btn->update(mouse_pos_f);
            if(end_turn_btn->isPressed()==true && game_over==false)
            {
                //next players go and resets all the booleans used to run the code as intended
                end_turn=false;

                std::cout<<"--------------"<<std::endl;
                player_incriment++;
                this->if_double_roll();

                buy_houses=false;
                option=true;
                this->dice->return_button();
            }
        }
    }
}
   
void game_state::render(sf::RenderTarget* target)
{
    if(!target)
        target = this->window;

    //render background
    target->draw(this->board);
    target->draw(this->background);

    //render each player
    for(int i=0; i<number_of_players;i++){
        this->player_vector[i]->render(target);
    }

    //render dice
    this->dice->render(target);

    //only render property buttons when the option to buy is pressent
    if(this->is_buyable==true)
    {
        std::unique_ptr<Button> buy_btn(new Button(1000, 455, 150, 50, &this->font, "Buy property",
        sf::Color(70,70,70,200)));
        std::unique_ptr<Button> pass_btn(new Button(1000, 530, 150, 50, &this->font, "Pass Property",
        sf::Color(70,70,70,200)));
        buy_btn->render(target);
        pass_btn->render(target);
    }

    //only render end turn button when player has finsihed their move
    if(end_turn==true){
        std::unique_ptr<Button> end_turn_btn(new Button(1000, 605, 150, 50, &this->font, "End Turn",
        sf::Color(70,70,70,200)));
        end_turn_btn->render(target);
    }

    //render game info
    this->scores->render(target);
    this->game_information->render(target);

    //renders owners of the house (coloured line underneath property to show ownsership)
    //and render houses when bought
    for(int i =0; i<40; i++)
    {
        if(i!=0 && i!=10 && i!=20 && i!=30 && i!=2 && i!=7 && i!=17 && i!=22 && i!=33 && i!=36 && i!=4 && i!=38){ //only on buyable properties
            dynamic_cast<buyable_properties *>(this->properties_vec[i].get())->render_house_owner(target);
            
            //houses
            if(i!=5 && i!=15 && i!=25 && i!=35 //not train stations
            && i!=12 && i!=28) //not companies
                dynamic_cast<color_properties *>(this->properties_vec[i].get())->render_houses(target);
        }
        properties_vec[i]->render_position_boxes(target);
    } 
}
