#include "../include/zoom.hpp"

// void Zoom::zoomView(sf::RenderWindow& window, sf::View& view, int mouseX, int mouseY)
// {
//     sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
//     view.zoom(zoomFactor);
//     sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
//     const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
//     view.move(offsetCoords);
//     window.setView(view);
// }

Zoom::Zoom()
{
    zoomFactor = 1.1;
    zoomLimit = 12;
}

Zoom::Zoom(float zoomFactor, int zoomLimit)
{
    this->zoomFactor = zoomFactor;
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
    int mouseX = mousePos.x, mouseY = mousePos.y;

    sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    view.zoom(1/zoomFactor);
    sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
    const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
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
    // sf::View newView;
    auto newSize = window.getSize();
    view.setSize(newSize.x, newSize.y);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int mouseX = mousePos.x, mouseY = mousePos.y;

    if(zoomCount > 0)
    {
        sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
        view.zoom(pow(1/zoomFactor,zoomCount));
        sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
        const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
        view.move(offsetCoords);
        window.setView(view);
    }
    else if(zoomCount < 0)
    {
        sf::Vector2f beforeCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
        view.zoom(pow(zoomFactor,-zoomCount));
        sf::Vector2f afterCoords = window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY), view);
        const sf::Vector2f offsetCoords{ beforeCoords - afterCoords };
        view.move(offsetCoords);
        window.setView(view);
    }
    view.setCenter(view.getCenter());
    // view = newView;
}

int Zoom::getCount() const
{
    return zoomCount;
}

float Zoom::getFactor() const
{
    return zoomFactor;
}