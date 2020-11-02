#include <simulator.h>

namespace idealgas {

Simulator::Simulator() = default;

void Simulator::AddParticle(const Particle& particle) {
  for (size_t i = 5; i <= 90; i++) {
    particles_.push_back(Particle(1, glm::vec2(i, i), glm::vec2(0.25, 0.5)));
  }
  for (size_t i = 5; i <= 90; i++) {
    particles_.push_back(Particle(1, glm::vec2(i, i), glm::vec2(-0.25, 0.5)));
  }
  for (size_t i = 5; i <= 90; i++) {
    particles_.push_back(Particle(1, glm::vec2(i, i), glm::vec2(0.25, -0.25)));
  }
  for (size_t i = 5; i <= 90; i++) {
    particles_.push_back(Particle(1, glm::vec2(i, i), glm::vec2(0.25, 0.5)));
  }
  for (size_t i = 5; i <= 90; i++) {
    particles_.push_back(Particle(1, glm::vec2(i, i), glm::vec2(-0.25, 0.5)));
  }
  for (size_t i = 5; i <= 90; i++) {
    particles_.push_back(Particle(1, glm::vec2(i, i), glm::vec2(0.25, -0.25)));
  }
}

std::vector<Particle> Simulator::GetParticles() const {
  return particles_;
}

void Simulator::Update() {
  for (Particle& particle : particles_) {
    glm::vec2 position = particle.GetPosition();
    glm::vec2 velocity = particle.GetVelocity();
    if ((position.x >= 100 - particle.GetRadius() && velocity.x >= 0) ||
        (position.x <= particle.GetRadius() && velocity.x <= 0)) {
      velocity = particle.GetVelocity();
      glm::vec2 new_velocity(-velocity.x, velocity.y);
      particle.SetVelocity(new_velocity);
    }
    if ((position.y >= 100 - particle.GetRadius() && velocity.y >= 0) ||
        (position.y <= particle.GetRadius() && velocity.y <= 0)) {
      velocity = particle.GetVelocity();
      glm::vec2 new_velocity(velocity.x, -velocity.y);
      particle.SetVelocity(new_velocity);
    }
  }

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

  for (Particle& particle : particles_) {
    glm::vec2 position = particle.GetPosition();
    glm::vec2 velocity = particle.GetVelocity();
    particle.SetPosition(position + velocity);
  }
}

}  // namespace idealgas