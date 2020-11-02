#pragma once

#include <vector>

#include "particle.h"

namespace idealgas {

class Simulator {
 public:
  Simulator();
  void AddParticle(const Particle& particle);

  std::vector<Particle>::iterator begin();
  std::vector<Particle>::iterator end();
  void Update();
  const double kPlaneWidth = 100;

 private:
  std::vector<Particle> particles_;
};

}  // namespace idealgas