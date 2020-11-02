#include <ideal_gas_app.h>

namespace idealgas {

IdealGasApp::IdealGasApp() : box_(glm::vec2(kMargin, kMargin), kWindowWidth - 2 * kMargin){
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowWidth);
}

void IdealGasApp::setup() {

}

void IdealGasApp::draw() {
  ci::gl::clear(ci::Color::gray(0.3f));

  box_.Draw();
}

void IdealGasApp::update() {

}

}  // namespace idealgas
