#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "..\include\grid.hpp"
#include "..\include\shape.hpp"
#include "..\include\line.hpp"
#include <math.h>

void updateMousePosView(sf::Vector2i &prevMousePos,sf::Vector2i &currMousePos, sf::RenderWindow &window, sf::View &view)
{
    prevMousePos = currMousePos;
    // currMousePos = sf::Mouse::getPosition(window);
    currMousePos = sf::Mouse::getPosition(window);
    window.setView(view);
    sf::Vector2f currMousePosF = window.mapPixelToCoords(currMousePos);
    currMousePos = { static_cast<int>(currMousePosF.x), static_cast<int>(currMousePosF.y) };
    window.setView(window.getDefaultView());

}

void updateMousePosWindow(sf::Vector2i &prevMousePos, sf::Vector2i &currMousePos,sf::RenderWindow &window, sf::View& view) 
{
    prevMousePos = currMousePos;
    currMousePos = sf::Mouse::getPosition(window);
    // auto tmpPos = sf::Mouse::getPosition();
    // currMousePos = window.mapCoordsToPixel(sf::Vector2f(static_cast<float>(tmpPos.x), static_cast<float>(tmpPos.y)), view);
}

void zoomView(sf::RenderWindow& window, sf::View& view, int mouseX, int mouseY, float scale)
{
    sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    view.zoom(scale);
    sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
    view.move(offsetCoords);
    window.setView(view);
}

int main()
{
    //default window width and height
    const uint16_t SCREENW = 1920;
    const uint16_t SCREENH = 1080;

    //creating and configuring the window
    sf::RenderWindow window(sf::VideoMode(SCREENW, SCREENH), "52", 7, sf::ContextSettings(24,8,8));  // sf::Style::Fullscreen
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    bool isFullscreen = false;
    
    //grid
    Grid grid(100.f);

    //init game elements
    sf::CircleShape shape(1000.f);
    sf::RectangleShape rect_shape(sf::Vector2f(grid.getGridSizeF()*5, grid.getGridSizeF()*5));
    rect_shape.setPosition(100.f,100.f);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape background;
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                        static_cast<float>(window.getSize().y)));

    //view
    sf::View view;
    view.setCenter(0,0);
    view.setSize(window.getSize().x, window.getSize().y);
    sf::View visibleArea (sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    //mouse
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    sf::Vector2i prevMousePosView;
    sf::Vector2i currMousePosView;
    sf::Vector2i currMousePosWindow;
    sf::Vector2i prevMousePosWindow;

    bool isMouseButtonPressed = false;

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
  
    std::vector<Shape> shapes;

    //zoom
    int counter = 0; 
    const float zoomNumber = 1.05;

    std::vector<sf::CircleShape> toDraw;

    //main loop
    while (window.isOpen())
    {
        //update view
// <<<<<<< dev-conk7
        // view.setSize(window.getSize().x/currZoom, window.getSize().y/currZoom);
        visibleArea.setSize(window.getSize().x, window.getSize().y);
        visibleArea.setCenter(static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y/2));
// =======
        // view.setSize(window.getSize().x/currZoom, window.getSize().y/currZoom);
        // visibleArea.setSize(window.getSize().x, window.getSize().y);
        // visibleArea.setCenter(static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y/2));
// >>>>>>> Pablo-

        //update bg
        background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                            static_cast<float>(window.getSize().y)));
        // background.setPosition(sf::Vector2f(window.getPosition().x,
        //                         window.getPosition().y));

        //update mouse pos
        updateMousePosView(prevMousePosView, currMousePosView, window, view);
        updateMousePosWindow(prevMousePosWindow, currMousePosWindow, window, view);

        if(shapes.size() > 0)
        {
            shapes[shapes.size() - 1].updateDE(currMousePosView);
        }

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
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
            << "CurrMousePos: " << currMousePosView.x << " " << currMousePosView.y << "\n";
        // text.setString(ss.str());

        //event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                isMouseButtonPressed = false;
                view.move((prevMousePosWindow.x - currMousePosWindow.x), 
                          (prevMousePosWindow.y - currMousePosWindow.y));
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                isMouseButtonPressed = true;
            }
            if(isMouseButtonPressed && event.type == sf::Event::MouseButtonReleased) //triggers on any mouse button
            {

                if(shapes.size() == 0)
                {
                    Shape shape(3);
                    shape.addVert(currMousePosView);
                    shapes.push_back(shape);
                }
                else if (shapes.size() != 0 && !shapes[shapes.size() - 1].isFinished())
                {
                    shapes[shapes.size() - 1].addVert(currMousePosView);
                    auto edges = shapes[shapes.size() - 1].getEdges();
                    ss << edges.size();
                }
                else if (shapes.size() != 0 && shapes[shapes.size() - 1].isFinished())
                {
                    Shape shape(3);
                    shape.addVert(currMousePosView);
                    shapes.push_back(shape);
                }
                // else
                // {
                //     shapes[shapes.size() - 1].addVert(currMousePosView);
                // }
            }
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && isFullscreen)
            {
                window.create(sf::VideoMode(SCREENW, SCREENH), "52", 7, sf::ContextSettings(24,8,8));
                isFullscreen = false;
            }
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && !isFullscreen)
            {
                window.create(sf::VideoMode(SCREENW, SCREENH), "52", sf::Style::Fullscreen, sf::ContextSettings(24,8,8));
                isFullscreen = true;
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta > 0 && counter < 24) 
                {
                    if(counter > 24)
                        counter = 24;
                    counter += 1;
                    int mouseX = sf::Mouse::getPosition(window).x;
                    int mouseY = sf::Mouse::getPosition(window).y;
                    // currZoom -= event.mouseWheel.delta * 0.1f;
                    // zoomViewAtMouse(window, view, mouseX, mouseY, 1/1.1);
                    zoomView(window, view, mouseX, mouseY, 1/zoomNumber);
                }
                if (event.mouseWheel.delta < 0 && counter > -24) 
                  {
                    if(counter < -24)
                        counter = -24;
                    counter -= 1;
                    // currZoom += event.mouseWheel.delta * 0.1f;
                    int mouseX = sf::Mouse::getPosition(window).x;
                    int mouseY = sf::Mouse::getPosition(window).y;
                    // zoomViewAtCenter(view, 1.1, window);
                    zoomView(window, view, mouseX, mouseY, zoomNumber);
                }
            }

            // text.setString(ss.str());    
        }
       

        // sf::Vector2i negmousePosGrid;
        mousePosGrid.x = floor(mousePosView.x / grid.getGridSizeU());
        mousePosGrid.y = floor(mousePosView.y / grid.getGridSizeU());

        tileSelector.setPosition(mousePosGrid.x * grid.getGridSizeF(), 
                                mousePosGrid.y * grid.getGridSizeF()); //new tile selection that works incorrectly                                                     //with negative values

        //render begins
        window.clear();
        // sf::View visibleArea (sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        // visibleArea.setSize(sf::Vector2f(1920/2, 1080/2));
        // visibleArea.zoom(2);
        window.setView(visibleArea);
        window.draw(background);
        
        //render game elements
        window.setView(view);
       
        grid.draw_axes(window, view, counter, ss);
        window.draw(tileSelector);

        for (auto &shape : shapes)
        {
            std::vector<tLine> edges = shape.getEdges();
            for(auto &edge : edges)
            {
                window.draw(edge);
            }
            std::vector<sf::CircleShape> verts = shape.getVerts();
            for(auto &vert : verts)
            {
                window.draw(vert);
            }
        }
        // window.draw(ln);

        // window.draw(rect_shape);

        // window.setView(window.getDefaultView());
        window.setView(visibleArea);

        //render ui
        text.setString(ss.str());
        window.draw(text);

        window.display();
        //render ends
    }

    return 0;
}