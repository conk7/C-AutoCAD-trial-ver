#include <SFML/Graphics.hpp>
#include <cmath>
class Zoom
{
  private:
    float zoomFactor;
    int zoomCount;
    int zoomLimit;

  public:
    Zoom();
    Zoom(float zoomFactor, int zoomLimit);

    void zoomIn(sf::RenderWindow& window, sf::View& view);
    void zoomOut(sf::RenderWindow& window, sf::View& view);
    void zoomSet(sf::RenderWindow& window, sf::View& view);
    int getCount() const;
    float getFactor() const;
};