#pragma once

#include "DurationProtocolController.h"

class PrescribedProtocolController : public DurationProtocolController {
  public:
    PrescribedProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    juce::Label text;
};
