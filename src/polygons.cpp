#include "../include/polygons.hpp"

#define EPS 10e-3

void drawPolygons(std::vector<Polygon> &polygons, sf::RenderWindow &window)
{
    for (auto &polygon : polygons)
    {
        std::vector<tLine> edges = polygon.getEdges();
        for(auto &edge : polygon.getEdges())
            window.draw(edge);
    }
    for (auto &polygon : polygons) //this loop is necessary to avoid drawing vertices under edges
    {
        std::vector<sf::CircleShape> verts = polygon.getVerts();
        for(auto &vert : verts)
            window.draw(vert);
    }
}

void drawIntersectionArea(sf::RenderWindow& window, std::vector<sf::CircleShape> &intersectionPoints)
{
    sf::ConvexShape polygon;
    unsigned vertCount = intersectionPoints.size();
    polygon.setPointCount(vertCount);
    float radius = 5;
    for(int i = 0; i < vertCount; i++)
    {   
        float x = intersectionPoints[i].getPosition().x + radius;
        float y = intersectionPoints[i].getPosition().y + radius;
        polygon.setPoint(i, sf::Vector2f(x, y));
    }


    polygon.setFillColor(sf::Color(173,216,230,155));
    polygon.setOutlineThickness(0);
    
    window.draw(polygon);
}

void drawIntersectionPoints(sf::RenderWindow &window, std::vector<sf::CircleShape> &intersectionPoints)
{
    for(auto &point : intersectionPoints)
    {
        window.draw(point);
    }
}

void findIntersectionPoints(std::vector<Polygon> polygons, 
                        std::vector<Point> &intersectionPointsCoords, 
                        bool &redrawIntersectionArea)
{

    if(!(polygons.size() >= 2 /*&& polygons[polygons.size() - 1].isFinished()*/)) {return;}
    if (!polygons[polygons.size() - 1].isFinished())
    {
        polygons.pop_back();
    }
    if(!(polygons.size() >= 2)) {return;}
    auto fig1 = polygons[0].getVertsCoords();
    auto fig2 = polygons[1].getVertsCoords();
    std::vector<Point> newintersectionPointsCoords = The_area_of_intersection(fig1, fig2);

    if(newintersectionPointsCoords.size() == 0) 
    {
        intersectionPointsCoords = newintersectionPointsCoords;
        redrawIntersectionArea = true;
        return;
    }

    for(int i = 2; i < polygons.size(); i++)
    {
        newintersectionPointsCoords = The_area_of_intersection(newintersectionPointsCoords, polygons[i].getVertsCoords());
        if(newintersectionPointsCoords.size() == 0)
        {
            intersectionPointsCoords = newintersectionPointsCoords;
            redrawIntersectionArea = true;
            return;
        }
    }
    // ss << "OLD\n";
    // ss << intersectionPointsCoords.size() << "\n";
    // for(auto &point : intersectionPointsCoords)
    // {
    //     ss << point.getX() + 5 << " "
    //     << point.getY() + 5 << "\n";   
    // }
    // ss << "NEW\n";
    // ss << newintersectionPointsCoords.size() << "\n";
    // for(auto &point : newintersectionPointsCoords)
    // {
    //     ss << point.getX() + 5 << " "
    //     << point.getY() + 5 << "\n";   
    // }

    if(newintersectionPointsCoords.size() != intersectionPointsCoords.size())
    {
        intersectionPointsCoords = newintersectionPointsCoords;
        redrawIntersectionArea = true;
        return;
    }

    bool equals = false;
    for (int i = 0; i < newintersectionPointsCoords.size(); i++)
    {
        equals = false;
        for (int j = 0; j < intersectionPointsCoords.size(); j++)
        {
            if((fabs(newintersectionPointsCoords[i].getX() - intersectionPointsCoords[j].getX())) < EPS &&
            fabs(newintersectionPointsCoords[i].getY() - intersectionPointsCoords[j].getY()) < EPS)
            {
                equals = true;
            }
        }
        if(!equals)
            break;
    }

    if(equals)
        return;

    intersectionPointsCoords = newintersectionPointsCoords;
    redrawIntersectionArea = true;

}

void getIntersectionPoints(std::vector<Point> intersectionPointsCoords, 
                        std::vector<sf::CircleShape> &intersectionPoints,
                        bool &redrawIntersectionArea)
{
    if(!redrawIntersectionArea) 
    {
        // intersectionPointsCoords.clear(); 
        // redrawIntersectionArea = false; 
        return;
    }

    float radius = 5;
    intersectionPoints.clear();
    for(auto &pointCoords : intersectionPointsCoords)
    {
        sf::CircleShape circle(radius);
        float x = pointCoords.getX();
        float y = pointCoords.getY();
        circle.setPosition(sf::Vector2f(x, y));
        circle.setFillColor(sf::Color(30,220,220,170));
        intersectionPoints.push_back(circle);
    }
    redrawIntersectionArea = false;
}