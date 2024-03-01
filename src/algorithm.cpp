#include<vector>
#include<iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include "..\include\algorithm.hpp"

#define EPS 10e-3

Point::Point(float x1, float y1)
{
    this->x = x1;
    this->y = y1;
}
Point::Point() 
{
    x = 0;
    y = 0;
}
float Point::getX()
{
    return x;
}
float Point::getY()
{
    return y;
}
typedef Point Vector;
static Point P = Point(0,0);
int sign(float a)
{
    if (a > 0) return 1;
    if (a == 0) return 0;
    return -1;
}

void Point::setX(float x)
{
    this->x = x;
}
void Point::setY(float y)
{
    this->y = y;
}


float angle(Point a)
{
    return (a.getY() - P.getY()) / sqrtf(pow(a.getX() - P.getX(), 2) + pow(a.getY() - P.getY(), 2));
}
bool f(Point a, Point b)
{
    if (angle(a) < angle(b)) return true;
    return false;
}
float distance(Point p1, Point p2) {
    return sqrtf(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}
bool are_collinear(std::pair<Point, Point> otr1, std::pair<Point, Point> otr2)
{
    Vector vec1 = Point(otr1.second.getX() - otr1.first.getX(), otr1.second.getY() - otr1.first.getY());
    Vector vec2 = Point(otr2.second.getX() - otr2.first.getX(), otr2.second.getY() - otr2.first.getY());
    if (fabs(vec1.getX()) >= EPS)
    {
        if (fabs(vec1.getY()) >= EPS)
        {
            if (fabs(vec2.getX() / vec1.getX() - vec2.getY() / vec1.getY()) < EPS)
            {
                return true;
            }
        }
        else
        {
            if (fabs(vec2.getY()) < EPS)
            {
                return true;
            }
        }
    }
    else
    {
        if (fabs(vec2.getX()) < EPS)
        {
            return true;
        }
    }
    return false;
}
std::vector<Point> convex_hull(std::vector<Point> points)
{
    int n = points.size();
    if (n < 2)
    {
        return points;
    }
    int min_ind = 0;
    Point minr = Point(1e10, 0);
    for (int i = 0; i < n; i++)
    {
        if (points[i].getX() < minr.getX())
        {
            minr = points[i];
            min_ind = i;
        }
    }
    P = minr;
    std::swap(points[0], points[min_ind]);
    auto it = points.begin();
    it++;
    sort(it, points.end(), f);
    std::vector<Point> a;
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < a.size(); j++)
        {
            if (fabs(points[i].getX() - a[j].getX()) < EPS && fabs(points[i].getY() - a[j].getY()) < EPS)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            a.push_back(points[i]);
        }
    }
    // for (int i = 0; i < n - 1; i++)
    // {
    //     if (fabs(points[i].getX() - points[i + 1].getX()) >= EPS  || fabs(points[i].getY() - points[i + 1].getY()) >= EPS)
    //     {
    //         a.push_back(points[i]);
    //         count++;
    //     }
    // }
    // if (fabs(points[n - 1].getX() - points[n - 2].getX()) >= EPS  || fabs(points[n - 1].getY() - points[n - 2].getY()) >= EPS)
    // {
    //     a.push_back(points[n - 1]);
    // }
    // a.resize(count + 1);
    return a;
}
void per_otr(std::pair<Point, Point> otr1, std::pair<Point, Point> otr2, std::vector<Point>& res)
{
    float x1 = otr1.first.getX(), y1 = otr1.first.getY(), x2 = otr1.second.getX(), y2 = otr1.second.getY();
    float x3 = otr2.first.getX(), y3 = otr2.first.getY(), x4 = otr2.second.getX(), y4 = otr2.second.getY();
    if (are_collinear(otr1, otr2))
    {
        return;
    }
    float det = (x1 - x2) * (y4 - y3) - (x4 - x3) * (y1 - y2);
    if (det == 0)
    {
        return;
    }
    float t1 = ((y4 - y3) * (x4 - x2) + (x3 - x4) * (y4 - y2)) / det;
    float t2 = ((y2 - y1) * (x4 - x2) + (x1 - x2) * (y4 - y2)) / det;
    if (t1 > 0 && t1 < 1 && t2 > 0 && t2 < 1)
    {
        res.push_back(Point(x1 * t1 + x2 * (1 - t1), y1 * t1 + y2 * (1 - t1)));
    }
    return;
}
bool is_inside(std::vector<Point> fig, Point p)
{
    Vector prev = Point( fig[0].getX() - p.getX(), fig[0].getY() - p.getY() );
    float det_prev = 0;
    fig.push_back(fig[0]);
    for (int i = 1; i < fig.size(); i++)
    {   
        if (fabs(distance(fig[i-1], fig[i]) - distance(fig[i-1], p) - distance(fig[i], p)) < EPS)
        {
            return true;
        }
        if (are_collinear({ p, fig[i - 1] }, { p, fig[i] }))
        {
            return false;
        }
        Vector tek = Point( fig[i].getX() - p.getX(), fig[i].getY() - p.getY() );
        float det_tek = tek.getX() * prev.getY() - tek.getY() * prev.getX();
        if (i != 1)
        {
            if (sign(det_prev) != sign(det_tek))
            {
                return false;
            }
            det_prev = det_tek;
            prev = tek;
        }
        else if (i==1)
        {
            det_prev = det_tek;
            prev = tek;
        }
    }
    return true;
}
std::vector<Point> The_area_of_intersection(std::vector<Point> fig1, std::vector<Point> fig2)
{
    // if(fig1.size() == 0 || fig2.size() == 0) {return fig1;} //uncomment this and comment line 53 in main to get a new intersention 
                                                                //area every time a new group of intersected triangles is drawn
    std::vector<Point> points;
    for (auto it : fig2)
    {
        if (is_inside(fig1, it))
        {
            points.push_back(it); 
        }
    }
    for (auto it : fig1)
    {
        if (is_inside(fig2, it)) 
        { 
            points.push_back(it);
        }
    }
    fig1.push_back(fig1[0]);
    fig2.push_back(fig2[0]);
    for (int i = 1; i < fig1.size(); i++)
    {
        for (int j = 1; j < fig2.size(); j++)
        {
            per_otr({ fig1[i - 1],fig1[i] }, { fig2[j - 1], fig2[j] }, points);
        }
    }
    points = convex_hull(points);
    return points;
}