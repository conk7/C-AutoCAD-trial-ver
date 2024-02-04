#pragma once

class Grid
{
private:
    float gridSizeF;
    unsigned gridSizeU;
public:
    Grid();
    Grid(float const gridSizeF);

    void draw_axes(sf::RenderWindow &window, sf::View const &view);
    float getGridSizeF() const;
    unsigned getGridSizeU() const;
    void setGridSizeF(float const gridSizeF);
   
};