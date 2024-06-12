#include <iostream>
#include <SFML/Graphics.hpp>
#include "test.hpp"
#include "Ant.hpp"

int main()
{
    std::cout << "holaaa" << std::endl;
    /* GENERAL CONFIGURATION */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!", sf::Style::Default, settings);
    window.setTitle("BREAD");
    
    /* OBJECTS CREATION */

    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(-1.f);
    shape.setOutlineColor(sf::Color(250, 250, 250));

    sf::CircleShape tile = Tile().getTile();

    sf::RectangleShape line(sf::Vector2f(80.f,80.f));
    line.setPosition(100,100);


    /* VIEWS */
    sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));



    /* NORMAL LOOP */
    window.setFramerateLimit(60);

    int speed = 5;

    while (window.isOpen())
    {
        
        /* EVENT LOOP */
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // catch the resize events
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                view.setSize(event.size.width, event.size.height);
            }

            // zoom the view in or out
            if (event.type == sf::Event::MouseWheelMoved){
                if (event.mouseWheel.delta == -1){
                    view.zoom(1.5f);
                }
                if (event.mouseWheel.delta == 1){
                    view.zoom(0.5f);
                }
            }

        }
        
        /* MOVMENT */

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            tile.move(-1.f * speed, 0.f);
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            tile.move(1.f * speed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            tile.move(0.f, -1.f * speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            tile.move(0.f, 1.f * speed);
        }


        // view movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(-1.f * speed, 0.f);
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(1.f * speed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            view.move(0.f, -1.f * speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            view.move(0.f, 1.f * speed);
        }

        
        window.clear();
        window.setView(view);
        // DRAW HEARE
        
        // draw something to that view
        window.draw(tile);
        window.draw(line);
        window.draw(shape);
        
        // END DRAW
        window.display();

    }

    return 0;
}