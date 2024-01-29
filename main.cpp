#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <vector>

int main()
{
    const uint16_t SCREEN_WIDTH = 1920;
    const uint16_t SCREEN_HEIGHT = 1080;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "52");  // sf::Style::Fullscreen

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);


    //grid
    static float gridSizeF = 50.f;
    static unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    float viewSpeed = 300.f;
    float dt = 0.f;
    sf::Clock dtClock;

    //init game elements
    sf::CircleShape shape(1000.f);
    sf::RectangleShape rect_shape(sf::Vector2f(gridSizeF, gridSizeF));
    rect_shape.setPosition(100.f,100.f);
    shape.setFillColor(sf::Color::Green);


    const int mapSize = 100;
    std::vector<std::vector<sf::RectangleShape>> tileMap;
    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

    for (int x = 0; x < mapSize; x++)
    {
        tileMap[x].resize(mapSize, sf::RectangleShape());
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineThickness(2.f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
        }
        
    }

    int fromX = 0;
    int fromY = 0;
    int toX = 0;
    int toY = 0;

    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineColor(sf::Color::Blue);
    tileSelector.setOutlineThickness(2.f);
    

    // sf::RectangleShape rectangle(sf::Vector2f(200.0f, 100.0f));
    // rectangle.setFillColor(sf::Color::Red);
    // rectangle.setPosition(window.getSize().x/2.f, window.getSize().y/2.f);

    //view = camera
    sf::View view;
    // view.setSize(window.getSize().x, window.getSize().y);
    // view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    //mouse
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;
    sf::Font font;
    font.loadFromFile("Dosis-VariableFont_wght.ttf");
    sf::Text text;
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");

    sf::Vector2f prevMousePos;
    sf::Vector2f currMousePos;

    while (window.isOpen())
    {
        //update dt
        dt = dtClock.restart().asSeconds();

        //update view
        view.setSize(window.getSize().x, window.getSize().y);

        //update mouse pos
        prevMousePos = currMousePos;
        currMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.f)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if(mousePosView.y >= 0.f)
            mousePosGrid.y = mousePosView.y / gridSizeU;
        window.setView(window.getDefaultView());

        //update game elements
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        //update ui
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";


        text.setString(ss.str());

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                // view.setCenter(localPosition.x, localPosition.y);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                view.move(-viewSpeed * dt, 0.f);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                view.move(viewSpeed * dt, 0.f);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // currMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                view.move((prevMousePos.x - currMousePos.x), 
                            (prevMousePos.y - currMousePos.y));
                prevMousePos = currMousePos;
            }

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            

        }
        //render
        window.clear();
        
        //render game elements
        window.setView(view);
        // window.draw(rect_shape);

        fromX = view.getCenter().x / gridSizeF - 7;
        toX = view.getCenter().x / gridSizeF + 7;
        fromY = view.getCenter().y / gridSizeF  - 7;
        toY = view.getCenter().y / gridSizeF + 7;

        if(fromX < 0)
            fromX = 0;
        else if(fromX >= mapSize)
            fromX = mapSize - 1;
        if(fromY < 0)
            fromY = 0;
        else if(fromY >= mapSize)
            fromY = mapSize - 1;

        if(toX < 0)
            toX = 0;
        else if(toX >= mapSize)
            toX = mapSize - 1;
        if(toY < 0)
            toY = 0;
        else if(toY >= mapSize)
            toY = mapSize - 1;
       
        for (int x = fromX; x < toX; x++)
        {
            for (int y = fromY; y < toY; y++)
            {
                window.draw(tileMap[x][y]);
            }
        }
        // window.draw(rectangle);
        window.draw(tileSelector);
        // window.setView(window.getDefaultView());
        sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
        window.setView(sf::View(visibleArea));

        //render ui
        window.draw(text);
        window.display();
    }

    return 0;
}