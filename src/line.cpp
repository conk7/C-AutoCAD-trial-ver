#include "..\include\line.hpp"


tLine::tLine(const sf::Vector2f &pointA, const sf::Vector2f &pointB)
{
    this->pointA = pointA;
    this->pointB = pointB;
    this->thickness = 5.f;
    this->color = sf::Color::Black;
    
    sf::Vector2f direction = pointB - pointA;
    sf::Vector2f unitDirection = direction / sqrt(direction.x*direction.x+direction.y*direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    sf::Vector2f offset = (thickness /2.f) * unitPerpendicular;

    vertices[0].position = pointA + offset;
    vertices[1].position = pointB + offset;
    vertices[2].position = pointB - offset;
    vertices[3].position = pointA - offset;

    for (int i = 0; i < 4; ++i)
        vertices[i].color = color;
}

tLine::tLine(const sf::Vector2f &pointA, const sf::Vector2f &pointB, sf::Color color, float thickness)
{
    this->pointA = pointA;
    this->pointB = pointB;
    this->thickness = thickness;
    this->color = color;

    sf::Vector2f direction = pointB - pointA;
    sf::Vector2f unitDirection = direction / sqrt(direction.x*direction.x+direction.y*direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

    vertices[0].position = pointA + offset;
    vertices[1].position = pointB + offset;
    vertices[2].position = pointB - offset;
    vertices[3].position = pointA - offset;

    for (int i = 0; i < 4; ++i)
        vertices[i].color = color;
}

void tLine::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
    window.draw(vertices, 4, sf::Quads);
}

void tLine::setColor(sf::Color color)
{
    this->color = color;
    for (int i = 0; i < 4; ++i)
        vertices[i].color = color;
}

void tLine::updatePointA(const sf::Vector2f &pointA)
{
    this->pointA = pointA;

    sf::Vector2f direction = pointB - pointA;
    sf::Vector2f unitDirection = direction/ sqrt(direction.x*direction.x+direction.y*direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

    vertices[0].position = pointA + offset;
    vertices[1].position = pointB + offset;
    vertices[2].position = pointB - offset;
    vertices[3].position = pointA - offset;
}

void tLine::updatePointB(const sf::Vector2f &pointB)
{
    this->pointB = pointB;

    sf::Vector2f direction = pointB - pointA;
    sf::Vector2f unitDirection = direction/ sqrt(direction.x*direction.x+direction.y*direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

    vertices[0].position = pointA + offset;
    vertices[1].position = pointB + offset;
    vertices[2].position = pointB - offset;
    vertices[3].position = pointA - offset;
}

sf::Vector2f tLine::getPointA() const
{
    return pointA;
}

sf::Vector2f tLine::getPointB() const
{
    return pointB;
}

// void tLine::setPointA(sf::Vector2f pos)
// {
//     this->pointA = pos;
// }

// void tLine::setPointB(sf::Vector2f pos)
// {
//     this->pointB = pos;
// }