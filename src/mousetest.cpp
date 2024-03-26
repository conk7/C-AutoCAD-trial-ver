#include "../gtest/gtest.h"
#include "../include/mouse.hpp"
#include <SFML/Graphics.hpp>

// Test fixture for mouse functions
class MouseTest : public ::testing::Test {
protected:
    sf::RenderWindow window;
    sf::View view;
    sf::Vector2i prevMousePos;
    sf::Vector2i currMousePos;

    MouseTest() : window(sf::VideoMode(800, 600), "Test Window"), view(window.getDefaultView()) {}

    void SetUp() override {
        window = sf::RenderWindow(sf::VideoMode(800, 600), "Test Window");
        view = window.getDefaultView();
        prevMousePos = sf::Mouse::getPosition(window);
        currMousePos = prevMousePos;
    }
};

// Test case: Checking updateMousePosView function
TEST_F(MouseTest, UpdateMousePosView) {
    updateMousePosView(prevMousePos, currMousePos, window, view);
    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
    ASSERT_EQ(currMousePos, newMousePos);
}

// Test case: Checking updateMousePosWindow function
TEST_F(MouseTest, UpdateMousePosWindow) {
    updateMousePosWindow(prevMousePos, currMousePos, window, view);
    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
    ASSERT_EQ(currMousePos, newMousePos);
}