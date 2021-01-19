#pragma once

#include <DurationsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>

class FigureOnsetSelection : public juce::Component {
  public:
    FigureOnsetSelection(aleatoric::DurationsProducer &producer);
    ~FigureOnsetSelection();

    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    juce::Label onsetSelectionHeading;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureOnsetSelection)
};
