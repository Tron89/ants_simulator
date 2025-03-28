#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Environment.hpp"
#include "config.hpp"
#include "Input.hpp"

int main()
{

    /* GENERAL CONFIGURATION */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(config::screenX, config::screenY), config::title, sf::Style::Default, settings);

    if(config::fpsLimit != 0){
        window.setFramerateLimit(config::fpsLimit);
    }

    /* OBJECTS CREATION */
    Environment environment;


    /* VIEWS */
    sf::View view(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(window.getSize()));

    /* DECLARATIONS */
    float fps;
    std::vector<float> fpsAvargeV;
    float fpsAvarge;

    /* NORMAL LOOP */
    sf::Clock clock;

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
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta == -1)
                {
                    view.zoom(1.25f);
                }
                if (event.mouseWheel.delta == 1)
                {
                    view.zoom(0.75f);
                }
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }

        }

        /* LOGIC UPDATES */

        Input::update(window, view, environment);


        environment.update(window);

        /* VIEW THINGS */
        window.clear();
        window.setView(view);

        // DRAW HEARE
        environment.draw(window);

        // END DRAW
        window.display();

        /* EXTRA THINGS */
        // FPS and DeltaTime
        float currentTime = clock.restart().asSeconds();
        fps = 1.f / currentTime;
        config::dt = currentTime * config::timeSpeed;

        fpsAvargeV.push_back(fps);

        if (fpsAvargeV.size() >= 60)
        {
            float lastFps = 0;
            float fpss = 0;
            for (float fps2 : fpsAvargeV)
            {
                fpss += lastFps;
                lastFps = fps2;
            }
            fpsAvarge = fpss / 60;
            fpsAvargeV.clear();
        }

        // OUTPUT
        if (config::passConsole)
        {
            std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                      << std::endl;
        }

        if (config::seeFPS)
        {
            std::cout << fpsAvarge << std::endl;
        }
    }

    return 0;
}