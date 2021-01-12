#pragma once
#include "NumberProtocolController.h"

class CycleProtocolController : public NumberProtocolController {
  public:
    CycleProtocolController(
        aleatoric::NumberProtocolParameters::Protocols initialParams);

    ~CycleProtocolController();

    void paint(juce::Graphics &g) override;

    void resized() override;

    void
    setParams(aleatoric::NumberProtocolParameters::Protocols params) override;

    aleatoric::NumberProtocolParameters::Protocols getParams() override;

  private:
    bool isBidirectional = false;
    bool isReverseDirection = false;
    juce::ToggleButton bidirectionalToggle;
    juce::ToggleButton reverseDirectionToggle;

    void updateState(juce::Button &button);
};
