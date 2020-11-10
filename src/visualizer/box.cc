#include <visualizer/box.h>

namespace idealgas {

Box::Box(Simulator& simulator, const glm::vec2& top_left_corner,
         double box_length)
    : top_left_corner_(top_left_corner),
      box_length_(box_length),
      simulator_(simulator) {
}

void Box::Draw() const {
  DrawBox();
  DrawParticles();
}

void Box::DrawBox() const {
  glm::vec2 pixel_bottom_right =
      top_left_corner_ + glm::vec2(box_length_, box_length_);
  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right);

  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(pixel_bounding_box);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box, 1.0);
}

void Box::DrawParticles() const {
  /* The conversion factor between the dimensions used by the simulation and
     the pixel width specified for the box */
  double scale_factor = box_length_ / simulator_.kPlaneWidth;

  for (const Particle& particle : simulator_.GetParticles()) {
    /* Scale the radius to be in terms of pixels */
    double radius = particle.GetRadius() * scale_factor;

    /* Re-scale the position of the particle in terms of pixel position
       in the application window and re-orient the cooridinate such that
       the y value increases from bottom to top */
    glm::vec2 position = particle.GetPosition();
    position.y = simulator_.kPlaneWidth - position.y;
    position *= scale_factor;
    position += top_left_corner_;

    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(position, radius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedCircle(position, radius, 1.0, -1);
  }
}

}  // namespace idealgas