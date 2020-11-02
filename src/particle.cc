#include <particle.h>

namespace idealgas {

Particle::Particle()
    : radius_(1), position_(50, 50), velocity_(0.25, 1.5) {
}

Particle::Particle(double radius, const glm::vec2& position,
                   const glm::vec2& velocity)
    : radius_(radius), position_(position), velocity_(velocity) {
}

glm::vec2 Particle::GetPosition() const {
  return position_;
}

glm::vec2 Particle::GetVelocity() const {
  return velocity_;
}

double Particle::GetRadius() const {
  return radius_;
}

void Particle::SetPosition(glm::vec2 position) {
  position_ = position;
}

void Particle::SetVelocity(glm::vec2 velocity) {
  velocity_ = velocity;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

void Particle::InvertVelocityComponent(char component) {
  switch (component) {
    case 'x':
      velocity_.x = -velocity_.x;
      break;
    case 'y':
      velocity_.y = -velocity_.y;
      break;
    default:
      break;
  }
}

}  // namespace idealgas