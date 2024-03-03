#include <unordered_map>
#include "..\include\shape.hpp"
#include <sstream>

struct MovingVert
{
    int shapeNum = -1, VertNum = -1;
};

MovingVert findShapeOfVert(std::vector<Shape>& shapes, sf::Vector2f coords, std::stringstream &ss);
void moveVert(std::vector<Shape>& shapes, Grid& grid, MovingVert vert, sf::Vector2f const mousePosView);

