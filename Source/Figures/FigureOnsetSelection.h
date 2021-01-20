#pragma once

#include "NumberProtocolController.h"

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
    std::unique_ptr<NumberProtocolController> numberProtocolController;

    juce::Label onsetSelectionHeading;
    juce::Label numberProtocolSelectorLabel;
    juce::ComboBox numberProtocolSelector;

    void configureNumberProtocolSelector();
    void numberProtocolChanged();
    void updateNumberProtocolParams(
        aleatoric::NumberProtocolParameters::Protocols newParams);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureOnsetSelection)
};
