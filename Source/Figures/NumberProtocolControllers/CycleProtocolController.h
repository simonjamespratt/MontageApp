#pragma once
#include "NumberProtocolController.h"

class CycleProtocolController : public NumberProtocolController {
  public:
    CycleProtocolController();
    ~CycleProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;
    void
    setInitialDefaults(aleatoric::NumberProtocolParameters::Protocols params);
    aleatoric::NumberProtocolParameters::Protocols getParams() override;

  private:
    bool isBidirectional = false;
    bool isReverseDirection = false;
    juce::ToggleButton bidirectionalToggle;
    juce::ToggleButton reverseDirectionToggle;

    void updateState(juce::Button &button);
};
