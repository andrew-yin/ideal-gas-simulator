#include <ideal_gas_app.h>

#include <ctime>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : num_particles_(0),
      box_(glm::vec2(kMargin, kMargin), kWindowWidth - 2 * kMargin) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowWidth);
}

void IdealGasApp::setup() {
  srand(static_cast<unsigned>(time(0)));
}

void IdealGasApp::draw() {
  ci::gl::clear(ci::Color8u(255, 246, 148));
  box_.Draw();

  ci::gl::drawStringCentered(
      "Press Enter to add a random particle. Press Backspace to empty the box.",
      glm::vec2(kWindowWidth / 2, kMargin / 2), ci::Color("black"));

  ci::gl::drawStringCentered(
      "Number of Particles: " + std::to_string(num_particles_),
      glm::vec2(kWindowWidth / 2, kWindowWidth - kMargin / 2),
      ci::Color("blue"));
}

void IdealGasApp::update() {
  box_.Update();
}
void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      box_.AddRandomParticle();
      num_particles_++;
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      box_.Reset();
      num_particles_ = 0;
      break;
    default:
      break;
  }
}

}  // namespace idealgas