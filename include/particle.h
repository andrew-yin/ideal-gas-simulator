#pragma once

#include <string>

#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {
 public:
  Particle(double radius, const glm::vec2& position,
           const glm::vec2& velocity);

  glm::vec2 GetPosition() const;
  glm::vec2 GetVelocity() const;
  double GetRadius() const;

  void SetVelocity(glm::vec2 velocity);

  void UpdatePosition();

  void InvertVelocityComponent(char component);
 private:
  double radius_;
  glm::vec2 position_;
  glm::vec2 velocity_;
};

}  // namespace idealgas