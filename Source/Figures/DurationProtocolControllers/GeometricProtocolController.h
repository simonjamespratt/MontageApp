#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

class GeometricProtocolController : public DurationProtocolController {
  public:
    GeometricProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    juce::Label text;
};
