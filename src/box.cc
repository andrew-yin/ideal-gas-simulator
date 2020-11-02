#include <box.h>

using glm::vec2;

namespace idealgas {

Box::Box(const glm::vec2& top_left_corner, double box_length)
    : top_left_corner_(top_left_corner),
      box_length_(box_length),
      scale_factor_(box_length_ / simulator_.kPlaneWidth) {
  simulator_.AddParticle(Particle());
}

void Box::Draw() {
  vec2 pixel_bottom_right = top_left_corner_ + vec2(box_length_, box_length_);

  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);

  for (const Particle& particle : simulator_) {
    double radius = particle.GetRadius() * scale_factor_;

    glm::vec2 position = particle.GetPosition();
    position *= scale_factor_;
    position += top_left_corner_;

    ci::gl::color(ci::Color("red"));
    ci::gl::drawSolidCircle(position, radius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedCircle(position, radius, 1.0, -1);
  }
}

void Box::Update() {
  simulator_.Update();
}

}  // namespace idealgas
