#pragma once

#include <vector>

#include "cinder/gl/gl.h"
#include "core/particle.h"

namespace idealgas {

/**
 * A control object used to simulate the interaction between particles.
 *
 * The simulation is run on a 100x100 coordinate plane with (0,0) at the lower
 * left corner of the plane and increasing x and y from left to right and bottom
 * to top, respectively.
 */
class Simulator {
 public:
  /** Default constructor */
  Simulator();

  /** Updates the current state of the particles' positions and velocities */
  void Update();

  /** Resets the simulation to zero particles */
  void Reset();

  /** Adds the specified particle to the simulation */
  void AddParticle(const Particle& particle);

  /**
   * Methods to add a particle with specified size and random position/velocity
   * to the simulation
   */
  /** Mass and radius both 1% of simulator width */
  void AddRandomSmallParticle();
  /** Mass 2%, radius 1.5% of simulator width */
  void AddRandomMediumParticle();
  /** Mass 3%, radius 2% of simulator width */
  void AddRandomLargeParticle();

  const std::vector<Particle>& GetParticles() const;
  size_t GetNumParticles() const;

  /** The width of the coordinate plane used for the simulation */
  const double kPlaneWidth = 100;

  /** Returns a vector of the speeds of particles filtered by size, used for
   *  histogram computation */
  std::vector<double> GetSmallParticleSpeeds() const;
  std::vector<double> GetMediumParticleSpeeds() const;
  std::vector<double> GetLargeParticleSpeeds() const;

  /** Measurements for the small, medium, and large particles */
  const double kSmallMass = kPlaneWidth / 100;
  const double kSmallRadius = kPlaneWidth / 100;
  const ci::Color kSmallColor = ci::Color("red");
  const double kMediumMass = kPlaneWidth / 100 * 2;
  const double kMediumRadius = kPlaneWidth / 100 * 1.25;
  const ci::Color kMediumColor = ci::Color("blue");
  const double kLargeMass = kPlaneWidth / 100 * 4;
  const double kLargeRadius = kPlaneWidth / 100 * 1.5;
  const ci::Color kLargeColor = ci::Color("green");

 private:
  std::vector<Particle> particles_;

  /** Helper methods used during updating the state of the simulation */
  void UpdateWallCollisions();
  void UpdateParticleCollisions();
  void UpdatePositions();

  /**
   * Utility methods used to help determine whether individual particles
   * are in certain states
   */
  bool IsAgainstVerticalWall(const Particle& particle) const;
  bool IsAgainstHorizontalWall(const Particle& particle) const;
  bool IsCollision(const Particle& particle1, const Particle& particle2) const;

  /**
   * Computes the post-collision of two particles that are assumed to be in
   * contact with each other.
   *
   * @param p1  The first particle specified
   * @param p2  The second particle specified
   * @return    A std::pair of the post-collision velocities.
   *            The first element in the pair is the post-collision velocity of
   *            particle1.
   *            The second element in the pair is the post-collision velocity
   *            of particle2.
   */
  std::pair<glm::vec2, glm::vec2> ComputePostCollisionVelocities(
      const Particle& p1, const Particle& p2) const;

  /** Returns true if the specified particle is of a certain size, false
   * otherwise */
  bool IsSmall(const Particle& p) const;
  bool IsMedium(const Particle& p) const;
  bool IsLarge(const Particle& p) const;
};

}  // namespace idealgas