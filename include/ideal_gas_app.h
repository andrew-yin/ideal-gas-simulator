#pragma once

#include "box.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace idealgas {

class IdealGasApp : public ci ::app ::App {
 public:
  IdealGasApp();

  void setup() override;
  void draw() override;
  void update() override;

  void keyDown(ci::app::KeyEvent event) override;

 private:
  const double kWindowWidth = 800;
  const double kMargin = 100;
  size_t num_particles_;
  Box box_;
};

}  // namespace idealgas