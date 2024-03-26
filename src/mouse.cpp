#include "../include/mouse.hpp"

void updateMousePosView(sf::Vector2i &prevMousePos,sf::Vector2i &currMousePos, sf::RenderWindow &window, sf::View &view)
{
    prevMousePos = currMousePos;
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
}