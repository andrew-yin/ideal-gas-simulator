#pragma once

#include <vector>

#include "particle.h"
#include "cinder/gl/gl.h"

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

  void UpdateWallCollisions();
  void UpdateParticleCollisions();
  void UpdatePositions();
  bool IsAgainstVerticalWall(const Particle& particle);
  bool IsAgainstHorizontalWall(const Particle& particle);
  bool IsCollision(const Particle& particle1, const Particle& particle2);
  std::pair<glm::vec2, glm::vec2> ComputePostCollisionVelocities(const Particle& p1,
                                                       const Particle& p2);
};

}  // namespace idealgas