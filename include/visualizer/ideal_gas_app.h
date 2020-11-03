#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/box.h"

namespace idealgas {

/**
 * Allows a user to spawn gas particles in a container and visualize their
 * interaction in an ideal gas container.
 */
class IdealGasApp : public ci ::app ::App {
 public:
  /** Default constructor */
  IdealGasApp();

  /** Overriding Cinder methods */
  void setup() override;
  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;

 private:
  /** The width of the Cinder application window in pixels */
  const double kWindowWidth = 800;

  /** The margin between the edge of the Cinder application window and the box
      containing the gas particles */
  const double kMargin = 100;
  Box box_;
};

}  // namespace idealgas