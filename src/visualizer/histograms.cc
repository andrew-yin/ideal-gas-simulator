#include "visualizer/histograms.h"

namespace idealgas {

void Histograms::Setup() {
  intervals_.push_back(0);
  for (size_t i = 1; i <= kNumIntervals; i++) {
    intervals_.push_back(intervals_.back() + kIntervalWidth);
  }
}

Histograms::Histograms(Simulator& simulator,
                       const std::vector<glm::vec2>& top_left_corners,
                       const double graph_width, const double graph_height)
    : top_left_corners_(top_left_corners),
      graph_width_(graph_width),
      graph_height_(graph_height),
      simulator_(simulator) {
}

void Histograms::Draw() const {
  DrawBorders();
  DrawGraphs();
}

void Histograms::DrawBorders() const {
  for (const glm::vec2& top_left_corner : top_left_corners_) {
    glm::vec2 pixel_bottom_right =
        top_left_corner + glm::vec2(graph_width_, graph_height_);

    ci::Rectf pixel_bounding_box(top_left_corner, pixel_bottom_right);
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRect(pixel_bounding_box);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRect(pixel_bounding_box, 1.0);
  }
}

void Histograms::DrawGraphs() const {
  std::vector<double> small_speeds = simulator_.GetSmallParticleSpeeds();
  std::vector<double> medium_speeds = simulator_.GetMediumParticleSpeeds();
  std::vector<double> large_speeds = simulator_.GetLargeParticleSpeeds();

  std::vector<size_t> small_freqs = GetFrequencies(small_speeds);
  size_t max_small_freq =
      *std::max_element(small_freqs.begin(), small_freqs.end());

  std::vector<size_t> med_freqs = GetFrequencies(medium_speeds);
  size_t max_med_freq = *std::max_element(med_freqs.begin(), med_freqs.end());

  std::vector<size_t> large_freqs = GetFrequencies(large_speeds);
  size_t max_large_freq =
      *std::max_element(large_freqs.begin(), large_freqs.end());

  DrawHistogramBars(top_left_corners_[0], small_freqs, max_small_freq,
                    simulator_.kSmallColor);
  DrawHistogramBars(top_left_corners_[1], med_freqs, max_med_freq,
                    simulator_.kMediumColor);
  DrawHistogramBars(top_left_corners_[2], large_freqs, max_large_freq,
                    simulator_.kLargeColor);
}

std::vector<size_t> Histograms::GetFrequencies(
    const std::vector<double>& speeds) const {
  std::vector<size_t> frequencies;
  for (size_t i = 0; i < kNumIntervals; i++) {
    double interval_min = intervals_[i];
    double interval_max = intervals_[i + 1];

    size_t count = 0;
    for (double speed : speeds) {
      if (speed >= interval_min && speed < interval_max) {
        count++;
      }
    }
    frequencies.push_back(count);
  }
  return frequencies;
}

void Histograms::DrawHistogramBars(const glm::vec2& top_left_corner,
                                   const std::vector<size_t>& frequencies,
                                   size_t max_frequency,
                                   const ci::Color& color) const {
  double max_frequency_height = graph_height_ * 3 / 4;
  double bar_width = graph_width_ / kNumIntervals;

  glm::vec2 bar_bot_left_corner = top_left_corner + glm::vec2(0, graph_height_);
  for (size_t frequency : frequencies) {
    double bar_height =
        (double)frequency / max_frequency * max_frequency_height;

    glm::vec2 bar_top_left_corner =
        bar_bot_left_corner + glm::vec2(0, -bar_height);
    glm::vec2 bar_bot_right_corner =
        bar_top_left_corner + glm::vec2(bar_width, bar_height);
    ci::Rectf bar(bar_top_left_corner, bar_bot_right_corner);
    ci::gl::color(color);
    ci::gl::drawSolidRect(bar);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawStrokedRect(bar, 1.0);

    bar_bot_left_corner += glm::vec2(bar_width, 0);
  }
}

}  // namespace idealgas