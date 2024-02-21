#include<vector>
#include<iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include "..\include\algorithm.hpp"
static float constexpr EPS = 1e-5;

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
std::vector<Point> convex_hull(std::vector<Point> points) 
{ 
    int n = points.size();
    std::vector<Point>a(n);
    if (n == 0)
    {
        return a;
    }  
    Point minr = Point(1e10, 0); 
    for (int i = 0; i < n; i++) 
    { 
        if (points[i].getX() < minr.getX()) 
        { 
            minr = points[i]; 
        } 
    } 
    P = minr;
    int count = 1; 
    for (auto it : points) 
    { 
        if (fabs(it.getX() - minr.getX())>EPS || fabs(it.getY() - minr.getY())>EPS) 
        { 
            a[count] = Point(it.getX(), it.getY()); 
            count++; 
        } 
    } 
    a[0] = minr; 
    auto it = a.begin(); 
    it++; 
    sort(it, a.end(), f); 
    return a; 
}
bool per_otr(std::pair<Point, Point> otr1, std::pair<Point, Point> otr2, std::vector<Point>& res) //peresechenie otrezkov
{
    Vector vec1 = Point( otr1.second.getX() - otr1.first.getX(), otr1.second.getY() - otr1.first.getY() );
    Vector vec2 = Point( otr2.second.getX() - otr2.first.getX(), otr2.second.getY() - otr2.first.getY() );
    float x1 = otr1.first.getX(), y1 = otr1.first.getY(), x2 = otr1.second.getX(), y2 = otr1.second.getY();
    float x3 = otr2.first.getX(), y3 = otr2.first.getY(), x4 = otr2.second.getX(), y4 = otr2.second.getY();
    if (vec1.getX() != 0)
    {
        if (vec1.getY() != 0)
        {
            if (vec2.getX() / vec1.getX() > vec2.getY() / vec1.getY() - EPS && vec2.getX() / vec1.getX() < vec2.getY() / vec1.getY() + EPS)
            {
                return false;
            }
        }
        else
        {
            if (fabs(vec2.getY()) < EPS)
            {
                return false;
            }
        }
    }
    else
    {
        if (fabs(vec2.getX()) < EPS)
        {
            return false;
        }
    }
    float det = (x1 - x2) * (y4 - y3) - (x4 - x3) * (y1 - y2);
    if (det == 0)
    {
        return false;
    }
    float t1 = ((y4 - y3) * (x4 - x2) + (x3 - x4) * (y4 - y2)) / det;
    float t2 = ((y2 - y1) * (x4 - x2) + (x1 - x2) * (y4 - y2)) / det;
    if (t1 > 0-EPS && t1 < 1+EPS && t2 > 0-EPS && t2 < 1+EPS)
    {
        res.push_back(Point(x1 * t1 + x2 * (1 - t1), y1 * t1 + y2 * (1 - t1)));
        return true;
    }
    return false;
}
bool is_inside(std::vector<Point> fig, Point p)
{
    Vector prev = Point( fig[0].getX() - p.getX(), fig[0].getY() - p.getY() );
    float det_prev = 0;
    fig.push_back(fig[0]);
    for (int i = 1; i < fig.size(); i++)
    {
        Vector tek = Point( fig[i].getX() - p.getX(), fig[i].getY() - p.getY() );
        float det_tek = tek.getX() * prev.getY() - tek.getY() * prev.getX();
        if (det_tek != 0 &&  det_prev != 0)
        {
            if (sign(det_prev) != sign(det_tek))
            {
                fig.pop_back();
                return false;
            }
            det_prev = det_tek;
            prev = tek;
        }
        else if (det_prev == 0)
        {
            det_prev = det_tek;
            prev = tek;
        }
        else
        {
            prev = tek;
        }        
    }
    fig.pop_back();
    return true;
}
std::vector<Point> The_area_of_intersection(std::vector<Point> fig1, std::vector<Point> fig2)
{
    if (fig1.size() == 0 || fig2.size() == 0)
    {
        // std::vector<Point> a(0);
        return fig1;
    }

    bool equals = false;
    for (int i = 0; i < fig1.size(); i++)
    {
        equals = false;
        for (int j = 0; j < fig2.size(); j++)
        {
            if((fabs(fig1[i].getX() - fig2[j].getX())) < EPS ||
            fabs(fig1[i].getY() - fig2[j].getY()) < EPS)
            {
                equals = true;
            }
        }
        if(!equals)
            break;
    }

    if(equals)
        return fig1;

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
    auto fig1_copy = fig1;
    auto fig2_copy = fig2;
    fig1_copy.push_back(fig1[0]);
    fig2_copy.push_back(fig2[0]);
    for (int i = 1; i < fig1.size() + 1; i++)
    {
        for (int j = 1; j < fig2.size() + 1; j++)
        {
            per_otr({ fig1_copy[i - 1],fig1_copy[i] }, { fig2_copy[j - 1], fig2_copy[j] }, points);
        }
    }
    points = convex_hull(points);
    return points;
}