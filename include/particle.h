#pragma once

namespace idealgas {

class Particle {
 public:
  Particle();
  Particle(double mass, double radius, std::string color, glm::vec_2 position,
           glm::vec_2 velocity);

 private:
  double mass_;
  double radius_;
  std::string color_;
  glm::vec_2 position_;
  glm::vec_2 velocity_;
};

}  // namespace idealgas