#pragma once

#include "cinder/gl/gl.h"
#include "simulator.h"

namespace idealgas {

class Box {
 public:
  Box(const glm::vec2& top_left_corner, double box_length);
  void Draw();
  void Update();

  void AddRandomParticle();

  void Reset();

 private:
  glm::vec2 top_left_corner_;
  double box_length_;
  Simulator simulator_;

  double scale_factor_;

  void DrawBox();
  void DrawParticles();
};

}  // namespace idealgas