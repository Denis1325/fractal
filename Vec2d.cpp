#include "Vec2d.h"
#include <cmath>
#include <iostream>

Vec2d::Vec2d(Point p1, Point p2, bool turn_right) 
    : start_point(p1), end_point(p2) {
    calculate_bend(turn_right);
}

void Vec2d::calculate_bend(bool turn_right) {
    int mid_x = (start_point.x + end_point.x) / 2;
    int mid_y = (start_point.y + end_point.y) / 2;
    
    int dx = end_point.x - start_point.x;
    int dy = end_point.y - start_point.y;
    
    if (turn_right) {
        bend_point = Point(mid_x + dy/2, mid_y - dx/2);
    } else {
        bend_point = Point(mid_x - dy/2, mid_y + dx/2);
    }
}

std::vector<Point> Vec2d::get_points() const {
    return {start_point, bend_point, end_point};
}

std::pair<Vec2d, Vec2d> Vec2d::split(bool turn1, bool turn2) const {
    return {
        Vec2d(start_point, bend_point, turn1),
        Vec2d(bend_point, end_point, turn2)
    };
}