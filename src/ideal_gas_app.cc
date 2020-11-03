#include <ideal_gas_app.h>
#include <ctime>

namespace idealgas {

IdealGasApp::IdealGasApp()
    : box_(glm::vec2(kMargin, kMargin), kWindowWidth - 2 * kMargin) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowWidth);
}

void IdealGasApp::setup() {
  srand (static_cast <unsigned> (time(0)));
}

void IdealGasApp::draw() {
  ci::gl::clear(ci::Color::gray(0.3f));
  box_.Draw();
}

void IdealGasApp::update() {
  box_.Update();
}
void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      box_.AddRandomParticle();
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      box_.Reset();
      break;
    default:
      break;
  }
}

}  // namespace idealgas