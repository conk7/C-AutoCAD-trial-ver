#pragma once
#include <vector>
#include <array>
#include <cmath>
#include "../include/line.hpp"
#include "../include/algorithm.hpp"
#include "../include/grid.hpp"
#include <sstream>

class Polygon
{
private:
    unsigned vertCount;
    bool dynamicEdge;
    bool finished;
    std::vector<tLine> edges;
    std::vector<sf::CircleShape> verts;
public:
    Polygon();
    void addVert(sf::Vector2i coords, Grid grid, std::stringstream &ss);
    void updateDynamicEdge(Grid grid, sf::Vector2i coords);
    std::vector<tLine> getEdges() const;
    std::vector<sf::CircleShape> getVerts() const;
    void setVerts(std::vector<sf::CircleShape> verts);
    void setEdges(std::vector<tLine> edges);
    bool isFinished();
    std::vector<Point> getVertsCoords();
};