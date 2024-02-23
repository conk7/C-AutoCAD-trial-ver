#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "..\include\grid.hpp"
#include "..\include\shape.hpp"
#include "..\include\line.hpp"
#include "..\include\isOnVerts.hpp"
#include <cmath>

#define EPS 1e-5

void drawIntersectionPoints(sf::RenderWindow &window, std::vector<sf::CircleShape> &newIntersectionPoints)
{
    // if(newIntersectionPoints.size() == 0) {return;}
    for(auto &point : newIntersectionPoints)
    {
        window.draw(point);
    }
}

void drawShapes(std::vector<Shape> &shapes, sf::RenderWindow &window)
{
    for (auto &shape : shapes)
    {
        std::vector<tLine> edges = shape.getEdges();
        for(auto &edge : edges)
            window.draw(edge);
    }
    for (auto &shape : shapes) //this loop is needed to avoid drawing vertices under edges
    {
        std::vector<sf::CircleShape> verts = shape.getVerts();
        for(auto &vert : verts)
        {
            window.draw(vert);
        }
    }
}

void findIntersectionArea(std::vector<Shape> shapes, 
                        std::vector<Point> &intersectionAreaPoints, 
                        bool &redrawIntersectionArea,
                        std::stringstream &ss)
{
    if (shapes.size() == 2 && shapes[1].isFinished())
    {
        auto fig1 = shapes[0].getVertsCoords();
        auto fig2 = shapes[1].getVertsCoords();
        intersectionAreaPoints = The_area_of_intersection(fig1, fig2);
        redrawIntersectionArea = true;
    }
    else if (shapes.size() > 2 && shapes[shapes.size() - 1].isFinished())
    {
        if(intersectionAreaPoints.size() == 0) {return;}
        auto fig = shapes[shapes.size()-1].getVertsCoords();
        auto newIntersectionAreaPoints = The_area_of_intersection(fig, intersectionAreaPoints);

        bool equals = false;
        for (int i = 0; i < newIntersectionAreaPoints.size(); i++)
        {
            equals = false;
            for (int j = 0; j < intersectionAreaPoints.size(); j++)
            {
                if((fabs(newIntersectionAreaPoints[i].getX() - intersectionAreaPoints[j].getX())) < EPS ||
                fabs(newIntersectionAreaPoints[i].getY() - intersectionAreaPoints[j].getY()) < EPS)
                {
                    equals = true;
                }
            }
            if(!equals)
                break;
        }

        if(equals)
            return;
        else
        {
            intersectionAreaPoints = newIntersectionAreaPoints;
            redrawIntersectionArea = true;
            ss << "size " << newIntersectionAreaPoints.size() << " "
            << intersectionAreaPoints.size() << "\n";   
        }
    }
}

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

void getIntersectionArea(std::vector<Point> points, 
                        std::vector<sf::CircleShape> &newIntersectionPoints,
                        bool &redrawIntersectionArea)
{
    if(!redrawIntersectionArea) {redrawIntersectionArea = false; return;}
    if(points.size() == 0) {redrawIntersectionArea = false; return;}

    float radius = 5;
    newIntersectionPoints.clear();
    for(auto &point : points)
    {
        sf::CircleShape circle(radius);
        float x = point.getX();
        float y = point.getY();
        circle.setPosition(sf::Vector2f(x, y));
        circle.setFillColor(sf::Color::Blue);
        newIntersectionPoints.push_back(circle);
    }
    redrawIntersectionArea = false;
}

void updateMousePosWindow(sf::Vector2i &prevMousePos, sf::Vector2i &currMousePos,sf::RenderWindow &window, sf::View& view) 
{
    prevMousePos = currMousePos;
    currMousePos = sf::Mouse::getPosition(window);
}

void zoomView(sf::RenderWindow& window, sf::View& view, int mouseX, int mouseY, float factor)
{
    sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    view.zoom(factor);
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
  

    //vector of all triangles (polygons)
    std::vector<Shape> shapes;

    //zoom
    int counter = 0; 
    const float zoomFactor = 1.05;

    //intersectionArea
    std::vector<Point> intersectionAreaPoints;
    std::vector<sf::CircleShape> newIntersectionPoints;

    bool redrawIntersectionArea = false;

    //main loop
    while (window.isOpen())
    {
        //update view
        visibleArea.setSize(window.getSize().x, window.getSize().y);
        visibleArea.setCenter(static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y/2));

        //update bg
        background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                            static_cast<float>(window.getSize().y)));

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
        mousePosGrid.x = mousePosView.x / grid.getGridSizeU();
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


        isOnVerts(currMousePosView, shapes, ss);


        //event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                isMouseButtonPressed = false;
                view.move((prevMousePosWindow.x - currMousePosWindow.x) * pow(1/zoomFactor, counter), 
                          (prevMousePosWindow.y - currMousePosWindow.y) * pow(1/zoomFactor, counter));
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                isMouseButtonPressed = true;
            }
            if(isMouseButtonPressed && event.type == sf::Event::MouseButtonReleased)
            {

                if(shapes.size() == 0)
                {
                    Shape shape(3);
                    shape.addVert(currMousePosView, grid);
                    shapes.push_back(shape);
                    isMouseButtonPressed = false;
                }
                else if (shapes.size() != 0 && !shapes[shapes.size() - 1].isFinished())
                {
                    shapes[shapes.size() - 1].addVert(currMousePosView, grid);
                    auto edges = shapes[shapes.size() - 1].getEdges();
                    ss << edges.size();
                    isMouseButtonPressed = false;
                }
                else if (shapes.size() != 0 && shapes[shapes.size() - 1].isFinished())
                {
                    Shape shape(3);
                    shape.addVert(currMousePosView, grid);
                    shapes.push_back(shape);
                    isMouseButtonPressed = false;
                }
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
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    zoomView(window, view, mousePos.x, mousePos.y, 1/zoomFactor);
                }
                if (event.mouseWheel.delta < 0 && counter > -24) 
                  {
                    if(counter < -24)
                        counter = -24;
                    counter -= 1;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    zoomView(window, view, mousePos.x, mousePos.y, zoomFactor);
                }
            }
            if (event.type == sf::Event::Resized)
            {
                sf::View newView;
                auto newSize = window.getSize();
                newView.setSize(newSize.x, newSize.y);
                if(counter > 0)
                    newView.zoom(pow(1/zoomFactor,counter));
                else if(counter < 0)
                    newView.zoom(pow(zoomFactor,-counter));
                newView.setCenter(view.getCenter());
                view = newView;
            }  
        }
       
        // Calling Alexey's function
        findIntersectionArea(shapes, intersectionAreaPoints, redrawIntersectionArea, ss);




        mousePosGrid.x = floor(mousePosView.x / grid.getGridSizeU());
        mousePosGrid.y = floor(mousePosView.y / grid.getGridSizeU());

        tileSelector.setPosition(mousePosGrid.x * grid.getGridSizeF(), 
                                mousePosGrid.y * grid.getGridSizeF());



        //render begins
        window.clear();

        //bg
        window.setView(visibleArea);
        window.draw(background);
        
        //render game elements
        window.setView(view);
       
        grid.draw_axes(window, view, counter, ss);
        window.draw(tileSelector);

        getIntersectionArea(intersectionAreaPoints, newIntersectionPoints, redrawIntersectionArea);

        drawShapes(shapes, window);
        drawIntersectionPoints(window, newIntersectionPoints);

        // if (shapes.size() > 1 && shapes[0].isFinished())
        // {
        //     auto tmp = shapes[0].getVerts()[0].getGlobalBounds();
        //     ss << "TMP Characters: "<< tmp.height << " height " << tmp.left << " left " << tmp.top << " top " << tmp.width << " width \n";
        //     sf::RectangleShape hitbox;
        //     hitbox.setPosition(sf::Vector2f(tmp.left, tmp.top));
        //     hitbox.setSize(sf::Vector2f(tmp.height, tmp.width));
        //     hitbox.setFillColor(sf::Color::Transparent);
        //     hitbox.setOutlineThickness(3.f);
        //     hitbox.setOutlineColor(sf::Color::Red);
        //     window.draw(hitbox);
        // }
        
        // ss << "GLOBAL BOUNDS "<< tmp.getPosition() << "\n";

        window.setView(visibleArea);

        //render ui
        text.setString(ss.str());
        window.draw(text);

        window.display();
        //render ends
    }

    return 0;
}