#pragma once
#include "AdjacentStepsProtocolController.h"
#include "BasicProtocolController.h"

#include <juce_gui_basics/juce_gui_basics.h>

class FigureParticleSelection : public juce::Component {
  public:
    FigureParticleSelection();
    ~FigureParticleSelection();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    juce::Label heading;
    juce::Label protocolLabel;
    juce::ComboBox protocol;
    void protocolChanged();

    // Number protocol controllers
    BasicProtocolController basicCtrl;
    AdjacentStepsProtocolController adjacentStepsCtrl;
};
