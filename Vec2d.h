#ifndef VEC2D_H
#define VEC2D_H

#include "Graph_lib/Graph.h"
#include <vector>
#include <utility>

using namespace Graph_lib;

class Vec2d {
private:
    Point start_point;
    Point end_point;
    Point bend_point;
    
public:
    Vec2d(Point p1, Point p2, bool turn_right = true);
    
    void calculate_bend(bool turn_right);
    
    std::vector<Point> get_points() const;
    
    std::pair<Vec2d, Vec2d> split(bool turn1, bool turn2) const;

    Point get_start() const { return start_point; }
    Point get_end() const { return end_point; }
    Point get_bend() const { return bend_point; }
};

#endif // VEC2D_H