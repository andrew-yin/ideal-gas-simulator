#include <box.h>

using glm::vec2;

namespace idealgas {

Box::Box(const glm::vec2& top_left_corner, double box_length)
    : top_left_corner_(top_left_corner), box_length_(box_length) {

  Simulator.add(Particle());
}

void Box::Draw() const {
  vec2 pixel_bottom_right = top_left_corner_ + vec2(box_length_, box_length_);

  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box, 10.0);

}

}  // namespace idealgas
