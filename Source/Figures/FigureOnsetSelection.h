#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class FigureOnsetSelection : public juce::Component {
  public:
    FigureOnsetSelection();
    ~FigureOnsetSelection();

    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    juce::Label onsetSelectionHeading;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureOnsetSelection)
};
