#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace idealgas {

class IdealGasApp : public ci : app : App {
 public:
  IdealGasApp();

  void setup() override;
  void draw() override;
  void update() override;

 private:
  Box box_;
};

}  // namespace idealgas