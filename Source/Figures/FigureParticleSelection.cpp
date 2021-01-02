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

    addProtocols();
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
    setProtocolBounds(controlsArea);
}

// Private methods
void FigureParticleSelection::protocolChanged()
{
    using namespace aleatoric;

    switch(protocolSelector.getSelectedId()) {
    case 1:
        producer->setProtocol(
            NumberProtocol::create(NumberProtocol::Type::adjacentSteps));
        break;
    case 2:
        producer->setProtocol(
            NumberProtocol::create(NumberProtocol::Type::basic));
        break;
    case 3:
        producer->setProtocol(
            NumberProtocol::create(NumberProtocol::Type::cycle));
        break;
    default:
        break;
    }

    auto newParams = producer->getParams();
    auto activeProtocol = newParams.getActiveProtocol();
    if(activeProtocol ==
       NumberProtocolParameters::Protocols::ActiveProtocol::adjacentSteps) {
        DBG("adjacentSteps is active");
    }
    if(activeProtocol ==
       NumberProtocolParameters::Protocols::ActiveProtocol::basic) {
        DBG("basic is active");
    }
    if(activeProtocol ==
       NumberProtocolParameters::Protocols::ActiveProtocol::cycle) {
        DBG("cycle is active");
    }

    setVisibility();
}

void FigureParticleSelection::addProtocols()
{
    addChildComponent(&adjacentStepsCtrl);
    addChildComponent(&basicCtrl);
    addChildComponent(&cycleCtrl);
}

void FigureParticleSelection::hideProtocols()
{
    adjacentStepsCtrl.setVisible(false);
    basicCtrl.setVisible(false);
    cycleCtrl.setVisible(false);
}

void FigureParticleSelection::setProtocolBounds(juce::Rectangle<int> area)
{
    adjacentStepsCtrl.setBounds(area);
    basicCtrl.setBounds(area);
    cycleCtrl.setBounds(area);
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

    setVisibility();
}

void FigureParticleSelection::setVisibility()
{
    hideProtocols();

    switch(protocolSelector.getSelectedId()) {
    case 1:
        adjacentStepsCtrl.setVisible(true);
        break;
    case 2:
        basicCtrl.setVisible(true);
        break;
    case 3:
        cycleCtrl.setVisible(true);
        break;
    default:
        break;
    }
}
