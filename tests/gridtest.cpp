#include "gtest/gtest.h"
#include "../include/grid.hpp"
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>

// Test fixture for Grid class
class GridTest : public ::testing::Test {
protected:
    Grid grid;

    GridTest() : grid(Grid(50.f)) {}

    void SetUp() override {
        grid = Grid(50.f);
    }
};

// Test case: Checking default constructor
TEST_F(GridTest, DefaultConstructor) {
    Grid defaultGrid;
    ASSERT_EQ(defaultGrid.getGridSizeF(), 50.f);
    ASSERT_EQ(defaultGrid.getGridSizeU(), 50);
}

// Test case: Checking parameterized constructor
TEST_F(GridTest, ParameterizedConstructor) {
    Grid paramGrid(100.f);
    ASSERT_EQ(paramGrid.getGridSizeF(), 100.f);
    ASSERT_EQ(paramGrid.getGridSizeU(), 100);
}

// Test case: Checking getGridSizeF function
TEST_F(GridTest, GetGridSizeF) {
    ASSERT_EQ(grid.getGridSizeF(), 50.f);
}

// Test case: Checking getGridSizeU function
TEST_F(GridTest, GetGridSizeU) {
    ASSERT_EQ(grid.getGridSizeU(), 50);
}

// Test case: Checking setGridSizeF function
TEST_F(GridTest, SetGridSizeF) {
    grid.setGridSizeF(100.f);
    ASSERT_EQ(grid.getGridSizeF(), 100.f);
    ASSERT_EQ(grid.getGridSizeU(), 100);
}

// Test case: Checking grid size after setting it to a non-integer value
TEST_F(GridTest, SetGridSizeFNonInteger) {
    grid.setGridSizeF(100.5f);
    ASSERT_EQ(grid.getGridSizeF(), 100.5f);
    ASSERT_EQ(grid.getGridSizeU(), 100); // gridSizeU should still be an integer
}

// Test case: Checking grid size after setting it to a negative value
TEST_F(GridTest, SetGridSizeFNegative) {
    grid.setGridSizeF(-50.f);
    ASSERT_EQ(grid.getGridSizeF(), -50.f);
    ASSERT_EQ(grid.getGridSizeU(), 0); // gridSizeU should not be negative
}

// Test case: Checking grid size after setting it to zero
TEST_F(GridTest, SetGridSizeFZero) {
    grid.setGridSizeF(0.f);
    ASSERT_EQ(grid.getGridSizeF(), 0.f);
    ASSERT_EQ(grid.getGridSizeU(), 0);
}