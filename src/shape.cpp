#include <SFML/Graphics.hpp>
#include "..\include\shape.hpp"
#include "..\include\line.hpp"
#include <math.h>

Shape::Shape(unsigned const vertCount = 3)
{
    maxVertCount = vertCount;
    // this->edges.resize(vertCount);
    // this->verts.resize(vertCount);
    dynamicEdge = false;
    finished = true;
}

void Shape::addVert(sf::Vector2i coords)
{
    if(edges.size() == 0)
    {
        sf::CircleShape circle(5);
        circle.setPosition(sf::Vector2f(static_cast<float>(coords.x), static_cast<float>(coords.y)));
        circle.setFillColor(sf::Color::Red);
        verts.push_back(circle);

        tLine edge(sf::Vector2f(coords.x, coords.y), sf::Vector2f(coords.x+5, coords.y+5), sf::Color::Black, 5.f);
        edges.push_back(edge);
        finished = false;
        dynamicEdge = true;
    }
    else if(edges.size() < maxVertCount)
    {
        sf::CircleShape circle(5);
        circle.setPosition(sf::Vector2f(static_cast<float>(coords.x), static_cast<float>(coords.y)));
        circle.setFillColor(sf::Color::Red);
        verts.push_back(circle);

        sf::Vector2f coordsF = sf::Vector2f(static_cast<float>(coords.x), static_cast<float>(coords.y));
        edges[edges.size() - 1].updatePointB(coordsF);

        tLine edge(sf::Vector2f(coords.x, coords.y), sf::Vector2f(coords.x+5, coords.y+5), sf::Color::Black, 5.f);
        edges.push_back(edge);
    }
    else if(edges.size() == maxVertCount)
    {
        sf::Vector2f pointA = edges[0].getPointA();
        // sf::Vector2f coordsF = sf::Vector2f(static_cast<float>(coords.x), static_cast<float>(coords.y));
        edges[edges.size() - 1].updatePointB(pointA);
        finished = true;
        dynamicEdge = false;
    }
}

void Shape::updateDE(sf::Vector2i coords)
{
    if(!dynamicEdge)
        return;
    
    sf::Vector2f coordsF = sf::Vector2f(static_cast<float>(coords.x), static_cast<float>(coords.y));
    edges[edges.size() - 1].updatePointB(coordsF);
}

std::vector<tLine> Shape::getEdges() const
{
    return this->edges;
}

std::vector<sf::CircleShape> Shape::getVerts() const
{
    return this->verts;
}

bool Shape::isFinished()
{
    return finished;
}