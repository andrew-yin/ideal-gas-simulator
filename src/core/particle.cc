#include <core/particle.h>

namespace idealgas {

Particle::Particle(double radius, double mass, const glm::vec2& position,
                   const glm::vec2& velocity)
    : radius_(radius), mass_(mass), position_(position), velocity_(velocity) {
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

const glm::vec2& Particle::GetPosition() const {
  return position_;
}

const glm::vec2& Particle::GetVelocity() const {
  return velocity_;
}

double Particle::GetRadius() const {
  return radius_;
}

double Particle::GetMass() const {
  return mass_;
}

void Particle::SetVelocity(const glm::vec2& velocity) {
  velocity_ = velocity;
}

bool Particle::operator==(const Particle& other) const {
  return (this->GetRadius() == other.GetRadius()) &&
         (this->GetMass() == other.GetMass()) &&
         (this->GetPosition() == other.GetPosition()) &&
         (this->GetVelocity() == other.GetVelocity());
}

}  // namespace idealgas