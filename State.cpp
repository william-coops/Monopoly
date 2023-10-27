#include "State.h"

//private function
void state::init_font()
{
    if(!this->font.loadFromFile("OpenSans-Light.ttf"))
        std::cout<<"Error font could not be loaded"<<std::endl;
}

//public function
const bool& state::get_quit() const{return this->quit;}