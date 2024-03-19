#include<vector>
#include<iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include "../include/algorithm.hpp"

#define EPS 1e-3
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
float distance(Point p1, Point p2)
{
    return sqrtf(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}
bool f(Point a, Point b)
{   
    if (are_collinear({P,a}, {P,b}))
    {
        return distance(a, P) > distance(b, P);
    }
    return angle(a) < angle(b);
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
float Rotate(std::pair<Point, Point> a, std::pair<Point, Point> b)
{
    return (a.second.getX() - a.first.getX()) * (b.second.getY() - b.first.getY()) - (a.second.getY() - a.first.getY()) * (b.second.getX() - b.first.getX());
}
bool IsConvex(std::vector<Point> fig)
{   
    int n = fig.size();
    if (n <= 3)
    {
        return true;
    }
    fig.push_back(fig[0]);
    float det_prev = 0;
    bool flag = false;
    for (int i = 1; i < n; i++)
    {
        if (are_collinear({ fig[i - 1], fig[i] }, { fig[i], fig[i + 1] }))
        {
            if (distance(fig[i - 1], fig[i]) > distance(fig[i - 1], fig[i + 1]))
            {
                return false;
            }
        }
        else
        {
            float det_tek = Rotate({ fig[i - 1], fig[i] }, { fig[i], fig[i + 1] });
            if (sign(det_prev) != sign(det_tek) && flag)
            {
                return false;
            }
            else if (!flag)
            {
                det_prev = det_tek;
                flag = true;
            }
            else
            {
                det_prev = det_tek;
            }
        }
    }
    return true;
}
std::vector<Point> convex_hull(std::vector<Point> points)
{
    int n = points.size();
    if (n < 2)
    {
        return points;
    }
    int min_ind = 0;
    Point minr = Point(1e10, 1e10);
    for (int i = 0; i < n; i++)
    {
        if (fabs(points[i].getX() - minr.getX()) < EPS)
        {
            if (points[i].getY() < minr.getY())
            {
                minr = points[i];
                min_ind = i;
            }
        }
        else if (points[i].getX() < minr.getX())
        {
            minr = points[i];
            min_ind = i;
        }
    }
    P = minr;
    std::swap(points[0], points[min_ind]);
    auto it = points.begin();
    it++;
    std::sort(it, points.end(), f);
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
    if (a.size() <= 2)
    {
        return a;
    }
    a.push_back(a[0]);
    std::vector<Point> st = {a[0], a[1]};
    for (int i = 2; i < a.size(); i++)
    {
        if (are_collinear({st[st.size() - 1], st[st.size() - 2]}, {st[st.size() - 1], a[i]}))
        {
            if (distance(st[st.size() - 2], st[st.size() - 1]) < distance(st[st.size() - 2], a[i]))
            {
                st[st.size() - 1] = a[i];
            }
        }
        else
        {
            st.push_back(a[i]);
        }
    }
    st.pop_back();
    return st;
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
    bool flag = true;
    fig.push_back(fig[0]);
    for (int i = 1; i < fig.size(); i++)
    {   
        if (fabs(distance(fig[i-1], fig[i]) - distance(fig[i-1], p) - distance(fig[i], p)) < EPS)
        {
            return true;
        }
        if (are_collinear({ p, fig[i - 1] }, { p, fig[i] }))
        {
            flag = false;
        }
        Vector tek = Point( fig[i].getX() - p.getX(), fig[i].getY() - p.getY() );
        float det_tek = tek.getX() * prev.getY() - tek.getY() * prev.getX();
        if (i != 1 && flag)
        {
            if (sign(det_prev) != sign(det_tek))
            {
                return false;
            }
            det_prev = det_tek;
            prev = tek;
        }
        else if (i == 1)
        {
            det_prev = det_tek;
            prev = tek;
        }
    }
    return flag;
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