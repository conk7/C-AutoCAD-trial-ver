#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class tLine : public sf::Drawable
{
private:
    sf::Vertex vertices[4];
    float thickness;
    sf::Color color;
    sf::Vector2f pointA;
    sf::Vector2f pointB;
public:
    tLine(const sf::Vector2f &pointA, const sf::Vector2f &pointB);
    tLine(const sf::Vector2f &pointA, const sf::Vector2f &pointB, sf::Color color, float thickness);
    void draw(sf::RenderTarget &window, sf::RenderStates states) const;
    void setColor(sf::Color color);
    void updatePointA(const sf::Vector2f &pointA);
    void updatePointB(const sf::Vector2f &pointB);
    sf::Vector2f getPointA() const;
    sf::Vector2f getPointB() const;
};