#include "../include/movingVert.hpp"

#define EPS 10e-3

MovingVert findPolygonIdxOfVert(std::vector<Polygon>& polygons, sf::Vector2f const coords)
{
    auto const coordsF = coords;
    int i = -1, j = -1;
    
    for(i = polygons.size()-1; i >= 0; i--)
    {
        auto verts = polygons[i].getVerts();
        for(j = verts.size()-1; j >= 0; j--)
        {
            sf::FloatRect mouseHitbox(sf::Vector2f(coordsF.x - 5, coordsF.y - 5), sf::Vector2f(10, 10 ));
            if(verts[j].getGlobalBounds().intersects(mouseHitbox))
            {
                return {i, j};
            }
        }
    }
    
    return {-1, -1};
}

void moveVert(std::vector<Polygon>& polygons, Grid& grid, MovingVert vert, sf::Vector2f const mousePosView)
{
    int i = vert.polygonIdx, j = vert.vertIdx;

    auto verts = polygons[i].getVerts();
    float const radius = 5;
    float const gridSizeF = grid.getGridSizeF();

    sf::Vector2f const newPos = { round(mousePosView.x/gridSizeF) * gridSizeF, round(mousePosView.y/gridSizeF) * gridSizeF };
    sf::Vector2f const newPosRadius = { round(mousePosView.x/gridSizeF) * gridSizeF - radius, round(mousePosView.y/gridSizeF) * gridSizeF - radius};

    verts[j].setPosition(newPosRadius);
    for (int k = 0; k < verts.size(); ++k)
    {
        if (k != j)
        {
            if(abs(verts[k].getPosition().x - verts[j].getPosition().x) < EPS &&
            abs(verts[k].getPosition().y - verts[j].getPosition().y) < EPS)
            {
                return;
            }
        }
    }
    std::vector<Point> verts_as_points;
    Point temp_point;
    for (int k = 0; k < verts.size(); k++){
        temp_point = {verts[k].getPosition().x, verts[k].getPosition().y};
        verts_as_points.push_back(temp_point);
    }

    bool flagConvex = IsConvex(verts_as_points);

    // ss << flagConvex << "\n";
    if (!flagConvex)
        return;

    polygons[i].setVerts(verts);

    auto edges = polygons[i].getEdges();
    if(j == 0)
    {
        edges[0].updatePointA(newPos);
        edges[edges.size()-1].updatePointB(newPos);
        polygons[i].setEdges(edges);
    }
    else
    {
        edges[j].updatePointA(newPos);
        edges[j-1].updatePointB(newPos);
        polygons[i].setEdges(edges);
    }
}

void removeVert(std::vector<Polygon>& polygons, Grid& grid, int MovingVertIdx, int PolygonIdx)
{
    int i = PolygonIdx, j = MovingVertIdx;
    
    auto verts = polygons[i].getVerts();
    auto VertsAsPoint = polygons[i].getVertsCoords();
    auto edges = polygons[i].getEdges();
    
    if (verts.size() <= 3) 
    {
        return;
    }
    
    verts.erase(verts.begin() + j); 
    VertsAsPoint.erase(VertsAsPoint.begin() + j); 
    edges.erase(edges.begin() + j);
    sf::Vector2f updateB = {VertsAsPoint[(j + verts.size()) % verts.size()].getX(), VertsAsPoint[(j + verts.size()) % verts.size()].getY()};
    edges[(j - 1 + edges.size()) % edges.size()].updatePointB(updateB);
    
    
    polygons[i].setVerts(verts);
    polygons[i].setEdges(edges);
}