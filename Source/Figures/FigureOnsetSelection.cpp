#include "FigureOnsetSelection.h"

#include "ProtocolConfig.h"

FigureOnsetSelection::FigureOnsetSelection(
    aleatoric::DurationsProducer &durationsProducer)
: producer(durationsProducer)
{
    onsetSelectionHeading.setText("Onset selection",
                                  juce::dontSendNotification);
    addAndMakeVisible(&onsetSelectionHeading);
    onsetSelectionHeading.setFont(juce::Font(20.0f, juce::Font::bold));

    // identical to FigParticleSel except for name changes
    numberProtocolSelectorLabel.setText("Selection strategy: ",
                                        juce::dontSendNotification);
    addAndMakeVisible(&numberProtocolSelectorLabel);

    addAndMakeVisible(&numberProtocolSelector);
    configureNumberProtocolSelector();
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

    // this is not much different from FigParticleSel
    auto chooseNumberProtocolArea = area.removeFromTop(45);
    auto numberProtocolColWidth = chooseNumberProtocolArea.getWidth() / 2;
    numberProtocolSelectorLabel.setBounds(
        chooseNumberProtocolArea.removeFromLeft(numberProtocolColWidth)
            .reduced(margin));
    numberProtocolSelector.setBounds(chooseNumberProtocolArea.reduced(margin));

    auto numberProtocolControlsArea = area;
}

// Private methods
void FigureOnsetSelection::configureNumberProtocolSelector()
{
    // identical to FigParticleSel
    for(auto &&config : ProtocolConfig::getConfigurations()) {
        numberProtocolSelector.addItem(config.getName(), config.getId());
    }
}
