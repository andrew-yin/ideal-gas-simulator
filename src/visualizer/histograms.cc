#include "visualizer/histograms.h"

namespace idealgas {

void Histograms::Setup() {
  speed_intervals_.push_back(0);
  freq_intervals_.push_back(0);
  for (size_t i = 1; i <= kNumSpeedIntervals; i++) {
    speed_intervals_.push_back(speed_intervals_.back() + kSpeedIntervalWidth);
  }
  for (size_t i = 1; i <= kNumFreqIntervals; i++) {
    freq_intervals_.push_back(freq_intervals_.back() + kFreqIntervalWidth);
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

  std::vector<size_t> small_freqs = GetSpeedFrequencies(small_speeds);
  std::vector<size_t> med_freqs = GetSpeedFrequencies(medium_speeds);
  std::vector<size_t> large_freqs = GetSpeedFrequencies(large_speeds);

  DrawHistogramBars(top_left_corners_[0], small_freqs, simulator_.kSmallColor);
  DrawHistogramBars(top_left_corners_[1], med_freqs, simulator_.kMediumColor);
  DrawHistogramBars(top_left_corners_[2], large_freqs, simulator_.kLargeColor);

  DrawXAxis();
  DrawYAxis();
}

std::vector<size_t> Histograms::GetSpeedFrequencies(
    const std::vector<double>& speeds) const {
  std::vector<size_t> frequencies;
  for (size_t i = 0; i < kNumSpeedIntervals - 1; i++) {
    double interval_min = speed_intervals_[i];
    double interval_max = speed_intervals_[i + 1];

    size_t count = 0;
    for (double speed : speeds) {
      if (speed >= interval_min && speed < interval_max) {
        count++;
      }
    }
    frequencies.push_back(count);
  }

  /* The last histogram interval is unbounded, deal with it seperately */
  double interval_min = speed_intervals_[speed_intervals_.size() - 2];
  size_t count = 0;
  for (double speed : speeds) {
    if (speed >= interval_min) {
      count++;
    }
  }

  frequencies.push_back(count);
  return frequencies;
}

void Histograms::DrawHistogramBars(const glm::vec2& top_left_corner,
                                   const std::vector<size_t>& frequencies,
                                   const ci::Color& color) const {
  double bar_width = graph_width_ / kNumSpeedIntervals;

  glm::vec2 bar_bot_left_corner = top_left_corner + glm::vec2(0, graph_height_);
  for (size_t frequency : frequencies) {
    double bar_height = frequency <= kMaxFrequency
                            ? (double)frequency / kMaxFrequency * graph_height_
                            : graph_height_;

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
void Histograms::DrawXAxis() const {
  double spacer = 10;
  for (const glm::vec2& top_left_corner : top_left_corners_) {
    DrawXLabel(top_left_corner);
    glm::vec2 bot_left_corner =
        top_left_corner + glm::vec2(0, graph_height_ + spacer);

    for (size_t i = 0; i < kNumSpeedIntervals; i++) {
      std::stringstream ss;
      ss << std::fixed << std::setprecision(1) << speed_intervals_[i] * 10;
      std::string speed = ss.str();
      ci::gl::drawStringCentered(speed, bot_left_corner, ci::Color("black"),
                                 cinder::Font("Arial", 8));
      bot_left_corner += glm::vec2(graph_width_ / kNumSpeedIntervals, 0);
    }

    /* Add '+' to end of label, deal with it separately */
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << speed_intervals_.back() * 10;
    std::string speed = ss.str();
    ci::gl::drawStringCentered(speed + "+", bot_left_corner, ci::Color("black"),
                               cinder::Font("Arial", 8));
  }
}

void Histograms::DrawYAxis() const {
  double spacer = 10;
  for (const glm::vec2& top_left_corner : top_left_corners_) {
    DrawYLabel(top_left_corner);
    glm::vec2 bot_left_corner =
        top_left_corner + glm::vec2(-spacer, graph_height_);

    for (size_t i = 0; i < kNumFreqIntervals; i++) {
      ci::gl::drawStringCentered(std::to_string(freq_intervals_[i]),
                                 bot_left_corner, ci::Color("black"),
                                 cinder::Font("Arial", 8));
      bot_left_corner += glm::vec2(0, -graph_height_ / kNumFreqIntervals);
    }

    /* Add '+' to end of label, deal with it separately */
    ci::gl::drawStringCentered(std::to_string(freq_intervals_.back()) + "+",
                               bot_left_corner, ci::Color("black"),
                               cinder::Font("Arial", 8));
  }
}
void Histograms::DrawXLabel(const glm::vec2& top_left_corner) const {
  double spacer = 40;
  glm::vec2 bot_left_corner =
      top_left_corner + glm::vec2(0, graph_height_ + spacer);
  glm::vec2 bot_right_corner = bot_left_corner + glm::vec2(graph_width_, 0);

  glm::vec2 label_location((bot_left_corner.x + bot_right_corner.x) * 0.5,
                           bot_left_corner.y);
  ci::gl::drawStringCentered("Speed", label_location, ci::Color("black"));
}
void Histograms::DrawYLabel(const glm::vec2& top_left_corner) const {
  double spacer = 10;
  glm::vec2 top_right_corner = top_left_corner + glm::vec2(graph_width_, 0);
  glm::vec2 bot_right_corner = top_right_corner + glm::vec2(0, graph_height_);

  glm::vec2 label_location(top_right_corner.x + spacer,
                           (top_right_corner.y + bot_right_corner.y) * 0.5);
  ci::gl::drawString("Freq.", label_location, ci::Color("black"));
}

}  // namespace idealgas