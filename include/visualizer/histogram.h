#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

class Histogram {
 public:
  Histogram(const glm::vec2& top_left_corner, const double box_width,
            const double box_height);

  /** Cinder-related methods */
  void Draw() const;
  void Update();

 private:
  glm::vec2 top_left_corner_;
  double box_width_;
  double box_height_;
};

}  // namespace idealgas
