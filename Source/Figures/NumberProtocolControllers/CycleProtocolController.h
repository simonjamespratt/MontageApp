#pragma once

#include "ProtocolControllerBroadcaster.h"

#include <NumberProtocolParameters.hpp>
#include <juce_gui_basics/juce_gui_basics.h>

class CycleProtocolController : public juce::Component,
                                public ProtocolControllerBroadcaster {
  public:
    CycleProtocolController();
    ~CycleProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;
    void
    setInitialDefaults(aleatoric::NumberProtocolParameters::Protocols params);

  private:
    juce::ToggleButton bidirectional;
    juce::ToggleButton reverseDirection;

    void updateState(juce::Button &button);
};
