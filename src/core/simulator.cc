#include <core/simulator.h>

#include "cinder/Rand.h"

namespace idealgas {

Simulator::Simulator() {
  cinder::Rand::randomize();
};

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

void Simulator::AddRandomSmallParticle() {
  double radius = kPlaneWidth/100;
  double mass = kPlaneWidth/100;
  ci::Color color("red");

  /* Position calculated at random anywhere on the coordinate plane accounting
     for radius size */
  double pos_x = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  double pos_y = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  glm::vec2 pos(pos_x, pos_y);

  /* Velocity calculated at random but maximum scaled down based on radius */
  double scale_factor = 0.5;
  double vel_x = cinder::Rand::randFloat(radius * scale_factor);
  double vel_y = cinder::Rand::randFloat(radius * scale_factor);
  glm::vec2 vel(vel_x, vel_y);

  particles_.push_back(Particle(radius, mass, pos, vel, color));
}

void Simulator::AddRandomMediumParticle() {
  double radius = kPlaneWidth/100 * 1.25;
  double mass = kPlaneWidth/100 * 2;
  ci::Color color("blue");

  double pos_x = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  double pos_y = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  glm::vec2 pos(pos_x, pos_y);

  double scale_factor = 0.375;
  double vel_x = cinder::Rand::randFloat(radius * scale_factor);
  double vel_y = cinder::Rand::randFloat(radius * scale_factor);
  glm::vec2 vel(vel_x, vel_y);

  particles_.push_back(Particle(radius, mass, pos, vel, color));
}

void Simulator::AddRandomLargeParticle() {
  double radius = kPlaneWidth/100 * 1.5;
  double mass = kPlaneWidth/100 * 3;
  ci::Color color("green");

  double pos_x = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  double pos_y = cinder::Rand::randFloat(radius, kPlaneWidth - radius);
  glm::vec2 pos(pos_x, pos_y);

  double scale_factor = 0.25;
  double vel_x = cinder::Rand::randFloat(radius * scale_factor);
  double vel_y = cinder::Rand::randFloat(radius * scale_factor);
  glm::vec2 vel(vel_x, vel_y);

  particles_.push_back(Particle(radius, mass, pos, vel, color));
}

const std::vector<Particle>& Simulator::GetParticles() const {
  return particles_;
}

size_t Simulator::GetNumParticles() const {
  return particles_.size();
}

void Simulator::UpdateWallCollisions() {
  for (Particle& particle : particles_) {
    if (IsAgainstHorizontalWall(particle)) {
      glm::vec2 old_vel = particle.GetVelocity();
      glm::vec2 new_vel(-old_vel.x, old_vel.y);
      particle.SetVelocity(new_vel);
    }

    if (IsAgainstVerticalWall(particle)) {
      glm::vec2 old_vel = particle.GetVelocity();
      glm::vec2 new_vel(old_vel.x, -old_vel.y);
      particle.SetVelocity(new_vel);
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
  glm::vec2 v1 = p1.GetVelocity();
  glm::vec2 x2 = p2.GetPosition();
  glm::vec2 v2 = p2.GetVelocity();
  float m1 = p1.GetMass();
  float m2 = p2.GetMass();

  glm::vec2 v1_prime =
      v1 - ((2 * m2) / (m1 + m2) * (glm::dot(v1 - v2, x1 - x2)) /
            (glm::length(x1 - x2) * glm::length(x1 - x2))) *
               (x1 - x2);
  glm::vec2 v2_prime =
      v2 - ((2 * m1) / (m1 + m2) * (glm::dot(v2 - v1, x2 - x1)) /
            (glm::length(x2 - x1) * glm::length(x2 - x1)) * (x2 - x1));

  return std::pair<glm::vec2, glm::vec2>(v1_prime, v2_prime);
}

}  // namespace idealgas