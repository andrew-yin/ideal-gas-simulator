#pragma once

#include <string>

#include "cinder/gl/gl.h"

namespace idealgas {

/**
 * A representation of a gas particle with radius, position, and velocity.
 */
class Particle {
 public:
  /**
   * Creates a new gas particle.
   *
   * @param radius    The radius of the particle.
   * @param mass      The mass of the particle.
   * @param position  A 2D vector representing the particle's current position.
   * @param velocity  A 2D vector representing the particle's current velocity.
   */
  Particle(double radius, double mass, const glm::vec2& position, const glm::vec2& velocity);

  /**
   * Updates the position of the object by a unit of time based on its current
   * velocity.
   */
  void UpdatePosition();

  /**
   * Reverses the sign of the specified component of the particle's velocity.
   * Used when the particle is colliding with a wall. If the component specified
   * is not a valid component of velocity, the particle's velocity will remain
   * the same.
   *
   * @param component  The component (e.g. x or y) of velocity whose sign is to
   *                   be inverted.
   */
  void InvertVelocityComponent(const char component);

  bool operator==(const Particle& other) const;

  /** Necessary getters and setters */
  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  double GetRadius() const;
  double GetMass() const;
  void SetVelocity(const glm::vec2& velocity);

 private:
  double radius_;
  double mass_;
  glm::vec2 position_;
  glm::vec2 velocity_;
};

}  // namespace idealgas