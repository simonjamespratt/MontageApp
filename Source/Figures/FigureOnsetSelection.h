#pragma once

#include <DurationsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>

class FigureOnsetSelection : public juce::Component {
  public:
    FigureOnsetSelection(aleatoric::DurationsProducer &durationsProducer);
    ~FigureOnsetSelection();

    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    aleatoric::DurationsProducer &producer;

    juce::Label onsetSelectionHeading;
    juce::Label numberProtocolSelectorLabel;
    juce::ComboBox numberProtocolSelector;

    void configureNumberProtocolSelector();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureOnsetSelection)
};
