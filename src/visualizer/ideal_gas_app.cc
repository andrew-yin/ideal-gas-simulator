#include <visualizer/ideal_gas_app.h>

#include <ctime>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : box_(glm::vec2(kMargin, kMargin), kWindowWidth - 2 * kMargin) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowWidth);
}

void IdealGasApp::draw() {
  /* Set background to light yellow */
  ci::gl::clear(ci::Color8u(255, 246, 148));

  /* Draw text instructions */
  ci::gl::drawStringCentered(
      "Press 1, 2, or 3 to add a random small, medium, or large particle, "
      "respectively. Press Backspace to empty the box.",
      glm::vec2(kWindowWidth / 2, kMargin / 2), ci::Color("black"));

  ci::gl::drawStringCentered(
      "Number of Particles: " + std::to_string(box_.GetNumParticles()),
      glm::vec2(kWindowWidth / 2, kWindowWidth - kMargin / 2),
      ci::Color("blue"));

  /* Draw the box and particles */
  box_.Draw();
}

void IdealGasApp::update() {
  box_.Update();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  box_.HandleKeyEvent(event);
}

}  // namespace idealgas