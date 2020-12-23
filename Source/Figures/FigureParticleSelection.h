#pragma once
#include "AdjacentStepsProtocolController.h"
#include "BasicProtocolController.h"
#include "CycleProtocolController.h"

#include <juce_gui_basics/juce_gui_basics.h>

class FigureParticleSelection : public juce::Component {
  public:
    FigureParticleSelection();
    ~FigureParticleSelection();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    juce::Label heading;
    juce::Label protocolSelectorLabel;
    juce::ComboBox protocolSelector;

    // Number protocol controllers
    BasicProtocolController basicCtrl;
    AdjacentStepsProtocolController adjacentStepsCtrl;
    CycleProtocolController cycleCtrl;

    void protocolChanged();
    void addProtocols();
    void hideProtocols();
    void setProtocolBounds(juce::Rectangle<int> area);
};
