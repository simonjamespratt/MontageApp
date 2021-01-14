#include "FigureParticleSelection.h"

#include <algorithm>

ProtocolConfig::ProtocolConfig(int id,
                               juce::String name,
                               Type type,
                               Params::Protocols::ActiveProtocol activeType)
: selectorId(id),
  humanName(name),
  protocolType(type),
  activeProtocolType(activeType)
{}

FigureParticleSelection::FigureParticleSelection(
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> particleProducer)
: producer(particleProducer)
{
    initialiseProtocolConfigurations();

    heading.setText("Particle selection", juce::dontSendNotification);
    addAndMakeVisible(&heading);
    heading.setFont(juce::Font(20.0f, juce::Font::bold));

    protocolSelectorLabel.setText("Selection strategy: ",
                                  juce::dontSendNotification);
    addAndMakeVisible(&protocolSelectorLabel);

    addAndMakeVisible(&protocolSelector);
    configureProtocolSelector();
    protocolSelector.onChange = [this] {
        protocolChanged();
    };

    setInitialActiveProtocol();
}

FigureParticleSelection::~FigureParticleSelection()
{}

void FigureParticleSelection::paint(juce::Graphics &g)
{}

void FigureParticleSelection::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();

    heading.setBounds(area.removeFromTop(50));

    auto chooseProtocolArea = area.removeFromTop(45);
    auto protocolColWidth = chooseProtocolArea.getWidth() / 2;
    protocolSelectorLabel.setBounds(
        chooseProtocolArea.removeFromLeft(protocolColWidth).reduced(margin));
    protocolSelector.setBounds(chooseProtocolArea.reduced(margin));

    auto controlsArea = area;

    if(controller != nullptr) {
        controller->setBounds(controlsArea);
    }
}

void FigureParticleSelection::resetParams()
{
    if(controller != nullptr) {
        controller->setParams(producer->getParams());
    }
}

// Private methods
void FigureParticleSelection::protocolChanged()
{
    using namespace aleatoric;

    auto id = protocolSelector.getSelectedId();

    // TODO: This coul be a method on Protocol::findByProtocolType that returns
    // the config you need
    auto it = std::find_if(protocolConfigurations.begin(),
                           protocolConfigurations.end(),
                           [&id](const ProtocolConfig &config) {
                               return config.selectorId == id;
                           });
    jassert(it != protocolConfigurations.end());

    auto selectedConfig = *it;
    producer->setProtocol(NumberProtocol::create(selectedConfig.protocolType));
    controller = NumberProtocolController::create(selectedConfig.protocolType,
                                                  producer->getParams());

    controller->attach(
        [this](aleatoric::NumberProtocolParameters::Protocols newParams) {
            updateParams(newParams);
        });

    addAndMakeVisible(*controller);
    resized();
}

void FigureParticleSelection::setInitialActiveProtocol()
{
    auto activeProtocol = producer->getParams().getActiveProtocol();

    // TODO: This could be a method on ProtocolConfig::findByActiveProtocolType
    // that returns the config you need
    auto it =
        std::find_if(protocolConfigurations.begin(),
                     protocolConfigurations.end(),
                     [&activeProtocol](const ProtocolConfig &config) {
                         return config.activeProtocolType == activeProtocol;
                     });
    jassert(it != protocolConfigurations.end());

    protocolSelector.setSelectedId(it->selectorId, juce::dontSendNotification);
}

void FigureParticleSelection::updateParams(
    aleatoric::NumberProtocolParameters::Protocols newParams)
{
    producer->setParams(newParams);
}

void FigureParticleSelection::initialiseProtocolConfigurations()
{
    using Type = aleatoric::NumberProtocol::Type;
    using Params = aleatoric::NumberProtocolParameters;

    protocolConfigurations.emplace_back(
        ProtocolConfig(1,
                       "Adjacent Steps",
                       Type::adjacentSteps,
                       Params::Protocols::ActiveProtocol::adjacentSteps));

    protocolConfigurations.emplace_back(
        ProtocolConfig(2,
                       "Basic",
                       Type::basic,
                       Params::Protocols::ActiveProtocol::basic));

    protocolConfigurations.emplace_back(
        ProtocolConfig(3,
                       "Cycle",
                       Type::cycle,
                       Params::Protocols::ActiveProtocol::cycle));
}

void FigureParticleSelection::configureProtocolSelector()
{
    for(auto &&config : protocolConfigurations) {
        protocolSelector.addItem(config.humanName, config.selectorId);
    }
}
