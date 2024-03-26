#include "../include/polygon.hpp"
#include <sstream>

struct MovingVert
{
    int polygonIdx = -1, vertIdx = -1;
};

MovingVert findPolygonIdxOfVert(std::vector<Polygon>& polygons, sf::Vector2f coords);
void moveVert(std::vector<Polygon>& polygons, Grid& grid, MovingVert vert, sf::Vector2f const mousePosView);
void removeVert(std::vector<Polygon>& polygons, Grid& grid, int MovingVertIdx, int PolygonIdx, sf::Vector2f mouse);

