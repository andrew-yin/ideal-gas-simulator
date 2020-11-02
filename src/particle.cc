#include <particle.h>

namespace idealgas {

Particle::Particle()
    : radius_(1), position_(50, 50) {
}

Particle::Particle(double mass, double radius, const glm::vec2& position,
                   const glm::vec2& velocity)
    : radius_(radius), position_(position) {
}

glm::vec2 Particle::GetPosition() const {
  return position_;
}

double Particle::GetRadius() const {
  return radius_;
}

}  // namespace idealgas
