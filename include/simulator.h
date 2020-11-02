#pragma once

namespace idealgas {

class Simulator {
 public:
  Simulator();

 private:
  std::vector<Particle> particles_;
};

}