#include "..\include\isOnVerts.hpp"
//static std::unordered_map<sf::Vector2i, std::vector<*sf::CircleShape>> mpVertsCoords;

bool isOnVerts(sf::Vector2i coords, std::vector<Shape> &shapes, std::stringstream &ss)
{
    auto coordsF = sf::Vector2f(static_cast<float>(coords.x),static_cast<float>(coords.y));
    for(int i = shapes.size()-1; i >= 0; i--)
    {
        auto verts = shapes[i].getVerts();
        for(int j = verts.size()-1; j >= 0; j--)
        {
            sf::FloatRect mouseHitbox(sf::Vector2f(coordsF.x - 5, coordsF.y - 5), sf::Vector2f(10, 10 ));
            if(verts[j].getGlobalBounds().intersects(mouseHitbox))
            {
                ss << "True \n";
            }
        }
    }
    return false;
}

// void addVertToMap(sf::Vector2f coordsF)
// {
//     sf::Vector2i coordsI = sf::Vector2i(static_cast<int>(currMousePosView.x), static_cast<int>(currMousePosView.y));
//     // vert = shape[];
//     mpVertsCoords[currMousePosViewI].push_back(currMousePosViewI);
// }