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
  std::vector<double> speed_intervals_;
  std::vector<size_t> freq_intervals_;
  Simulator& simulator_;

  void DrawBorders() const;
  void DrawGraphs() const;

  std::vector<size_t> GetSpeedFrequencies(const std::vector<double>& speeds) const;

  const size_t kMaxFrequency = 15;
  const size_t kNumFreqIntervals = 5;
  const size_t kFreqIntervalWidth = kMaxFrequency / kNumFreqIntervals;

  const double kMaxSpeed = 1;
  const size_t kNumSpeedIntervals = 20;
  const double kSpeedIntervalWidth = kMaxSpeed / kNumSpeedIntervals;

  void DrawHistogramBars(const glm::vec2& top_left_corner,
                         const std::vector<size_t>& frequencies,
                         size_t max_frequency, const cinder::Color& color) const;
  void DrawXAxis() const;
  void DrawYAxis() const;
};

}  // namespace idealgas