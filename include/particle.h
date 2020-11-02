#pragma once

#include <string>

#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {
 public:
  Particle();
  Particle(double mass, double radius, const glm::vec2& position,
           const glm::vec2& velocity);

 private:
  double mass_;
  double radius_;
  glm::vec2 position_;
  glm::vec2 velocity_;
};

}  // namespace idealgas