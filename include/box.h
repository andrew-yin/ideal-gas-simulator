#pragma once

namespace idealgas {

class Box {
 public:
  Box(const glm::vec2& top_left_corner, double box_length);
  void Draw() const;
};

}