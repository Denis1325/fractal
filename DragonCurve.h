#ifndef DRAGONCURVE_H
#define DRAGONCURVE_H

#include "Graph_lib/Graph.h"  // For Point class
#include "Vec2d.h"
#include <vector>

class DragonCurve {
private:
    std::vector<Vec2d> segments;
    int iteration;
    
public:
    // Constructor
    DragonCurve(Graph_lib::Point start, Graph_lib::Point end);
    
    // Generate next iteration
    void generate_next();
    
    // Get points for drawing
    std::vector<Graph_lib::Point> get_points() const;
    
    // Get iteration count
    int get_iteration() const;
    
    // Get number of segments
    size_t size() const;
    
    // Get individual segments
    const std::vector<Vec2d>& get_segments() const;
    
    // Clear and restart
    void clear();
    void init(Graph_lib::Point start, Graph_lib::Point end);
};

#endif // DRAGONCURVE_H