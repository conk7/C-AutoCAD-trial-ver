#include <SFML/Graphics.hpp>

int main()
{
    const uint16_t SCREEN_WIDTH = 1920;
    const uint16_t SCREEN_HEIGHT = 1080;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "dev-build", sf::Style::Fullscreen);
    // sf::Style::Fullscreen
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);

    sf::CircleShape shape(100.f);
    sf::RectangleShape rect_shape(sf::Vector2f(120.f, 50.f));
    rect_shape.setPosition(100.f,100.f);
    shape.setFillColor(sf::Color::Green);

    bool isPressedMLB = false;
    sf::Vector2i localPosition;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        rect_shape.setFillColor(sf::Color::Blue);
                    }

                case sf::Event::KeyReleased:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        rect_shape.setFillColor(sf::Color::White);
                    }
                
                case sf::Event::MouseButtonPressed:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        rect_shape.setFillColor(sf::Color::Red);
                        isPressedMLB = true;
                    }
                
                case sf::Event::MouseButtonReleased:
                    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        rect_shape.setFillColor(sf::Color::White);
                        isPressedMLB = false;
                    }

                case sf::Event::MouseMoved:
                    localPosition = sf::Mouse::getPosition();
                    rect_shape.setPosition(localPosition.x, localPosition.y);
                    if(isPressedMLB)
                    {
                        rect_shape.setFillColor(sf::Color::Red);
                    }
                
                default:
                    break;
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(rect_shape);
        window.display();
    }

    return 0;
}