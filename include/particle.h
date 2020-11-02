#pragma once

#include <string>

#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {
 public:
  Particle();
  Particle(double radius, const glm::vec2& position,
           const glm::vec2& velocity);

  glm::vec2 GetPosition() const;
  glm::vec2 GetVelocity() const;
  double GetRadius() const;

  void SetPosition(glm::vec2 position);
  void SetVelocity(glm::vec2 velocity);

  void UpdatePosition();

 private:
  double radius_;
  glm::vec2 position_;
  glm::vec2 velocity_;
};

}  // namespace idealgas