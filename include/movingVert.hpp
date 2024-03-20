#include "../include/polygon.hpp"
#include <sstream>

struct MovingVert
{
    int polygonIdx = -1, vertIdx = -1;
};

MovingVert findPolygonIdxOfVert(std::vector<Polygon>& polygons, sf::Vector2f coords, std::stringstream &ss);
void moveVert(std::vector<Polygon>& polygons, Grid& grid, MovingVert vert, sf::Vector2f const mousePosView, std::stringstream &ss);

