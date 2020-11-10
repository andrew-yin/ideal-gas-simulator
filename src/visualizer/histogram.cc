#include "visualizer/histogram.h"

namespace idealgas {

Histogram::Histogram(Simulator& simulator, const glm::vec2& top_left_corner,
                     const double box_width, const double box_height)
    : top_left_corner_(top_left_corner),
      box_width_(box_width),
      box_height_(box_height) simulator_(simulator) {
}

void Histogram::Draw() const {
  glm::vec2 pixel_bottom_right =
      top_left_corner_ + glm::vec2(box_width_, box_height_);
  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box, 1.0);
}

}  // namespace idealgas