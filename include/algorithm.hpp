#include<vector>
#include<iostream>
#include <set>
#include <cmath>
#include <algorithm>

class Point
{
    float x;
    float y;
  public:
    Point(float x1, float y1);
    Point();
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
};

int sign(float a);
float angle(Point a);
bool f(Point a, Point b);
float distance(Point p1, Point p2);
bool are_collinear(std::pair<Point, Point> otr1, std::pair<Point, Point> otr2);
float Rotate(std::pair<Point, Point> a, std::pair<Point, Point> b);
bool IsConvex(std::vector<Point> fig);
std::vector<Point> convex_hull(std::vector<Point> points);
void per_otr(std::pair<Point, Point> otr1, std::pair<Point, Point> otr2, std::vector<Point>& res);
bool is_inside(std::vector<Point> fig, Point p);
std::vector<Point> The_area_of_intersection(std::vector<Point> fig1, std::vector<Point> fig2);
float Area(std::vector<Point> fig);