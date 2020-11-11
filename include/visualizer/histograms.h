#pragma once

#include <core/simulator.h>

#include "cinder/gl/gl.h"

namespace idealgas {

/**
 * A series of three histograms to be drawn in the Cinder application that
 * visualize the distribution of particle speeds for small, medium, and large
 * sizes.
 */
class Histograms {
 public:
  /**
   * Creates a series of three histograms.
   * @param simulator          A simulator to be used for data retrieval
   * @param top_left_corners   A vector of the top left corners of the three
   * histograms
   * @param graph_width        The width of an individual histogram in pixels
   * @param graph_height       The height of an individual histogram in pixels
   */
  Histograms(const Simulator& simulator,
             const std::vector<glm::vec2>& top_left_corners,
             const double graph_width, const double graph_height);

  /** Cinder-related methods */
  void Setup();
  void Draw() const;

 private:
  const size_t kMaxFrequency = 15;
  const size_t kNumFreqIntervals = 5;
  const size_t kFreqIntervalWidth = kMaxFrequency / kNumFreqIntervals;

  const double kMaxSpeed = 1;
  const size_t kNumSpeedIntervals = 20;
  const double kSpeedIntervalWidth = kMaxSpeed / kNumSpeedIntervals;

  std::vector<glm::vec2> top_left_corners_;
  double graph_width_;
  double graph_height_;
  const Simulator& simulator_;

  /**
   * Vectors containing the interval boundaries for speed (x-axis) and
   * frequency (y-axis)
   */
  std::vector<double> speed_intervals_;
  std::vector<size_t> freq_intervals_;

  /** Helper methods used during the drawing of the histogram */
  void DrawBorders() const;
  void DrawGraphs() const;

  /**
   * Sorts the specified speeds into ranges and returns their frequency.
   *
   * @param speeds The specified speeds to be sorted
   * @return A vector representing the frequency in which the speeds occur in a
   *         given range. The i-th indexed value refers to the frequency of
   *         speeds between speed_intervals[i] and speed_intervals[i+1].
   */
  std::vector<size_t> GetSpeedFrequencies(
      const std::vector<double>& speeds) const;

  /**
   * Draws a set of histogram bars based on the specified parameters
   *
   * @param top_left_corner The top left corner of the histogram chart in which
   *                        the bars will be drawn
   * @param frequencies     The frequencies of each range in the histogram
   * @param color           The color of each bar in the histogram
   */
  void DrawHistogramBars(const glm::vec2& top_left_corner,
                         const std::vector<size_t>& frequencies,
                         const cinder::Color& color) const;

  /** Helper methods to draw the axes and proper labels for the histogram */
  void DrawXAxis() const;
  void DrawYAxis() const;
  void DrawXLabel(const glm::vec2& top_left_corner) const;
  void DrawYLabel(const glm::vec2& top_left_corner) const;
};

}  // namespace idealgas