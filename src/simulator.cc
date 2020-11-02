#include <simulator.h>

namespace idealgas {

Simulator::Simulator() = default;

void Simulator::AddParticle(const Particle& particle) {
  particles_.push_back(particle);
}

std::vector<Particle> Simulator::GetParticles() const {
  return particles_;
}


}
