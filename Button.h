#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Button
{
    private:
        //registers button click
        bool pressed = false;

        //button design
        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;
        sf::Color colour;
        float Width;
        float Height;

    public:
        Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color colour)
        {
            //initalise button design
            this->shape.setPosition(sf::Vector2f(x,y));
            this->shape.setSize(sf::Vector2f(width, height));
            this->colour = colour;
            this->shape.setFillColor(this->colour);
            this->Width=width;
            this->Height=height;

            //initalise button text
            this->font = font;
            this->text.setFont(*this->font);
            this->text.setString(text);
            this->text.setFillColor(sf::Color::White);
            this->text.setCharacterSize(12);
            //centre of button, position is a float
            this->text.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f) - this->text.getGlobalBounds().width/2.f,
                    this->shape.getPosition().y + (this->shape.getGlobalBounds().height/2.f) - this->text.getGlobalBounds().height/2.f);
        };
        ~Button(){};

        //functions
        bool isPressed(); //returns true if clicked

        //this is for the dice button
        void remove_button();
        void return_button();
 
        void update(const sf::Vector2f mousePos);

        void render(sf::RenderTarget* target);
};