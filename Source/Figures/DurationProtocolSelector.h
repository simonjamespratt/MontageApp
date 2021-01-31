#pragma once
#include "DurationProtocolController.h"

#include <DurationsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

class DurationProtocolSelector : public juce::Component {
  public:
    DurationProtocolSelector(
        std::shared_ptr<aleatoric::DurationsProducer> durationsProducer);

    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    std::shared_ptr<aleatoric::DurationsProducer> producer;

    std::unique_ptr<DurationProtocolController> controller;

    juce::Label protocolSelectorLabel;
    juce::ComboBox protocolSelector;

    void configureProtocolSelector();
    void protocolChanged();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DurationProtocolSelector)
};
