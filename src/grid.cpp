#include <SFML/Graphics.hpp>
#include "../include/grid.hpp"
#include <cmath>
#include <sstream>

Grid::Grid()
{
    this->gridSizeF = 50.f;
    this->gridSizeU = static_cast<unsigned>(gridSizeF);
}
    
Grid::Grid(float const gridSizeF)
{
    this->gridSizeF = gridSizeF;
    this->gridSizeU = static_cast<unsigned>(gridSizeF);
}

void Grid::draw_axes(sf::RenderWindow &window, sf::View const &view, int const counter)
{
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    
    float const thicknessFactor = 1.02;
    float const zoomFactor = pow(thicknessFactor, static_cast<float>(counter));

    float const viewLeftBorder = viewCenter.x - (viewSize.x / 2);
    float const gridLeftBorder = floor(viewLeftBorder / gridSizeU) * gridSizeU;

    float const viewRightBorder = viewCenter.x + (viewSize.x / 2);
    float const gridRightBorder = ceil(viewRightBorder / gridSizeU) * gridSizeU;

    float const viewTopBorder = viewCenter.y - (viewSize.y / 2);
    float const gridTopBorder = ceil(viewTopBorder / gridSizeU) * gridSizeU;

    float const viewBottomBorder = viewCenter.y + (viewSize.y / 2);
    float const gridBottomBorder = (floor(viewBottomBorder / gridSizeU) * gridSizeU) + gridSizeU;
    
    float gridIdx = gridLeftBorder;
    while (gridIdx < gridRightBorder)
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);
        line.setPosition(gridIdx, gridTopBorder - gridSizeU);
        line.setSize(sf::Vector2f(1/zoomFactor, viewSize.y + gridSizeU));
        window.draw(line);
        gridIdx += gridSizeU;
    }
    
    // ss << "ZoomFactor " << zoomFactor << "; ZoomCounter " << counter <<  '\n';

    gridIdx = gridBottomBorder;
    while (gridIdx >= gridTopBorder)
    {
        sf::RectangleShape line;
        line.setFillColor(sf::Color::Black);
        line.setPosition(gridLeftBorder - gridSizeU, gridIdx);
        line.setSize(sf::Vector2f(viewSize.x + gridSizeU * 2, 1/zoomFactor));
        window.draw(line);
        gridIdx -= gridSizeU;
    }

    // if(gridBottomBorder > 0 && gridTopBorder < 0)
    // {
    //     sf::RectangleShape line;
    //     line.setFillColor(sf::Color::Black);
    //     line.setPosition(gridLeftBorder - gridSizeU, -1);
    //     line.setSize(sf::Vector2f(viewSize.x + gridSizeU * 2, 4 /zoomFactor));
    //     window.draw(line);
    // }

    // if(gridRightBorder > 0 && gridLeftBorder < 0)
    // {
    //     sf::RectangleShape line;
    //     line.setFillColor(sf::Color::Black);
    //     line.setPosition(-1, gridTopBorder - gridSizeU);
    //     line.setSize(sf::Vector2f(4 /zoomFactor, viewSize.y + gridSizeU));
    //     window.draw(line);
    // }
}

float Grid::getGridSizeF() const
{
    return gridSizeF;
}

unsigned Grid::getGridSizeU() const
{
    return gridSizeU;
}

void Grid::setGridSizeF(float const gridSizeF)
{
    this->gridSizeF = gridSizeF;
    this->gridSizeU = static_cast<unsigned>(gridSizeF);
}