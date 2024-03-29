#include "gtest/gtest.h"
#include "../include/zoom.hpp"

// Test fixture for Zoom class
class ZoomTest : public ::testing::Test {
protected:
    Zoom zoom;
    sf::RenderWindow window;
    sf::View view;

    ZoomTest() : window(sf::VideoMode(800, 600), "Test Window"), view(window.getDefaultView()) {}

    void SetUp() override {
        window = sf::RenderWindow(sf::VideoMode(800, 600), "Test Window");
        view = window.getDefaultView();
        zoom = Zoom();
    }
};

// Test case: Checking default constructor
TEST_F(ZoomTest, DefaultConstructor) {
    ASSERT_EQ(zoom.getCount(), 0);
    ASSERT_EQ(zoom.getFactor(), 1.1f);
}

// Test case: Checking parameterized constructor
TEST_F(ZoomTest, ParameterizedConstructor) {
    Zoom paramZoom(1.2f, 10);
    ASSERT_EQ(paramZoom.getCount(), 0);
    ASSERT_EQ(paramZoom.getFactor(), 1.2f);
}

// Test case: Checking zoomIn function
TEST_F(ZoomTest, ZoomIn) {
    zoom.zoomIn(window, view);
    ASSERT_EQ(zoom.getCount(), 1);
}

// Test case: Checking zoomOut function
TEST_F(ZoomTest, ZoomOut) {
    zoom.zoomOut(window, view);
    ASSERT_EQ(zoom.getCount(), -1);
}

// Test case: Checking zoomSet function
TEST_F(ZoomTest, ZoomSet) {
    zoom.zoomSet(window, view);
    // As we can't directly check the zoom level of the view, we'll compare it with a new view with the expected zoom level
    sf::View expectedView = window.getDefaultView();
    expectedView.zoom(pow(1/zoom.getFactor(), zoom.getCount()));
    ASSERT_EQ(view.getSize(), expectedView.getSize());
    ASSERT_EQ(view.getCenter(), expectedView.getCenter());
}

// Test case: Checking zoomIn function with zoom limit
TEST_F(ZoomTest, ZoomIn_Limit) {
    for (int i = 0; i < 15; i++) {
        zoom.zoomIn(window, view);
    }
    ASSERT_EQ(zoom.getCount(), 12);
}

// Test case: Checking zoomOut function with zoom limit
TEST_F(ZoomTest, ZoomOut_Limit) {
    for (int i = 0; i < 15; i++) {
        zoom.zoomOut(window, view);
    }
    ASSERT_EQ(zoom.getCount(), -12);
}

// Test case: Checking zoomIn function after zoomOut
TEST_F(ZoomTest, ZoomIn_AfterZoomOut) {
    zoom.zoomOut(window, view);
    zoom.zoomIn(window, view);
    ASSERT_EQ(zoom.getCount(), 0);
}

// Test case: Checking zoomOut function after zoomIn
TEST_F(ZoomTest, ZoomOut_AfterZoomIn) {
    zoom.zoomIn(window, view);
    zoom.zoomOut(window, view);
    ASSERT_EQ(zoom.getCount(), 0);
}

// Test case: Checking zoomSet function after zoomIn and zoomOut
TEST_F(ZoomTest, ZoomSet_AfterZoomInAndZoomOut) {
    zoom.zoomIn(window, view);
    zoom.zoomOut(window, view);
    zoom.zoomSet(window, view);
    sf::View expectedView = window.getDefaultView();
    expectedView.zoom(pow(1/zoom.getFactor(), zoom.getCount()));
    ASSERT_EQ(view.getSize(), expectedView.getSize());
    ASSERT_EQ(view.getCenter(), expectedView.getCenter());
}