#include <simulator.h>

namespace idealgas {

Simulator::Simulator() = default;

void Simulator::AddParticle(const Particle& particle) {
  particles_.push_back(particle);
}

std::vector<Particle> Simulator::GetParticles() const {
  return particles_;
}

void Simulator::Update() {
  for (Particle& particle: particles_) {
    glm::vec2 position = particle.GetPosition();
    glm::vec2 velocity = particle.GetVelocity();
    if (position.x >= 100 || position.x <= 0) {
      glm::vec2 new_velocity(-velocity.x, velocity.y);
      particle.SetVelocity(new_velocity);
    }
    else if (position.y >= 100 || position.y <= 0) {
      glm::vec2 new_velocity(velocity.x, -velocity.y);
      particle.SetVelocity(new_velocity);
    }
  }

  for (Particle& particle: particles_) {
    glm::vec2 position = particle.GetPosition();
    glm::vec2 velocity = particle.GetVelocity();
    particle.SetPosition(position + velocity);
  }
}

}
