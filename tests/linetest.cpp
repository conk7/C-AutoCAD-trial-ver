#include "gtest/gtest.h"

// Test fixture for tLine class
class tLineTest : public ::testing::Test {
protected:
    tLine line;

    tLineTest() : line(tLine(sf::Vector2f(0, 0), sf::Vector2f(10, 10))) {}

    void SetUp() override {
        line = tLine(sf::Vector2f(0, 0), sf::Vector2f(10, 10));
    }
};

// Test case: Checking parameterized constructor
TEST_F(tLineTest, ParameterizedConstructor) {
    tLine paramLine(sf::Vector2f(0, 0), sf::Vector2f(10, 10), sf::Color::Red, 5.f);
    ASSERT_EQ(paramLine.getPointA(), sf::Vector2f(0, 0));
    ASSERT_EQ(paramLine.getPointB(), sf::Vector2f(10, 10));
}

// Test case: Checking getPointA function
TEST_F(tLineTest, GetPointA) {
    ASSERT_EQ(line.getPointA(), sf::Vector2f(0, 0));
}

// Test case: Checking getPointB function
TEST_F(tLineTest, GetPointB) {
    ASSERT_EQ(line.getPointB(), sf::Vector2f(10, 10));
}

// Test case: Checking updatePointA function
TEST_F(tLineTest, UpdatePointA) {
    line.updatePointA(sf::Vector2f(5, 5));
    ASSERT_EQ(line.getPointA(), sf::Vector2f(5, 5));
}

// Test case: Checking updatePointB function
TEST_F(tLineTest, UpdatePointB) {
    line.updatePointB(sf::Vector2f(15, 15));
    ASSERT_EQ(line.getPointB(), sf::Vector2f(15, 15));
}

// Test case: Checking setColor function
TEST_F(tLineTest, SetColor) {
    line.setColor(sf::Color::Red);
    // As we can't directly check the color of the line, we'll create a new line with the expected color and compare them
    tLine redLine(sf::Vector2f(0, 0), sf::Vector2f(10, 10), sf::Color::Red, 4.f);
    ASSERT_EQ(memcmp(&line, &redLine, sizeof(tLine)), 0);
}

// Test case: Checking the thickness of the line
TEST_F(tLineTest, LineThickness) {
    tLine thickLine(sf::Vector2f(0, 0), sf::Vector2f(10, 10), sf::Color::Red, 6.f);
    ASSERT_GT(thickLine.getThickness(), line.getThickness());
}

// Test case: Checking the direction of the line
TEST_F(tLineTest, LineDirection) {
    sf::Vector2f direction = line.getPointB() - line.getPointA();
    ASSERT_EQ(direction, sf::Vector2f(10, 10));
}