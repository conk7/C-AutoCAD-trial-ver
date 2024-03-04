#pragma once
#include <vector>
#include <array>
#include <cmath>
#include "..\include\line.hpp"
#include "..\include\algorithm.hpp"
#include "..\include\grid.hpp"

class Polygon
{
private:
    unsigned vertCount = 0;
    bool dynamicEdge = false;
    bool finished = true;
    std::vector<tLine> edges;
    std::vector<sf::CircleShape> verts;
public:
    Polygon();
    void addVert(sf::Vector2i coords, Grid grid);
    // void delVert();
    void updateDynamicEdge(Grid grid, sf::Vector2i coords);
    std::vector<tLine> getEdges() const;
    std::vector<sf::CircleShape> getVerts() const;
    void setVerts(std::vector<sf::CircleShape> verts);
    void setEdges(std::vector<tLine> edges);
    bool isFinished();
    // void draw(sf::RenderWindow window);
    std::vector<Point> getVertsCoords();
};