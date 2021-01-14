#pragma once

#include "NumberProtocolController.h"
#include "Particle.h"
#include "ProtocolConfig.h"

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
    juce::Label heading;
    juce::Label protocolSelectorLabel;
    juce::ComboBox protocolSelector;

    std::unique_ptr<NumberProtocolController> controller;

    // TODO: this probably needs to go somethere accessible from other classes,
    // e.g. Onset/duration selector when it's created. Maybe ProtocolConfig
    // should be extracted from here and should have a static method that
    // returns a vector containing all protocol configs?
    std::vector<ProtocolConfig> protocolConfigurations;
    void initialiseProtocolConfigurations();

    void configureProtocolSelector();

    void protocolChanged();
    void setInitialActiveProtocol();
    void updateParams(aleatoric::NumberProtocolParameters::Protocols newParams);
};
