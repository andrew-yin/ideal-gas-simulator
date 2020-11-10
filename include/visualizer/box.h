#pragma once

#include <cinder/app/KeyEvent.h>

#include "cinder/gl/gl.h"
#include "core/simulator.h"

namespace idealgas {

/**
 * A box which is to be displayed in the Cinder application that visualizes
 * the state of the particles based on ideal gas properties
 */
class Box {
 public:
  /**
   * Creates a box for gas particles.
   *
   * @param Simulator        A reference to a simulator used to draw data from
   * @param top_left_corner  The screen coordinates for fhe top left corner of
   *                         the box
   * @param box_length       The length the box should be drawn, in pixels
   */
  Box(Simulator& simulator, const glm::vec2& top_left_corner,
      const double box_length);

  /** Cinder-related methods */
  void Draw() const;

  /**
   * Returns the number of particles currently being drawn to the application
   */
  const size_t& GetNumParticles() const;

 private:
  glm::vec2 top_left_corner_;
  double box_length_;
  Simulator& simulator_;

  /** Helper methods for drawing the box onto the Cinder application */
  void DrawBox() const;
  void DrawParticles() const;
};

}  // namespace idealgas