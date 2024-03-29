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

void removeVert(std::vector<Polygon>& polygons, 
                Grid& grid, 
                int const MovingVertIdx, 
                int const PolygonIdx, 
                sf::Vector2f const mousePosView,
                bool &redrawIntersectionArea)
{
    int const i = PolygonIdx, j = MovingVertIdx;
    float const gridSizeF = grid.getGridSizeF();
    sf::Vector2f const newPos = { round(mousePosView.x/gridSizeF) * gridSizeF, round(mousePosView.y/gridSizeF) * gridSizeF };
    auto verts = polygons[i].getVerts();
    auto VertsAsPoint = polygons[i].getVertsCoords();
    auto edges = polygons[i].getEdges();

    if (!polygons[i].isFinished())
    {
        if (verts.size() == 0) 
        {
            return;
        }
        else if (verts.size() == 1) 
        {
            polygons.erase(polygons.begin() + i);
        }
        else if (j == verts.size() - 1)
        {
            verts.pop_back();
            edges.pop_back();
            VertsAsPoint.pop_back();
            polygons[i].setVerts(verts);
            edges[edges.size() - 1].updatePointB(newPos);
            sf::Vector2f updateA = {round(VertsAsPoint[VertsAsPoint.size() - 1].getX() / gridSizeF) * gridSizeF, round(VertsAsPoint[VertsAsPoint.size() - 1].getY() / gridSizeF) * gridSizeF};
            edges[edges.size() - 1].updatePointA(updateA);
            polygons[i].setVerts(verts);
            polygons[i].setEdges(edges);
        }
        else if(j == 0)
        {
            verts.erase(verts.begin());
            edges.erase(edges.begin());
            if(verts.size() > 0)
            {
                verts[0].setFillColor(sf::Color::Yellow);
                polygons[i].setVerts(verts);
                polygons[i].setEdges(edges);
            }
            else
                polygons.erase(polygons.begin() + i);
        }
        else
        {
            verts.erase(verts.begin() + j); 
            VertsAsPoint.erase(VertsAsPoint.begin() + j); 
            edges.erase(edges.begin() + j);
            sf::Vector2f updateB = {round(VertsAsPoint[(j + verts.size()) % verts.size()].getX() / gridSizeF) * gridSizeF, round(VertsAsPoint[(j + verts.size()) % verts.size()].getY() / gridSizeF) * gridSizeF};
            edges[(j - 1 + edges.size()) % edges.size()].updatePointB(updateB);
            
            polygons[i].setVerts(verts);
            polygons[i].setEdges(edges);
        }
    }
    else 
    {
        if (verts.size() <= 3) 
        {
            polygons.erase(polygons.begin() + i);
            redrawIntersectionArea = true;
            return;
        }
    
        verts.erase(verts.begin() + j); 
        VertsAsPoint.erase(VertsAsPoint.begin() + j); 
        edges.erase(edges.begin() + j);
        sf::Vector2f updateB = {round(VertsAsPoint[(j + verts.size()) % verts.size()].getX() / gridSizeF) * gridSizeF, round(VertsAsPoint[(j + verts.size()) % verts.size()].getY() / gridSizeF) * gridSizeF};
        edges[(j - 1 + edges.size()) % edges.size()].updatePointB(updateB);
        
        
        polygons[i].setVerts(verts);
        polygons[i].setEdges(edges);
    }
}