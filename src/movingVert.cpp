#include "../include/movingVert.hpp"

MovingVert findPolygonIdxOfVert(std::vector<Polygon>& polygons, sf::Vector2f coords, std::stringstream &ss)
{
    auto coordsF = coords;
    int i = -1, j = -1;
    
    for(i = polygons.size()-1; i >= 0; i--)
    {
        auto verts = polygons[i].getVerts();
        for(j = verts.size()-1; j >= 0; j--)
        {
            sf::FloatRect mouseHitbox(sf::Vector2f(coordsF.x - 5, coordsF.y - 5), sf::Vector2f(10, 10 ));
            if(verts[j].getGlobalBounds().intersects(mouseHitbox))
            {
                // ss << "True \n";
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
    float radius = 5;
    float gridSizeF = grid.getGridSizeF();
    sf::Vector2f newPos = { round(mousePosView.x/gridSizeF) * gridSizeF, round(mousePosView.y/gridSizeF) * gridSizeF };
    sf::Vector2f newPosRadius = { round(mousePosView.x/gridSizeF) * gridSizeF - radius, round(mousePosView.y/gridSizeF) * gridSizeF - radius};
    verts[j].setPosition(newPosRadius);
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