#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "..\include\grid.hpp"
#include <math.h>

void updateMousePos(sf::Vector2i &prevMousePos,sf::Vector2i &currMousePos, sf::View const &view)
{
    prevMousePos = currMousePos;
    currMousePos = sf::Mouse::getPosition() ;
}

int main()

{
    //default window width and height
    const uint16_t SCREENW = 1920;
    const uint16_t SCREENH = 1080;

    //creating and configuring the window
    sf::RenderWindow window(sf::VideoMode(SCREENW, SCREENH), "52");  // sf::Style::Fullscreen
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    
    //grid
    Grid grid(100.f);

    //init game elements
    sf::CircleShape shape(1000.f);
    sf::RectangleShape rect_shape(sf::Vector2f(grid.getGridSizeF(), grid.getGridSizeF()));
    rect_shape.setPosition(100.f,100.f);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                        static_cast<float>(window.getSize().y))); //полнейшая хуетень

    //view
    sf::View view;
    view.setCenter(0,0);

    //mouse
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    sf::Vector2i prevMousePos;
    sf::Vector2i currMousePos;

    //debug info
    sf::Font font;
    font.loadFromFile("misc/Dosis-VariableFont_wght.ttf");
    sf::Text text;
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);


    sf::RectangleShape tileSelector(sf::Vector2f(grid.getGridSizeF(), grid.getGridSizeF()));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineColor(sf::Color::Blue);
    tileSelector.setOutlineThickness(3);

    //zoom
    const float zoomDiff = 0.1;
    float currZoom = 1;
    // sf::View visibleArea(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    // visibleArea.zoom(0.5);
    // // visibleArea.setSize(sf::Vector2f(1920, 1080));
    // visibleArea.setViewport(sf::FloatRect(0, 0, 1, 1));
    // visibleArea.setCenter(visibleArea.getSize().x/2, visibleArea.getSize().y/2);
    // // visibleArea.setCenter(0,0);

    //main loop
    while (window.isOpen())
    {
        //update view
        view.setSize(window.getSize().x/currZoom, window.getSize().y/currZoom);

        //update bg
        background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                            static_cast<float>(window.getSize().y)));
        // background.setPosition(sf::Vector2f(window.getPosition().x,
        //                         window.getPosition().y));

        //update mouse pos
        updateMousePos(prevMousePos, currMousePos, view);

        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        // if(mousePosView.x >= 0.f)
        mousePosGrid.x = mousePosView.x / grid.getGridSizeU();
        // if(mousePosView.y >= 0.f)
        mousePosGrid.y = mousePosView.y / grid.getGridSizeU();
        window.setView(window.getDefaultView());

        //update ui
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
        text.setString(ss.str());

        //event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                view.move((prevMousePos.x - currMousePos.x), 
                            (prevMousePos.y - currMousePos.y));
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0 && currZoom < 2)
                {
                    currZoom += zoomDiff;           
                }

                else if (event.mouseWheelScroll.delta < 0 && currZoom > 0.5)
                    currZoom -= zoomDiff;
            }
            // else if(sf::Event::MouseButtonReleased)
            // {
                
            // }
                 
        }

        sf::Vector2i negmousePosGrid;
        negmousePosGrid.x = floor(mousePosView.x / grid.getGridSizeU());
        negmousePosGrid.y = floor(mousePosView.y / grid.getGridSizeU());

        tileSelector.setPosition(negmousePosGrid.x * grid.getGridSizeF(), 
                                negmousePosGrid.y * grid.getGridSizeF()); //new tile selection that works incorrectly                                                     //with negative values

        //render begins
        window.clear();
        sf::View visibleArea (sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        // visibleArea.setSize(sf::Vector2f(1920/2, 1080/2));
        // visibleArea.zoom(2);
        window.setView(visibleArea);
        window.draw(background);
        
        //render game elements
        window.setView(view);
       
        grid.draw_axes(window, view, currZoom);
        window.draw(tileSelector);
        // window.setView(window.getDefaultView());
        window.setView(visibleArea);

        //render ui
        window.draw(text);

        window.display();
        //render ends
    }

    return 0;
}