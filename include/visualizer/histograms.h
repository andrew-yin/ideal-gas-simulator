#pragma once

#include <core/simulator.h>

#include "cinder/gl/gl.h"

namespace idealgas {

class Histograms {
 public:
  Histograms(Simulator& simulator, const std::vector<glm::vec2>& top_left_corners,
            const double graph_width, const double graph_height);

  /** Cinder-related methods */
  void Draw() const;

 private:
  std::vector<glm::vec2> top_left_corners_;
  double graph_width_;
  double graph_height_;
  Simulator& simulator_;

  void DrawBorders() const;
};

}  // namespace idealgas