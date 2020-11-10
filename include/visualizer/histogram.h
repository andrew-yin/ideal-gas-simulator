#pragma once

#include <core/simulator.h>

#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 public:
  Histogram(Simulator& simulator, const glm::vec2& top_left_corner,
            const double box_width, const double box_height);

  /** Cinder-related methods */
  void Draw() const;

 private:
  glm::vec2 top_left_corner_;
  double box_width_;
  double box_height_;
  Simulator& simulator_;
};

}  // namespace idealgas