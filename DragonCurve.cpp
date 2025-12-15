#include "DragonCurve.h"
#include <iostream>

DragonCurve::DragonCurve(Graph_lib::Point start, Graph_lib::Point end) : iteration(0) {
    init(start, end);
}

void DragonCurve::init(Graph_lib::Point start, Graph_lib::Point end) {
    segments.clear();
    iteration = 0;
    
    // Create initial straight line
    // The initial direction doesn't matter for a straight line
    segments.push_back(Vec2d(start, end, false));
}

void DragonCurve::generate_next() {
    std::vector<Vec2d> new_segments;
    
    for (size_t i = 0; i < segments.size(); i++) {
        
        // Split the segment
        auto split_segments = segments[i].split(false, true);
        
        // Add the two new segments
        new_segments.push_back(split_segments.first);
        new_segments.push_back(split_segments.second);
    }
    
    segments = new_segments;
    iteration++;
}

std::vector<Graph_lib::Point> DragonCurve::get_points() const {
    std::vector<Graph_lib::Point> points;
    
    if (segments.empty()) {
        return points;
    }
    
    // Start with first point of first segment
    points.push_back(segments[0].get_start());
    
    // For each segment, add its bend point AND its end point
    for (const auto& segment : segments) {
        points.push_back(segment.get_bend());
        points.push_back(segment.get_end());
    }
    
    return points;
}

int DragonCurve::get_iteration() const {
    return iteration;
}

size_t DragonCurve::size() const {
    return segments.size();
}

const std::vector<Vec2d>& DragonCurve::get_segments() const {
    return segments;
}

void DragonCurve::clear() {
    segments.clear();
    iteration = 0;
}