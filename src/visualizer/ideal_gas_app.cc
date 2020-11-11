#include <visualizer/ideal_gas_app.h>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : box_(simulator_, glm::vec2(kMargin, kMargin), kBoxWidth),
      histograms_(simulator_,
                  std::vector<glm::vec2>(
                      {glm::vec2(kWindowHeight, kMargin),
                      glm::vec2(kWindowHeight, 2 * kMargin + kBoxWidth / 4),
                      glm::vec2(kWindowHeight, 3 * kMargin + 2 * kBoxWidth / 4)}),
                  kBoxWidth / 2, kBoxWidth / 4) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void IdealGasApp::setup() {
  histograms_.Setup();
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
      "Number of Particles: " + std::to_string(simulator_.GetNumParticles()),
      glm::vec2(kWindowHeight / 2, kWindowHeight - kMargin / 2),
      ci::Color("blue"));

  box_.Draw();
  histograms_.Draw();
}

void IdealGasApp::update() {
  simulator_.Update();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_1:
      simulator_.AddRandomSmallParticle();
      break;
    case ci::app::KeyEvent::KEY_2:
      simulator_.AddRandomMediumParticle();
      break;
    case ci::app::KeyEvent::KEY_3:
      simulator_.AddRandomLargeParticle();
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      simulator_.Reset();
      break;
  }
}

}  // namespace idealgas