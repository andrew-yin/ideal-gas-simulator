#include "visualizer/histograms.h"

namespace idealgas {

Histograms::Histograms(Simulator& simulator,
                       const std::vector<glm::vec2>& top_left_corners,
                       const double graph_width, const double graph_height)
    : top_left_corners_(top_left_corners),
      graph_width_(graph_width),
      graph_height_(graph_height),
      simulator_(simulator) {
}

void Histograms::Draw() const {
  DrawBorders();
}

void Histograms::DrawBorders() const {
  for (glm::vec2 top_left_corner: top_left_corners_) {
    glm::vec2 pixel_bottom_right =
        top_left_corner + glm::vec2(graph_width_, graph_height_);

    ci::Rectf pixel_bounding_box(top_left_corner, pixel_bottom_right);
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRect(pixel_bounding_box);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRect(pixel_bounding_box, 1.0);
  }
}

}  // namespace idealgas