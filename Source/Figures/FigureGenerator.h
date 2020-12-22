#pragma once

#include "Figure.h"
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

    juce::Label particleSelectionHeading;
    juce::Label particleSelectionProtocolLabel;
    juce::ComboBox particleSelectionProtocol;

    juce::Label onsetSelectionHeading;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureGenerator)
};
