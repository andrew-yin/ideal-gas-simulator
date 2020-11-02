#pragma once

#include <vector>

#include "particle.h"

namespace idealgas {

class Simulator {
 public:
  Simulator();
  void AddParticle(const Particle& particle);

 private:
  std::vector<Particle> particles_;
};

}  // namespace idealgas