#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Environment.hpp"
#include "config.hpp"

int main()
{
    /* GENERAL CONFIGURATION */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(config::screenX, config::screenY), config::title, sf::Style::Default, settings);

    /* OBJECTS CREATION */

    // 400 ants max for 60 fps
    Environment Environment(config::antsNumber);

    /* VIEWS */
    sf::View view(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(window.getSize()));

    /* DECLARATIONS */
    float fps;
    std::vector<float> fpsAvargeV;
    float fpsAvarge;

    /* NORMAL LOOP */
    sf::Clock clock;
    float dt;


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
        }

        /* LOGIC UPDATES */
        // view movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(-config::cameraSpeed * dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(config::cameraSpeed * dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            view.move(0.f, -config::cameraSpeed * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            view.move(0.f, config::cameraSpeed * dt);
        }

        Environment.update(dt, window);

        /* VIEW THINGS */
        window.clear();
        window.setView(view);

        // DRAW HEARE
        Environment.draw(window);

        // END DRAW
        window.display();

        /* EXTRA THINGS */
        // FPS and DeltaTime
        float currentTime = clock.restart().asSeconds();
        fps = 1.f / currentTime;
        dt = currentTime * config::timeSpeed;

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