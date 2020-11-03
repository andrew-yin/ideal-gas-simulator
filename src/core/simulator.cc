#include <core/simulator.h>

#include "cinder/Rand.h"

namespace idealgas {

Simulator::Simulator() = default;

void Simulator::Update() {
  UpdateWallCollisions();
  UpdateParticleCollisions();
  UpdatePositions();
}

void Simulator::Reset() {
  particles_.clear();
}

void Simulator::AddParticle(const Particle& particle) {
  particles_.push_back(particle);
}

void Simulator::AddRandomParticle() {
  /* Radius will be 1% of the coordinate plane size as a standard */
  double radius = kPlaneWidth / 100;

  /* Seed random number generator */
  cinder::Rand::randomize();

  /* Position calculated at random anywhere on the coordinate plane accounting
     for radius size */
  double pos_x = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  double pos_y = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  glm::vec2 pos(pos_x, pos_y);

  /* Velocity calculated at random such that individual components do not exceed
     half the size of the radius */
  double vel_x = cinder::Rand::randFloat(radius * 0.5);
  double vel_y = cinder::Rand::randFloat(radius * 0.5);
  glm::vec2 vel(vel_x, vel_y);

  particles_.push_back(Particle(radius, pos, vel));
}

const std::vector<Particle>& Simulator::GetParticles() const {
  return particles_;
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

void Simulator::UpdateParticleCollisions() {
  /* Since we use index-based iteration, first ensure there are enough
     particles to check for collisions */
  if (particles_.size() > 1) {
    for (size_t i = 0; i < particles_.size() - 1; i++) {
      Particle& p1 = particles_[i];

      /* Search every pair */
      for (size_t j = i + 1; j < particles_.size(); j++) {
        Particle& p2 = particles_[j];

        /* Update velocities if the pair of particles are in contact */
        if (IsCollision(p1, p2)) {
          auto new_velocities = ComputePostCollisionVelocities(p1, p2);
          p1.SetVelocity(new_velocities.first);
          p2.SetVelocity(new_velocities.second);
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

bool Simulator::IsAgainstHorizontalWall(const Particle& particle) const {
  glm::vec2 position = particle.GetPosition();
  glm::vec2 velocity = particle.GetVelocity();

  double left_bound = particle.GetRadius();
  double right_bound = kPlaneWidth - particle.GetRadius();

  /* Check if in contact with a wall and the particle is moving towards it */
  return (position.x <= left_bound && velocity.x <= 0) ||
         (position.x >= right_bound && velocity.x >= 0);
}

bool Simulator::IsAgainstVerticalWall(const Particle& particle) const {
  glm::vec2 position = particle.GetPosition();
  glm::vec2 velocity = particle.GetVelocity();

  double top_bound = kPlaneWidth - particle.GetRadius();
  double bottom_bound = particle.GetRadius();

  /* Check if in contact with a wall and the particle is moving towards it */
  return (position.y <= bottom_bound && velocity.y <= 0) ||
         (position.y >= top_bound && velocity.y >= 0);
}

bool Simulator::IsCollision(const Particle& p1, const Particle& p2) const {
  glm::vec2 x1 = p1.GetPosition();
  glm::vec2 x2 = p2.GetPosition();
  glm::vec2 v1 = p1.GetVelocity();
  glm::vec2 v2 = p2.GetVelocity();

  bool are_touching = glm::length(x1 - x2) <= p1.GetRadius() + p2.GetRadius();
  bool are_moving_towards_each_other = glm::dot(v1 - v2, x1 - x2) < 0;

  return are_touching && are_moving_towards_each_other;
}

std::pair<glm::vec2, glm::vec2> Simulator::ComputePostCollisionVelocities(
    const Particle& p1, const Particle& p2) const {
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

}  // namespace idealgas