#include "FigureParticleSelection.h"

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
    protocolSelector.addItem("AdjacentSteps", 1);
    protocolSelector.addItem("Basic", 2);
    protocolSelector.addItem("Cycle", 3);
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

// Private methods
void FigureParticleSelection::protocolChanged()
{
    using namespace aleatoric;

    switch(protocolSelector.getSelectedId()) {
    case 1:
        producer->setProtocol(
            NumberProtocol::create(NumberProtocol::Type::adjacentSteps));
        controller = std::make_unique<AdjacentStepsProtocolController>();
        break;
    case 2:
        producer->setProtocol(
            NumberProtocol::create(NumberProtocol::Type::basic));
        controller = std::make_unique<BasicProtocolController>();
        break;
    case 3:
        producer->setProtocol(
            NumberProtocol::create(NumberProtocol::Type::cycle));
        controller = std::make_unique<CycleProtocolController>();
        break;
    default:
        break;
    }

    controller->setParams(producer->getParams());

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
    using namespace aleatoric;
    const auto basic =
        NumberProtocolParameters::Protocols::ActiveProtocol::basic;
    const auto adjacentSteps =
        NumberProtocolParameters::Protocols::ActiveProtocol::adjacentSteps;
    const auto cycle =
        NumberProtocolParameters::Protocols::ActiveProtocol::cycle;

    switch(activeProtocol) {
    case adjacentSteps:
        protocolSelector.setSelectedId(1, juce::dontSendNotification);
        break;
    case basic:
        protocolSelector.setSelectedId(2, juce::dontSendNotification);
        break;
    case cycle:
        protocolSelector.setSelectedId(3, juce::dontSendNotification);
        break;
    default:
        break;
    }
}

void FigureParticleSelection::updateParams(
    aleatoric::NumberProtocolParameters::Protocols newParams)
{
    producer->setParams(newParams);
}
