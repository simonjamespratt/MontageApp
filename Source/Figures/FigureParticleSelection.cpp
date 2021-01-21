#include "FigureParticleSelection.h"

#include "ProtocolConfig.h"

FigureParticleSelection::FigureParticleSelection(
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> particleProducer)
: producer(particleProducer)
{
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
    auto selectedConfig = ProtocolConfig::findById(id);

    producer->setProtocol(
        NumberProtocol::create(selectedConfig.getProtocolType()));
    controller =
        NumberProtocolController::create(selectedConfig.getProtocolType(),
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
    auto config = ProtocolConfig::findByActiveProtocol(activeProtocol);
    protocolSelector.setSelectedId(config.getId(), juce::dontSendNotification);
}

void FigureParticleSelection::updateParams(
    aleatoric::NumberProtocolParameters::Protocols newParams)
{
    producer->setParams(newParams);
}

void FigureParticleSelection::configureProtocolSelector()
{
    for(auto &&config : ProtocolConfig::getConfigurations()) {
        protocolSelector.addItem(config.getName(), config.getId());
    }
}
