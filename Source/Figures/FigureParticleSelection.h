#pragma once
#include "AdjacentStepsProtocolController.h"
#include "BasicProtocolController.h"
#include "CycleProtocolController.h"
#include "NumberProtocolController.h"
#include "Particle.h"

#include <CollectionsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

class FigureParticleSelection : public juce::Component {
  public:
    FigureParticleSelection(
        std::shared_ptr<aleatoric::CollectionsProducer<Particle>>
            particleProducer);

    ~FigureParticleSelection();

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> producer;
    juce::Label heading;
    juce::Label protocolSelectorLabel;
    juce::ComboBox protocolSelector;

    std::unique_ptr<NumberProtocolController> controller;

    void protocolChanged();
    void addProtocols();
    void hideProtocols();
    void setProtocolBounds(juce::Rectangle<int> area);
    void setInitialActiveProtocol();
    void setVisibility();
    void updateParams(aleatoric::NumberProtocolParameters::Protocols newParams);
};
