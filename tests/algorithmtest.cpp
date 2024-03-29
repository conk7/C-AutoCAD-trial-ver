#include<vector>
#include<iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include "../include/algorithm.hpp"
#include <gtest/gtest.h>

#define EPS 1e-3

TEST(PointTest, DefaultConstructor) {
    Point p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, Constructor) {
    Point p(1.0, 2.0);
    EXPECT_EQ(p.getX(), 1.0);
    EXPECT_EQ(p.getY(), 2.0);
}

TEST(PointTest, SettersAndGetters) {
    Point p;
    p.setX(1.0);
    p.setY(2.0);
    EXPECT_EQ(p.getX(), 1.0);
    EXPECT_EQ(p.getY(), 2.0);
}

TEST(AreaTest, TriangleArea) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(0, 1)};
    EXPECT_NEAR(Area(fig), 0.5, EPS);
}

TEST(AreaTest, RectangleArea) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    EXPECT_NEAR(Area(fig), 1.0, EPS);
}

TEST(AreaTest, LargeNumberPoints) {
    std::vector<Point> fig;
    for (int i = 0; i < 1000; ++i) {
        fig.push_back(Point(i, i));
    }
    EXPECT_NEAR(Area(fig), 0.0, EPS);
}

TEST(ConvexHullTest, CollinearPoints) {
    std::vector<Point> points = {Point(0, 0), Point(1, 1), Point(2, 2)};
    std::vector<Point> expected = {Point(0, 0), Point(2, 2)};
    EXPECT_EQ(convex_hull(points), expected);
}

TEST(ConvexHullTest, LargeNumberPoints) {
    std::vector<Point> points;
    for (int i = 0; i < 1000; ++i) {
        points.push_back(Point(i, i));
    }
    std::vector<Point> expected = {Point(0, 0), Point(999, 999)};
    EXPECT_EQ(convex_hull(points), expected);
}

TEST(IsConvexTest, ConvexPolygon) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    EXPECT_TRUE(IsConvex(fig));
}

TEST(IsConvexTest, NonConvexPolygon) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(0.5, 0.5), Point(1, 1), Point(0, 1)};
    EXPECT_FALSE(IsConvex(fig));
}

TEST(IsInsideTest, PointInsidePolygon) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Point p(0.5, 0.5);
    EXPECT_TRUE(is_inside(fig, p));
}

TEST(IsInsideTest, PointOutsidePolygon) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Point p(1.5, 1.5);
    EXPECT_FALSE(is_inside(fig, p));
}

TEST(AreaOfIntersectionTest, IntersectingPolygons) {
    std::vector<Point> fig1 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> fig2 = {Point(1, 1), Point(3, 1), Point(3, 3), Point(1, 3)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_NEAR(Area(intersection), 1.0, EPS);
}

TEST(AreaOfIntersectionTest, NonIntersectingPolygons) {
    std::vector<Point> fig1 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> fig2 = {Point(3, 3), Point(4, 3), Point(4, 4), Point(3, 4)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_TRUE(intersection.empty());
}

TEST(AreaOfIntersectionTest, IdenticalPolygons) {
    std::vector<Point> fig1 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> fig2 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_EQ(intersection, fig1);
}

TEST(AreaOfIntersectionTest, PolygonInsideAnother) {
    std::vector<Point> fig1 = {Point(0, 0), Point(4, 0), Point(4, 4), Point(0, 4)};
    std::vector<Point> fig2 = {Point(1, 1), Point(3, 1), Point(3, 3), Point(1, 3)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_EQ(intersection, fig2);
}

TEST(AreaOfIntersectionTest, LargeNumberPoints) {
    std::vector<Point> fig1, fig2;
    for (int i = 0; i < 1000; ++i) {
        fig1.push_back(Point(i, i));
        fig2.push_back(Point(i + 0.5, i + 0.5));
    }
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_TRUE(intersection.empty());
}

TEST(AngleTest, DifferentPoints) {
    Point p1(0, 0), p2(1, 0), p3(0, 1);
    P = p1;
    EXPECT_NEAR(angle(p2), 0.0, EPS);
    EXPECT_NEAR(angle(p3), 1.0, EPS);
}

TEST(DistanceTest, SamePoint) {
    Point p1(1, 2), p2(1, 2);
    EXPECT_NEAR(distance(p1, p2), 0.0, EPS);
}

TEST(DistanceTest, DifferentPoints) {
    Point p1(1, 2), p2(4, 6);
    EXPECT_NEAR(distance(p1, p2), 5.0, EPS);
}

TEST(AreCollinearTest, CollinearPoints) {
    std::pair<Point, Point> otr1 = {Point(0, 0), Point(1, 1)};
    std::pair<Point, Point> otr2 = {Point(2, 2), Point(3, 3)};
    EXPECT_TRUE(are_collinear(otr1, otr2));
}

TEST(AreCollinearTest, NonCollinearPoints) {
    std::pair<Point, Point> otr1 = {Point(0, 0), Point(1, 1)};
    std::pair<Point, Point> otr2 = {Point(0, 1), Point(1, 0)};
    EXPECT_FALSE(are_collinear(otr1, otr2));
}

TEST(RotateTest, ZeroRotation) {
    std::pair<Point, Point> a = {Point(0, 0), Point(1, 0)};
    std::pair<Point, Point> b = {Point(0, 0), Point(0, 1)};
    EXPECT_NEAR(Rotate(a, b), 0.0, EPS);
}

TEST(RotateTest, PositiveRotation) {
    std::pair<Point, Point> a = {Point(0, 0), Point(1, 0)};
    std::pair<Point, Point> b = {Point(0, 0), Point(-1, 1)};
    EXPECT_GT(Rotate(a, b), 0);
}

TEST(RotateTest, NegativeRotation) {
    std::pair<Point, Point> a = {Point(0, 0), Point(1, 0)};
    std::pair<Point, Point> b = {Point(0, 0), Point(1, -1)};
    EXPECT_LT(Rotate(a, b), 0);
}

TEST(SignTest, PositiveNumber) {
    EXPECT_EQ(sign(1.0), 1);
}

TEST(SignTest, Zero) {
    EXPECT_EQ(sign(0.0), 0);
}

TEST(SignTest, NegativeNumber) {
    EXPECT_EQ(sign(-1.0), -1);
}

TEST(AngleTest, ZeroAngle) {
    P = Point(0, 0);
    Point a(1, 0);
    EXPECT_NEAR(angle(a), 0.0, EPS);
}

TEST(AngleTest, RightAngle) {
    P = Point(0, 0);
    Point a(0, 1);
    EXPECT_NEAR(angle(a), 1.0, EPS);
}

TEST(AngleTest, StraightAngle) {
    P = Point(0, 0);
    Point a(-1, 0);
    EXPECT_NEAR(angle(a), 0.0, EPS);
}

TEST(AngleTest, FullAngle) {
    P = Point(0, 0);
    Point a(0, -1);
    EXPECT_NEAR(angle(a), -1.0, EPS);
}

TEST(AngleTest, NegativeAngle) {
    P = Point(0, 0);
    Point a(-1, -1);
    EXPECT_NEAR(angle(a), -1.0, EPS);
}

TEST(DistanceTest, DifferentPointsInNegativeQuadrant) {
    Point p1(-1, -2), p2(-4, -6);
    EXPECT_NEAR(distance(p1, p2), 5.0, EPS);
}

TEST(AreCollinearTest, VerticalLine) {
    std::pair<Point, Point> otr1 = {Point(0, 0), Point(0, 1)};
    std::pair<Point, Point> otr2 = {Point(0, 2), Point(0, 3)};
    EXPECT_TRUE(are_collinear(otr1, otr2));
}

TEST(AreCollinearTest, HorizontalLine) {
    std::pair<Point, Point> otr1 = {Point(0, 0), Point(1, 0)};
    std::pair<Point, Point> otr2 = {Point(2, 0), Point(3, 0)};
    EXPECT_TRUE(are_collinear(otr1, otr2));
}

TEST(IsConvexTest, ConcavePolygon) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(0.5, 0.5), Point(1, 1), Point(0, 1)};
    EXPECT_FALSE(IsConvex(fig));
}

TEST(IsInsideTest, PointOnEdgeOfPolygon) {
    std::vector<Point> fig = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Point p(0.5, 0);
    EXPECT_TRUE(is_inside(fig, p));
}

TEST(AreaOfIntersectionTest, OverlappingSquares) {
    std::vector<Point> fig1 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> fig2 = {Point(1, 1), Point(3, 1), Point(3, 3), Point(1, 3)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_NEAR(Area(intersection), 1.0, EPS);
}

TEST(AreaOfIntersectionTest, IdenticalSquares) {
    std::vector<Point> fig1 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> fig2 = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_EQ(intersection, fig1);
}

TEST(AreaOfIntersectionTest, SquareInsideAnother) {
    std::vector<Point> fig1 = {Point(0, 0), Point(4, 0), Point(4, 4), Point(0, 4)};
    std::vector<Point> fig2 = {Point(1, 1), Point(3, 1), Point(3, 3), Point(1, 3)};
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_EQ(intersection, fig2);
}

TEST(AreaOfIntersectionTest, LargeNumberPoints) {
    std::vector<Point> fig1, fig2;
    for (int i = 0; i < 1000; ++i) {
        fig1.push_back(Point(i, i));
        fig2.push_back(Point(i + 0.5, i + 0.5));
    }
    std::vector<Point> intersection = The_area_of_intersection(fig1, fig2);
    EXPECT_TRUE(intersection.empty());
}