#include <SFML/Graphics.hpp>
#include "..\include\polygon.hpp"
#include <sstream>

void drawIntersectionArea(sf::RenderWindow& window, std::vector<sf::CircleShape> &intersectionPoints);

void drawIntersectionPoints(sf::RenderWindow &window, std::vector<sf::CircleShape> &intersectionPoints);

void findIntersectionPoints(std::vector<Polygon> shapes, 
                        std::vector<Point> &intersectionAreaPoints, 
                        bool &redrawIntersectionArea,
                        std::stringstream &ss);

void getIntersectionPoints(std::vector<Point> points, 
                        std::vector<sf::CircleShape> &intersectionPoints,
                        bool &redrawIntersectionArea);