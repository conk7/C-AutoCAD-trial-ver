#include "../include/zoom.hpp"

void zoomView(sf::RenderWindow& window, sf::View& view, int mouseX, int mouseY, float factor)
{
    sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    view.zoom(factor);
    sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
    view.move(offsetCoords);
    window.setView(view);
}