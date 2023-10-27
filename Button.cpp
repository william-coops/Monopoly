#include "Button.h"

//public functions
bool Button::isPressed()
{
    if(this->pressed==true)
    {
        return true;
        
    }else
        return false;
}
void Button::remove_button()
{
    this->shape.setSize(sf::Vector2f(0,0));
}
void Button::return_button()
{
    this->shape.setSize(sf::Vector2f(Width,  Height));
}
void Button::update(const sf::Vector2f mousePos)
{
    this->pressed=0;
    //mouse on top of the button shape
    if(this->shape.getGlobalBounds().contains(mousePos))
    {
        //pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->pressed=true;
        }
    }
}
void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}