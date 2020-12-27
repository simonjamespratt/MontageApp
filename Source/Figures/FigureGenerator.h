#pragma once

#include "Figure.h"
#include "FigureParticleSelection.h"
#include "Identifiers.h"

#include <juce_gui_basics/juce_gui_basics.h>

class FigureGenerator : public juce::Component {
  public:
    FigureGenerator(juce::ValueTree &as);
    ~FigureGenerator();

    void paint(juce::Graphics &) override;
    void resized() override;

    Figure generateFigure();

  private:
    juce::ValueTree &appState;

    juce::Label globalSettingsHeading;
    juce::TextEditor numEventsInput;
    juce::Label numEventsLabel;

    FigureParticleSelection figureParticleSelection;

    juce::Label onsetSelectionHeading;

    // TODO: make the particles collection a member
    // TODO: make producer a member
    // TODO: set particle selection to basic protocol initially
    // TODO: inform the selector UI dropdown which protocol (basic) is initially
    // selected
    // TODO: allow UI dropdown and settings UI to update protocol params

    // TODO: If particles collection size changes, call producer and update any
    // UI that needs to know

    // TODO: when the particle collections size is < 2 (producer will throw
    // error)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureGenerator)
};
