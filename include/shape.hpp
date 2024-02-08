#pragma once
#include <vector>
#include <math.h>
#include "..\include\line.hpp"

class Shape
{
private:
    int maxVertCount;
    bool dynamicEdge;
    bool finished;
    std::vector<tLine> edges;
    std::vector<sf::CircleShape> verts;
public:
    Shape(unsigned vertCount);
    void addVert(sf::Vector2i coords);
    // void delVert();
    void updateDE(sf::Vector2i coords);
    std::vector<tLine> getEdges() const;
    std::vector<sf::CircleShape> getVerts() const;
    bool isFinished();
    std::vector<sf::Vector2f> getVertsCoords();
    void draw(sf::RenderWindow window);
};