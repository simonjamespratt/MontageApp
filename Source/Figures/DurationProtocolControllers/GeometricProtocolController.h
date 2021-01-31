#pragma once

#include "DurationProtocolController.h"

class GeometricProtocolController : public DurationProtocolController {
  public:
    GeometricProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    juce::Label text;
};
