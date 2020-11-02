#include "../include/ideal_gas_app.h"

using idealgas::IdealGasApp;

void prepareSettings(NaiveBayesApp::Settings* settings) {
  settings -> setResizeable(false);
}

CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings);