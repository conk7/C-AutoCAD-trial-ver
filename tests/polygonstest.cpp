#include "../gtest/gtest.h"
#include "../include/polygons.hpp"

// Test fixture for polygons functions
class PolygonsTest : public ::testing::Test {
protected:
    std::vector<Polygon> polygons;
    sf::RenderWindow window;
    std::vector<sf::CircleShape> intersectionPoints;
    std::vector<Point> intersectionPointsCoords;
    bool redrawIntersectionArea;

    PolygonsTest() : window(sf::VideoMode(800, 600), "Test Window"), redrawIntersectionArea(false) {}

    void SetUp() override {
        window = sf::RenderWindow(sf::VideoMode(800, 600), "Test Window");
        redrawIntersectionArea = false;
        polygons.clear();
        intersectionPoints.clear();
        intersectionPointsCoords.clear();
    }
};

// Test case: Checking findIntersectionPoints function
TEST_F(PolygonsTest, FindIntersectionPoints) {
    // Add two polygons to the polygons vector
    polygons.push_back(Polygon());
    polygons.push_back(Polygon());

    // Call findIntersectionPoints function
    findIntersectionPoints(polygons, intersectionPointsCoords, redrawIntersectionArea);

    // Check if redrawIntersectionArea is set to true
    ASSERT_TRUE(redrawIntersectionArea);
}

// Test case: Checking getIntersectionPoints function
TEST_F(PolygonsTest, GetIntersectionPoints) {
    // Add a point to intersectionPointsCoords vector
    intersectionPointsCoords.push_back(Point(0, 0));

    // Call getIntersectionPoints function
    getIntersectionPoints(intersectionPointsCoords, intersectionPoints, redrawIntersectionArea);

    // Check if intersectionPoints vector is not empty
    ASSERT_FALSE(intersectionPoints.empty());

    // Check if redrawIntersectionArea is set to false
    ASSERT_FALSE(redrawIntersectionArea);
}

// Test case: Checking findIntersectionPoints function with more than two polygons
TEST_F(PolygonsTest, FindIntersectionPoints_MoreThanTwoPolygons) {
    // Add three polygons to the polygons vector
    polygons.push_back(Polygon());
    polygons.push_back(Polygon());
    polygons.push_back(Polygon());

    // Call findIntersectionPoints function
    findIntersectionPoints(polygons, intersectionPointsCoords, redrawIntersectionArea);

    // Check if redrawIntersectionArea is set to true
    ASSERT_TRUE(redrawIntersectionArea);
}

// Test case: Checking findIntersectionPoints function with no intersection points
TEST_F(PolygonsTest, FindIntersectionPoints_NoIntersectionPoints) {
    // Add two polygons to the polygons vector
    polygons.push_back(Polygon());
    polygons.push_back(Polygon());

    // Call findIntersectionPoints function
    findIntersectionPoints(polygons, intersectionPointsCoords, redrawIntersectionArea);

    // Check if intersectionPointsCoords vector is empty
    ASSERT_TRUE(intersectionPointsCoords.empty());
}

// Test case: Checking getIntersectionPoints function with no intersection points
TEST_F(PolygonsTest, GetIntersectionPoints_NoIntersectionPoints) {
    // Call getIntersectionPoints function
    getIntersectionPoints(intersectionPointsCoords, intersectionPoints, redrawIntersectionArea);

    // Check if intersectionPoints vector is empty
    ASSERT_TRUE(intersectionPoints.empty());

    // Check if redrawIntersectionArea is set to false
    ASSERT_FALSE(redrawIntersectionArea);
}