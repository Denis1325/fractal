#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H> 
#include <FL/fl_draw.H>  
#include <iostream>
#include "Settings.h"
#include "DragonCurve.h"


static int click_count = 0;
static DragonCurve* dragon_curve = nullptr;

class DrawingWindow : public Fl_Window {
private:
    DragonCurve* curve;
    
public:
    DrawingWindow(int w, int h, const char* title, DragonCurve* c) 
        : Fl_Window(w, h, title), curve(c) {
        color(FL_WHITE);  // background color
    }
    
    void draw() override {
        Fl_Window::draw();
        
        // Draw the dragon curve
        if (curve && curve->size() > 0) {
            const auto& points = curve->get_points();
            
            if (points.size() >= 2) {
                fl_color(FL_BLACK);
                
                // Draw lines through all points
                for (size_t i = 0; i < points.size() - 1; i++) {
                    fl_line(points[i].x, points[i].y, 
                            points[i + 1].x, points[i + 1].y);
                }
                
            }
        }
    }
};

void next_step(Fl_Widget* widget, void* data) {
    click_count++;
    
    Fl_Box* counter_label = static_cast<Fl_Box*>(data);
    
    std::string new_text = "Iteration: " + std::to_string(click_count);
    counter_label->copy_label(new_text.c_str());
    counter_label->redraw();
    
    // Generate next iteration of dragon curve
    if (dragon_curve) {
        dragon_curve->generate_next();
        
        std::cout << "Iteration " << dragon_curve->get_iteration() 
                  << " - Points: " << dragon_curve->get_points().size() << "\n";
        
        Fl_Widget* win = counter_label->window();
        if (win) {
            win->redraw();
        }
    }
}

int main() {
    // Create the dragon curve with initial segment
    Graph_lib::Point start(500, 800);
    Graph_lib::Point end(500, 300);
    dragon_curve = new DragonCurve(start, end);
    
    // Create custom window that can draw
    DrawingWindow* win = new DrawingWindow(windowWidth, windowHeight, 
                                          "Dragon Curve", dragon_curve);
    
    // Create UI elements
    Fl_Button* btn = new Fl_Button(20, 20, 120, 30, "Next Iteration");
    Fl_Box* counter_label = new Fl_Box(20, 60, 120, 30, "Iteration: 0");
    counter_label->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    counter_label->box(FL_DOWN_BOX);
    
    btn->callback(next_step, counter_label);
    
    win->end();
    win->show();
    
    int result = Fl::run();
    
    delete dragon_curve;
    
    return result;
}