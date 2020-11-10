#include <visualizer/ideal_gas_app.h>

#include <ctime>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : box_(glm::vec2(kMargin, kMargin), kBoxWidth),
      small_histogram_(glm::vec2(kWindowHeight, kMargin), kBoxWidth / 2,
                       kBoxWidth / 4),
      medium_histogram_(glm::vec2(kWindowHeight, 2 * kMargin + kBoxWidth / 4),
                        kBoxWidth / 2, kBoxWidth / 4),
      large_histogram_(
          glm::vec2(kWindowHeight, 3 * kMargin + 2 * kBoxWidth / 4),
          kBoxWidth / 2, kBoxWidth / 4) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void IdealGasApp::draw() {
  /* Set background to light yellow */
  ci::gl::clear(ci::Color8u(255, 246, 148));

  /* Draw text instructions */
  ci::gl::drawStringCentered(
      "Press 1, 2, or 3 to add a random small, medium, or large particle, "
      "respectively. Press Backspace to empty the box.",
      glm::vec2(kWindowHeight / 2, kMargin / 2), ci::Color("black"));

  ci::gl::drawStringCentered(
      "Number of Particles: " + std::to_string(box_.GetNumParticles()),
      glm::vec2(kWindowHeight / 2, kWindowHeight - kMargin / 2),
      ci::Color("blue"));

  box_.Draw();
  small_histogram_.Draw();
  medium_histogram_.Draw();
  large_histogram_.Draw();
}

void IdealGasApp::update() {
  box_.Update();
  small_histogram_.Update();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  box_.HandleKeyEvent(event);
}

}  // namespace idealgas