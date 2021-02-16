#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

class MultiplesProtocolController : public DurationProtocolController {
  public:
    MultiplesProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    juce::Label text;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultiplesProtocolController)
};
