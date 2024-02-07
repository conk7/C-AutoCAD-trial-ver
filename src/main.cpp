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

void updateMousePosWindow(sf::Vector2i &prevMousePos, sf::Vector2i &currMousePos,sf::RenderWindow &window)
{
    prevMousePos = currMousePos;
    currMousePos = sf::Mouse::getPosition(window);
}

// void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, sf::View &view, float zoomDiff, std::stringstream &ss)
// {
//     sf::View dummyView = window.getDefaultView();
// 	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
//     // dummyView.setSize(window.getSize().x/zoomDiff, window.getSize().y/zoomDiff);
//     // dummyView.setCenter(window.getDefaultView().getCenter());
//     dummyView.zoom(zoomDiff);
//     window.setView(dummyView);
//     // const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
// 	// const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
//     // dummyView.move(offsetCoords);
// 	window.setView(dummyView);
//     view = dummyView;
//     // ss << "BeforeCoords " << beforeCoord.x << " " << beforeCoord.y << " " << "\n"
//     // << "AfterCoords " << afterCoord.x << " " << afterCoord.y << " "  << "\n";
// 	// sf::View view{ window.getView() };
// 	//view.zoom(zoom);
// 	//window.setView(view);
	
// }

// void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom, sf::View &visibleArea, std::stringstream &ss)
// {
//     const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
// 	sf::View view = visibleArea;
// 	view.zoom(zoom);
// 	window.setView(view);
// 	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
// 	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
// 	view.move(offsetCoords);
// 	window.setView(view);
//     visibleArea = view;


//     ss << "BeforeCoords " << beforeCoord.x << " " << beforeCoord.y << " " << "\n"
//     << "AfterCoords " << afterCoord.x << " " << afterCoord.y << " "  << "\n";
// }

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

    //zoom
    const float zoomDiff = 0.01;
    float currZoom = 1;

    std::vector<Shape> shapes;

    // sf::VertexArray vec(sf::LineStrip, 4);
    // vec[0].position = sf::Vector2f(100, -50);
    // vec[0].color = sf::Color::Black;
    // vec[1].position = sf::Vector2f(200, 0);
    // vec[1].color = sf::Color::Black;
    // vec[2].position = sf::Vector2f(150, 150);
    // vec[2].color = sf::Color::Black;
    // vec[3].position = sf::Vector2f(100, -50);
    // vec[3].color = sf::Color::Black;

    tLine ln(sf::Vector2f(-100,-200), sf::Vector2f(100,100));

    //main loop
    while (window.isOpen())
    {
        //update view
        // view.setSize(window.getSize().x/currZoom, window.getSize().y/currZoom);
        // visibleArea.setSize(window.getSize().x, window.getSize().y);
        // visibleArea.setCenter(static_cast<float>(window.getSize().x/2), static_cast<float>(window.getSize().y/2));

        //update bg
        background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), 
                            static_cast<float>(window.getSize().y)));
        // background.setPosition(sf::Vector2f(window.getPosition().x,
        //                         window.getPosition().y));

        //update mouse pos
        updateMousePosView(prevMousePosView, currMousePosView, window, view);
        updateMousePosWindow(prevMousePosWindow, currMousePosWindow, window);
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
            if(isMouseButtonPressed && event.type == sf::Event::MouseButtonReleased)
            {
                // sf::CircleShape circle(10);
                // circle.setPosition(sf::Vector2f(static_cast<float>(currMousePosView.x), static_cast<float>(currMousePosView.y)));
                // circle.setFillColor(sf::Color::Red);
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
            // if (event.type == sf::Event::MouseWheelScrolled)
            // {
            //     if (event.mouseWheelScroll.delta > 0 && currZoom < 2)
            //     {
            //         currZoom += zoomDiff; 
            //         zoomViewAt({ currMousePosWindow.x, currMousePosWindow.y }, window, view, 1/1.1, ss); 
            //     }

            //     else if (event.mouseWheelScroll.delta < 0)
            //     {
            //         currZoom -= zoomDiff;
            //         zoomViewAt({ currMousePosWindow.x, currMousePosWindow.y }, window, view, 1.1, ss);
            //     }
            // }
            text.setString(ss.str());    
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
       
        grid.draw_axes(window, view, currZoom);
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
        window.draw(text);

        window.display();
        //render ends
    }

    return 0;
}