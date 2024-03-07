#include <SFML/Graphics.hpp>
#include <cmath>
class Zoom
{
  private:
        float zoomFactor = 0;
        int zoomCount = 0;
        int zoomLimit = 0;

  public:
    Zoom();
    Zoom(float zoomFactor, int zoomLimit);

    // void zoomView(sf::RenderWindow& window, sf::View& view, int mouseX, int mouseY, float factor);
    void zoomIn(sf::RenderWindow& window, sf::View& view);
    void zoomOut(sf::RenderWindow& window, sf::View& view);
    void zoomSet(sf::RenderWindow& window, sf::View& view);
    int getCount() const;
    float getFactor() const;
};