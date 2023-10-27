
#include "Game.h"

//private functions

void game::init_window()
{
    this->videomode.height=964;
    this->videomode.width=1300;
    this->window = new sf::RenderWindow(this->videomode, "Monopoly", sf::Style::Titlebar | sf::Style::Close);
    
    this->window->setVerticalSyncEnabled(false);
    this->window->setFramerateLimit(30);
}

void game::init_states()
{
    this->states.push(std::make_unique<game_state>(this->window));
    this->states.push(std::make_unique<menu_state>(this->window));
}

//functions

void game::poll_events()
{
    //event polling
    //if (this->window->waitEvent(this->ev))//this method is less cpu intensice but bugged with this version of SFML
    while(this->window->pollEvent(this->ev))//while we get events from window, we save into event variable we created
    {
        //switch allows a variable to be tested equally against a list of values, value = case
        switch(this->ev.type)//each event has a type, ev comes will all data from that event
        {
            case sf::Event::Closed: //when close button on window pressed it closes
                this->window->close();     //it sends an event with type: close, we have to manually close it
                break;
            case sf::Event::KeyPressed: //in the case a key is pressed
                if(this->ev.key.code == sf::Keyboard::Escape) //checks if its the esc key
                    this->window->close();                      // if true close the window
                break;
        }
    } //this is one frame
}

void game::update()
{
    this->poll_events();
    if(!this->states.empty()){
        this->states.top()->update(); 
        if(this->states.top()->get_quit()){
            this->states.top()->end_state();
            this->states.pop();
        }
    }
    //application end
    else{
        //std::cout<<"Ending Game"<<std::endl;
        this->window->close();
    }
}

void game::render()
{
    //clear window
    this->window->clear();

    //render the top state
    if(!this->states.empty())
        this->states.top()->render(); 

    this->window->display();
}
void game::run()
{
    while(this->window->isOpen())//while game is open keep updating and rendering
    {
        this->update();
        this->render();
    }
}