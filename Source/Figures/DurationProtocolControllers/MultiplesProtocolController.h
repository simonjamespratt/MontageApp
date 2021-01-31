#pragma once

#include "DurationProtocolController.h"

class MultiplesProtocolController : public DurationProtocolController {
  public:
    MultiplesProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    juce::Label text;
};
