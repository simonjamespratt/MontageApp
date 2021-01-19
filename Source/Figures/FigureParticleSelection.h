#pragma once

#include "NumberProtocolController.h"
#include "Particle.h"

#include <CollectionsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>
#include <vector>

class FigureParticleSelection : public juce::Component {
  public:
    FigureParticleSelection(
        std::shared_ptr<aleatoric::CollectionsProducer<Particle>>
            particleProducer);

    ~FigureParticleSelection();

    void paint(juce::Graphics &g) override;
    void resized() override;

    void resetParams();

  private:
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> producer;
    std::unique_ptr<NumberProtocolController> controller;

    juce::Label heading;
    juce::Label protocolSelectorLabel;
    juce::ComboBox protocolSelector;

    void configureProtocolSelector();
    void protocolChanged();
    void setInitialActiveProtocol();
    void updateParams(aleatoric::NumberProtocolParameters::Protocols newParams);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureParticleSelection)
};
