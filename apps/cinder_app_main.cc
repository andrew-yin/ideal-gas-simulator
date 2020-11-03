#include "visualizer/ideal_gas_app.h"

using idealgas::IdealGasApp;

void prepareSettings(IdealGasApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings);