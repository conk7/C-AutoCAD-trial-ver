#include "gtest/gtest.h"
#include "..\include\shape.hpp"

// Mock Grid class for testing
class MockGrid : public Grid {
public:
    MockGrid(float gridSizeF, int gridSizeU) : Grid() {
        this->gridSizeF = gridSizeF;
        this->gridSizeU = gridSizeU;
    }
};

// Test fixture for Shape class
class ShapeTest : public ::testing::Test {
protected:
    Shape shape;
    std::shared_ptr<Grid> grid;

    ShapeTest() : shape(Shape()), grid(std::make_shared<MockGrid>(10.0f, 10)) {}

    void SetUp() override {
        shape = Shape();
        grid = std::make_shared<MockGrid>(10.0f, 10);
    }
};

// Test case: Adding a vertex to an empty shape
TEST_F(ShapeTest, AddVertToEmptyShape) {
    sf::Vector2i coords(50, 50);
    shape.addVert(coords, *grid);
    ASSERT_EQ(shape.getVerts().size(), 1);
    ASSERT_EQ(shape.getEdges().size(), 1);
    ASSERT_FALSE(shape.isFinished());
    ASSERT_TRUE(shape.isDynamicEdge());
}

// Test case: Adding vertices until reaching maxVertCount - 2
TEST_F(ShapeTest, AddVertUntilMaxVertCountMinusTwo) {
    for (int i = 0; i < shape.getMaxVertCount() - 2; i++) {
        sf::Vector2i coords(i * 10, i * 10);
        shape.addVert(coords, *grid);
    }
    ASSERT_EQ(shape.getVerts().size(), shape.getMaxVertCount() - 2);
    ASSERT_EQ(shape.getEdges().size(), shape.getMaxVertCount() - 1);
    ASSERT_FALSE(shape.isFinished());
    ASSERT_TRUE(shape.isDynamicEdge());
}

// Test case: Adding vertices until reaching maxVertCount - 1
TEST_F(ShapeTest, AddVertUntilMaxVertCountMinusOne) {
    for (int i = 0; i < shape.getMaxVertCount() - 1; i++) {
        sf::Vector2i coords(i * 10, i * 10);
        shape.addVert(coords, *grid);
    }
    ASSERT_EQ(shape.getVerts().size(), shape.getMaxVertCount() - 1);
    ASSERT_EQ(shape.getEdges().size(), shape.getMaxVertCount());
    ASSERT_FALSE(shape.isFinished());
    ASSERT_TRUE(shape.isDynamicEdge());
}

// Test case: Adding vertices until reaching maxVertCount
TEST_F(ShapeTest, AddVertUntilMaxVertCount) {
    for (int i = 0; i < shape.getMaxVertCount(); i++) {
        sf::Vector2i coords(i * 10, i * 10);
        shape.addVert(coords, *grid);
    }
    ASSERT_EQ(shape.getVerts().size(), shape.getMaxVertCount());
    ASSERT_EQ(shape.getEdges().size(), shape.getMaxVertCount() + 1);
    ASSERT_TRUE(shape.isFinished());
    ASSERT_FALSE(shape.isDynamicEdge());
}

// Test case: Updating dynamic edge
TEST_F(ShapeTest, UpdateDE) {
    sf::Vector2i coords(50, 50);
    shape.addVert(coords, *grid);
    sf::Vector2i newCoords(60, 60);
    shape.updateDE(newCoords);
    ASSERT_EQ(shape.getEdges().back().getPointB(), sf::Vector2f(newCoords));
}

// Test case: Getting edges
TEST_F(ShapeTest, GetEdges) {
    sf::Vector2i coords(50, 50);
    shape.addVert(coords, *grid);
    ASSERT_EQ(shape.getEdges().size(), 1);
}

// Test case: Getting vertices
TEST_F(ShapeTest, GetVerts) {
    sf::Vector2i coords(50, 50);
    shape.addVert(coords, *grid);
    ASSERT_EQ(shape.getVerts().size(), 1);
}

// Test case: Checking if shape is finished
TEST_F(ShapeTest, IsFinished) {
    for (int i = 0; i < shape.getMaxVertCount(); i++) {
        sf::Vector2i coords(i * 10, i * 10);
        shape.addVert(coords, *grid);
    }
    ASSERT_TRUE(shape.isFinished());
}

// Test case: Getting vertices coordinates
TEST_F(ShapeTest, GetVertsCoords) {
    sf::Vector2i coords(50, 50);
    shape.addVert(coords, *grid);
    ASSERT_EQ(shape.getVertsCoords().size(), shape.getMaxVertCount());
}

// Test case: Setting vertices
TEST_F(ShapeTest, SetVerts) {
    std::vector<sf::CircleShape> verts;
    sf::CircleShape circle(5);
    circle.setPosition(50, 50);
    verts.push_back(circle);
    shape.setVerts(verts);
    ASSERT_EQ(shape.getVerts().size(), 1);
}