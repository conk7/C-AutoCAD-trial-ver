#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <vector>
#include <math.h>

void draw_axes(sf::RenderWindow &window, sf::View const &view, unsigned const gridSize)
{
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    float viewLeftBorder = viewCenter.x - (viewSize.x / 2);
    float gridLeftBorder = floor(viewLeftBorder / gridSize) * gridSize;
    float viewRightBorder = viewCenter.x + (viewSize.x / 2);
    float gridRightBorder = ceil(viewRightBorder / gridSize) * gridSize;
    float viewTopBorder = viewCenter.y - (viewSize.y / 2);
    float gridTopBorder = ceil(viewTopBorder / gridSize) * gridSize;
    float viewBottomBorder = viewCenter.y + (viewSize.y / 2);
    float gridBottomBorder = floor(viewBottomBorder / gridSize) * gridSize;
    
    float gridIdx = gridLeftBorder;

    while (gridIdx < gridRightBorder)
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);
        line.setPosition(gridIdx, gridTopBorder - gridSize);
        line.setSize(sf::Vector2f(1, viewSize.y + gridSize));
        window.draw(line);
        gridIdx += gridSize;
    }

    gridIdx = gridBottomBorder;
    while (gridIdx >= gridTopBorder)
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);
        line.setPosition(gridLeftBorder - gridSize, gridIdx);
        line.setSize(sf::Vector2f(viewSize.x + gridSize * 2, 1));
        window.draw(line);
        gridIdx -= gridSize;
    }

    if(gridBottomBorder > 0 && gridTopBorder < 0)
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);
        line.setPosition(gridLeftBorder - gridSize, 0);
        line.setSize(sf::Vector2f(viewSize.x + gridSize * 2, 3));
        window.draw(line);
        gridIdx += gridSize;
    }

    if(gridRightBorder > 0 && gridLeftBorder < 0)
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);
        line.setPosition(0, gridTopBorder - gridSize);
        line.setSize(sf::Vector2f(3, viewSize.y + gridSize));
        window.draw(line);
        gridIdx += gridSize;
    }

}

int main()
{
    //default width and height of the window
    const uint16_t SCREEN_WIDTH = 1920;
    const uint16_t SCREEN_HEIGHT = 1080;

    //creating and configuring the window
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

    // const int mapSizeX = window.getSize().x / gridSizeU + 3;
    // const int mapSizeY = window.getSize().y / gridSizeU + 3;
    // std::vector<std::vector<sf::RectangleShape>> tileMap;
    // tileMap.resize(mapSizeX, std::vector<sf::RectangleShape>());

    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                        static_cast<float>(window.getSize().y))); //полнейшая хуетень but works

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
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);

    sf::Vector2i prevMousePos;
    sf::Vector2i currMousePos;

    while (window.isOpen())
    {
        //update dt
        dt = dtClock.restart().asSeconds();

        //update view
        view.setSize(window.getSize().x, window.getSize().y);

        //update mouse pos
        prevMousePos = currMousePos;
        currMousePos = sf::Mouse::getPosition(window);

        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.f)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if(mousePosView.y >= 0.f)
            mousePosGrid.y = mousePosView.y / gridSizeU;
        window.setView(window.getDefaultView());

        sf::Vector2i negmousePosGrid;
        negmousePosGrid.x = mousePosView.x / gridSizeU;
        negmousePosGrid.y = mousePosView.y / gridSizeU;

        //update game elements
        // tileSelector.setPosition(mousePosGrid.x * gridSizeF, 
                                    // mousePosGrid.y * gridSizeF); //old tile selecton
        if(negmousePosGrid.x >= 0 && negmousePosGrid.y >= 0)
        {
            tileSelector.setPosition(negmousePosGrid.x * gridSizeF, 
                                    negmousePosGrid.y * gridSizeF); //new tile selection that works incorrectly
        }                                                        //with negative values
        else if(negmousePosGrid.x < 0 && negmousePosGrid.y >= 0)
        {
            tileSelector.setPosition(negmousePosGrid.x * gridSizeF - gridSizeF, 
                                    negmousePosGrid.y * gridSizeF);
        }
        else if(negmousePosGrid.x > 0 && negmousePosGrid.y < 0)
        {
            tileSelector.setPosition(negmousePosGrid.x * gridSizeF, 
                                    negmousePosGrid.y * gridSizeF - gridSizeF);
        }
        else if(negmousePosGrid.x < 0 && negmousePosGrid.y < 0)
        {
            tileSelector.setPosition(negmousePosGrid.x * gridSizeF - gridSizeF, 
                                    negmousePosGrid.y * gridSizeF - gridSizeF);
        }


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
                view.move((prevMousePos.x - currMousePos.x), 
                            (prevMousePos.y - currMousePos.y));
                // prevMousePos = currMousePos;
            }          

        }

        //render begins
        window.clear();

        sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
        window.setView(sf::View(visibleArea));
        window.draw(background);
        
        //render game elements
        window.setView(view);
       
        draw_axes(window, view, gridSizeU);
        
        window.draw(tileSelector);
        // window.setView(window.getDefaultView());
        // sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
        window.setView(sf::View(visibleArea));

        //render ui
        window.draw(text);
        window.display();
        //render ends
    }

    return 0;
}