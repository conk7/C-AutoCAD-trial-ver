#include "../include/zoom.hpp"

Zoom::Zoom()
{
    zoomFactor = 1.1;
    zoomCount = 0;
    zoomLimit = 12;
}

Zoom::Zoom(float zoomFactor, int zoomLimit)
{
    this->zoomFactor = zoomFactor;
    this->zoomCount = 0;
    this->zoomLimit = zoomLimit;
}

void Zoom::zoomIn(sf::RenderWindow& window, sf::View& view)
{
    if(zoomCount >= 12)
    {
        zoomCount = 12;
        return;
    }
    zoomCount += 1;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int const mouseX = mousePos.x, mouseY = mousePos.y;

    sf::Vector2f const beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    view.zoom(1/zoomFactor);
    sf::Vector2f const afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    sf::Vector2f const offsetCoords{ beforeCoords - afterCoords };
    view.move(offsetCoords);
    window.setView(view);
}
void Zoom::zoomOut(sf::RenderWindow& window, sf::View& view)
{
    if(zoomCount <= -12)
    {
        zoomCount = -12;
        return;
    }
    zoomCount -= 1;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int mouseX = mousePos.x, mouseY = mousePos.y;

    sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    view.zoom(zoomFactor);
    sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
    view.move(offsetCoords);
    window.setView(view);
}

void Zoom::zoomSet(sf::RenderWindow& window, sf::View& view)
{
    auto const newSize = window.getSize();
    view.setSize(newSize.x, newSize.y);

    view.zoom(pow(1/zoomFactor,zoomCount));

    view.setCenter(view.getCenter());
}

int Zoom::getCount() const
{
    return zoomCount;
}

float Zoom::getFactor() const
{
    return zoomFactor;
}