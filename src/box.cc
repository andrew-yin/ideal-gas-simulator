#include <box.h>

using glm::vec2;

namespace idealgas {

Box::Box(const glm::vec2& top_left_corner, double box_length)
    : top_left_corner_(top_left_corner),
      box_length_(box_length),
      scale_factor_(box_length_ / simulator_.kPlaneWidth) {
}

void Box::Draw() {
  DrawBox();
  DrawParticles();
}

void Box::Update() {
  simulator_.Update();
}

void Box::DrawBox() {
  vec2 pixel_bottom_right = top_left_corner_ + vec2(box_length_, box_length_);
  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box, 1.0);
}

void Box::DrawParticles() {
  for (const Particle& particle : simulator_) {
    double radius = particle.GetRadius() * scale_factor_;

    glm::vec2 position = particle.GetPosition();
    position.y = simulator_.kPlaneWidth - position.y;
    position *= scale_factor_;
    position += top_left_corner_;

    ci::gl::color(ci::Color("red"));
    ci::gl::drawSolidCircle(position, radius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedCircle(position, radius, 1.0, -1);
  }
}

void Box::AddRandomParticle() {
  double radius = 1;
  double pos_x =
      radius +
          (double) (rand()) /
          ((double) (RAND_MAX / ((simulator_.kPlaneWidth - radius)*0.5)));
  double pos_y =
      radius +
      (double)(rand()) /
          ((double)(RAND_MAX / ((simulator_.kPlaneWidth - radius)*0.5)));
  double vel_x =
      (double)(rand()) / ((double)(RAND_MAX / (radius*0.8)));
  double vel_y =
      (double)(rand()) / ((double)(RAND_MAX / (radius*0.8)));

  simulator_.AddParticle(
      Particle(radius, glm::vec2(pos_x, pos_y), glm::vec2(vel_x, vel_y)));
}

void Box::Reset() {
  simulator_.Reset();
}

}  // namespace idealgas