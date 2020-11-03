#include <simulator.h>

namespace idealgas {

Simulator::Simulator() = default;

void Simulator::AddParticle(const Particle& particle) {
  particles_.push_back(particle);
}

std::vector<Particle>::iterator Simulator::begin() {
  return particles_.begin();
}

std::vector<Particle>::iterator Simulator::end() {
  return particles_.end();
}

void Simulator::Update() {
  UpdateWallCollisions();
  UpdateParticleCollisions();
  UpdatePositions();
}

void Simulator::UpdateWallCollisions() {
  for (Particle& particle : particles_) {
    if (IsAgainstHorizontalWall(particle)) {
      particle.InvertVelocityComponent('x');
    }

    if (IsAgainstVerticalWall(particle)) {
      particle.InvertVelocityComponent('y');
    }
  }
}

bool Simulator::IsAgainstHorizontalWall(const Particle& particle) {
  glm::vec2 position = particle.GetPosition();
  glm::vec2 velocity = particle.GetVelocity();

  double left_bound = particle.GetRadius();
  double right_bound = kPlaneWidth - particle.GetRadius();

  return (position.x <= left_bound && velocity.x <= 0) ||
         (position.x >= right_bound && velocity.x >= 0);
}

bool Simulator::IsAgainstVerticalWall(const Particle& particle) {
  glm::vec2 position = particle.GetPosition();
  glm::vec2 velocity = particle.GetVelocity();

  double top_bound = kPlaneWidth - particle.GetRadius();
  double bottom_bound = particle.GetRadius();

  return (position.y <= bottom_bound && velocity.y <= 0) ||
         (position.y >= top_bound && velocity.y >= 0);
}

void Simulator::UpdateParticleCollisions() {
  if (particles_.size() > 0) {
    for (size_t i = 0; i < particles_.size() - 1; i++) {
      Particle& particle1 = particles_[i];
      for (size_t j = i + 1; j < particles_.size(); j++) {
        Particle& particle2 = particles_[j];
        if (IsCollision(particle1, particle2)) {
          std::pair<glm::vec2, glm::vec2> new_velocities =
              ComputePostCollisionVelocities(particle1, particle2);
          particle1.SetVelocity(new_velocities.first);
          particle2.SetVelocity(new_velocities.second);
        }
      }
    }
  }
}

void Simulator::UpdatePositions() {
  for (Particle& particle : particles_) {
    particle.UpdatePosition();
  }
}

bool Simulator::IsCollision(const Particle& p1, const Particle& p2) {
  glm::vec2 x1 = p1.GetPosition();
  glm::vec2 x2 = p2.GetPosition();
  glm::vec2 v1 = p1.GetVelocity();
  glm::vec2 v2 = p2.GetVelocity();

  bool are_touching = glm::length(x1 - x2) <= p1.GetRadius() + p2.GetRadius();
  bool are_moving_towards_each_other = glm::dot(v1 - v2, x1 - x2) < 0;

  return are_touching && are_moving_towards_each_other;
}
std::pair<glm::vec2, glm::vec2> Simulator::ComputePostCollisionVelocities(
    const Particle& p1, const Particle& p2) {
  glm::vec2 x1 = p1.GetPosition();
  glm::vec2 x2 = p2.GetPosition();
  glm::vec2 v1 = p1.GetVelocity();
  glm::vec2 v2 = p2.GetVelocity();

  glm::vec2 v1_prime = v1 - (glm::dot(v1 - v2, x1 - x2)) /
                                (glm::length(x1 - x2) * glm::length(x1 - x2)) *
                                (x1 - x2);
  glm::vec2 v2_prime = v2 - (glm::dot(v2 - v1, x2 - x1)) /
                                (glm::length(x2 - x1) * glm::length(x2 - x1)) *
                                (x2 - x1);

  return std::pair<glm::vec2, glm::vec2>(v1_prime, v2_prime);
}
void Simulator::Reset() {
  particles_.clear();
}

}  // namespace idealgas