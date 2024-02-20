#pragma once
#include <vector>
#include <array>
#include <math.h>
#include "..\include\line.hpp"
#include "..\include\algorithm.hpp"
#include "..\include\grid.hpp"

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
    void addVert(sf::Vector2i coords, Grid grid);
    // void delVert();
    void updateDE(sf::Vector2i coords);
    std::vector<tLine> getEdges() const;
    std::vector<sf::CircleShape> getVerts() const;
    void setVerts(std::vector<sf::CircleShape> verts);
    bool isFinished();
    // std::vector<sf::Vector2f> getVertsCoords();
    void draw(sf::RenderWindow window);
    std::vector<Point> getVertsCoords();

    // std::array<std::array<float,2>,3> getVertsCoords();
};