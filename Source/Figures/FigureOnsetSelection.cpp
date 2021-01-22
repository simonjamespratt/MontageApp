#include "FigureOnsetSelection.h"

#include "ProtocolConfig.h"

FigureOnsetSelection::FigureOnsetSelection(
    std::shared_ptr<aleatoric::DurationsProducer> durationsProducer)
: producer(durationsProducer)
{
    onsetSelectionHeading.setText("Onset selection",
                                  juce::dontSendNotification);
    addAndMakeVisible(&onsetSelectionHeading);
    onsetSelectionHeading.setFont(juce::Font(20.0f, juce::Font::bold));

    // below is identical to FigParticleSel except for name changes
    numberProtocolSelectorLabel.setText("Selection strategy: ",
                                        juce::dontSendNotification);
    addAndMakeVisible(&numberProtocolSelectorLabel);

    addAndMakeVisible(&numberProtocolSelector);
    configureNumberProtocolSelector();
    numberProtocolSelector.onChange = [this] {
        numberProtocolChanged();
    };

    setInitialActiveNumberProtocol();
}

FigureOnsetSelection::~FigureOnsetSelection()
{}

void FigureOnsetSelection::paint(juce::Graphics &g)
{}

void FigureOnsetSelection::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();

    onsetSelectionHeading.setBounds(area.removeFromTop(50));

    // this is almost identical to FigParticleSel
    auto chooseNumberProtocolArea = area.removeFromTop(45);
    auto numberProtocolColWidth = chooseNumberProtocolArea.getWidth() / 2;
    numberProtocolSelectorLabel.setBounds(
        chooseNumberProtocolArea.removeFromLeft(numberProtocolColWidth)
            .reduced(margin));
    numberProtocolSelector.setBounds(chooseNumberProtocolArea.reduced(margin));

    auto numberProtocolControlsArea = area;

    if(numberProtocolController != nullptr) {
        numberProtocolController->setBounds(numberProtocolControlsArea);
    }
}

// Private methods
void FigureOnsetSelection::configureNumberProtocolSelector()
{
    // identical to FigParticleSel
    for(auto &&config : ProtocolConfig::getConfigurations()) {
        numberProtocolSelector.addItem(config.getName(), config.getId());
    }
}

void FigureOnsetSelection::numberProtocolChanged()
{
    // logic is identical to FigParticleSel. Differs only in how producer is
    // called because they differ ever so slightly
    using namespace aleatoric;

    auto id = numberProtocolSelector.getSelectedId();
    auto selectedConfig = ProtocolConfig::findById(id);

    producer->setNumberProtocol(
        NumberProtocol::create(selectedConfig.getProtocolType()));

    numberProtocolController =
        NumberProtocolController::create(selectedConfig.getProtocolType(),
                                         producer->getParams());

    numberProtocolController->attach(
        [this](aleatoric::NumberProtocolParameters::Protocols newParams) {
            updateNumberProtocolParams(newParams);
        });

    addAndMakeVisible(*numberProtocolController);
    resized();
}

void FigureOnsetSelection::updateNumberProtocolParams(
    aleatoric::NumberProtocolParameters::Protocols newParams)
{
    // identical to FigParticleSel
    producer->setParams(newParams);
}

void FigureOnsetSelection::setInitialActiveNumberProtocol()
{
    // identical to FigParticleSel
    auto activeProtocol = producer->getParams().getActiveProtocol();
    auto config = ProtocolConfig::findByActiveProtocol(activeProtocol);
    numberProtocolSelector.setSelectedId(config.getId(),
                                         juce::dontSendNotification);
}
