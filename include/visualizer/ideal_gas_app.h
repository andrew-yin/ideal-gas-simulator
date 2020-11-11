#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "histograms.h"
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
  const double kWindowWidth = 1500;
  const double kWindowHeight = 1000;

  /** The margin between the edge of the Cinder application window and the
   *  box/histograms */
  const double kMargin = 100;

  /** The width of the box holding the particles in pixels */
  const double kBoxWidth = kWindowHeight - 2 * kMargin;

  Simulator simulator_;
  Box box_;
  Histograms histograms_;
};

}  // namespace idealgas