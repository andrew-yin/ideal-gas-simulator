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

bool Simulator::IsAgainstHorizontalWall(Particle particle) {
  glm::vec2 position = particle.GetPosition();
  glm::vec2 velocity = particle.GetVelocity();

  double left_bound = particle.GetRadius();
  double right_bound = kPlaneWidth - particle.GetRadius();

  return (position.x <= left_bound && velocity.x <= 0) ||
         (position.x >= right_bound && velocity.x >= 0);
}

bool Simulator::IsAgainstVerticalWall(Particle particle) {
  glm::vec2 position = particle.GetPosition();
  glm::vec2 velocity = particle.GetVelocity();

  double top_bound = kPlaneWidth - particle.GetRadius();
  double bottom_bound = particle.GetRadius();

  return (position.y <= bottom_bound && velocity.y <= 0) ||
      (position.y >= top_bound && velocity.y >= 0);
}

void Simulator::UpdateParticleCollisions() {
  for (size_t i = 0; i < particles_.size() - 1; i++) {
    Particle& particle1 = particles_[i];
    glm::vec2 particle1_velocity = particle1.GetVelocity();
    glm::vec2 particle1_position = particle1.GetPosition();

    for (size_t j = i + 1; j < particles_.size(); j++) {
      Particle& particle2 = particles_[j];
      glm::vec2 particle2_velocity = particle2.GetVelocity();
      glm::vec2 particle2_position = particle2.GetPosition();

      if ((glm::length(particle1_position - particle2_position) <=
           particle1.GetRadius() + particle2.GetRadius()) &&
          (glm::dot(particle1_velocity - particle2_velocity,
                    particle1_position - particle2_position) < 0)) {
        glm::vec2 x1_minus_x2 = particle1_position - particle2_position;
        x1_minus_x2 *= (glm::dot(particle1_velocity - particle2_velocity,
                                 particle1_position - particle2_position)) /
                       (glm::length(particle1_position - particle2_position) *
                        glm::length(particle1_position - particle2_position));

        glm::vec2 x2_minus_x1 = particle2_position - particle1_position;
        x2_minus_x1 *= (glm::dot(particle2_velocity - particle1_velocity,
                                 particle2_position - particle1_position)) /
                       (glm::length(particle2_position - particle1_position) *
                        glm::length(particle2_position - particle1_position));

        particle1.SetVelocity(particle1_velocity - x1_minus_x2);
        particle2.SetVelocity(particle2_velocity - x2_minus_x1);
      }
    }
  }
}

void Simulator::UpdatePositions() {
  for (Particle& particle : particles_) {
    particle.UpdatePosition();
  }
}

}  // namespace idealgas