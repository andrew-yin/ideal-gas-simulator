#pragma once

#include <core/simulator.h>

#include "cinder/gl/gl.h"

namespace idealgas {

class Histograms {
 public:
  Histograms(Simulator& simulator,
             const std::vector<glm::vec2>& top_left_corners,
             const double graph_width, const double graph_height);

  /** Cinder-related methods */
  void Setup();
  void Draw() const;

 private:
  std::vector<glm::vec2> top_left_corners_;
  double graph_width_;
  double graph_height_;
  std::vector<double> intervals_;
  Simulator& simulator_;

  void DrawBorders() const;
  void DrawGraphs() const;

  std::vector<size_t> GetFrequencies(const std::vector<double>& speeds) const;

  const double kMaxSpeed = 1.5;
  const size_t kNumIntervals = 20;
  const double kIntervalWidth = kMaxSpeed / kNumIntervals;

  void DrawHistogramBars(const glm::vec2& top_left_corner,
                         const std::vector<size_t>& frequencies,
                         size_t max_frequency, const cinder::Color& color) const;
};

}  // namespace idealgas