#pragma once //source file is only included once in a single compliation

#include "GameState.h"
#include "MenuState.h"

//game engine
class game
{   
    private:
        //SFML classes 

        sf::RenderWindow* window; //A window that is a target for 2D drawing
        sf::VideoMode videomode; //dimensions, resolution of window

        sf::Event ev; //Defines a system event

        //stack of states to hold menu and game states
        std::stack<std::unique_ptr<state>> states;

        //private functions
        //init stands for inisalisation
        void init_window();
        void init_states();

    public:
        game()
        {
            this->init_window();
            this->init_states();
        }; //constructor
        virtual ~game()
        {
            delete this->window;
            while(!this->states.empty())
            {
                this->states.top()->end_state();
                this->states.pop();
            }
        }; //destructor

        //functions

        void poll_events(); //checks for window closure, escape pressed etc

        void update(); //updates the top of stack state

        void render(); //renders the top of stack state

        void run(); //calls update and render^ whilst window us open

};