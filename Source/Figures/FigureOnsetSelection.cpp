#include "FigureOnsetSelection.h"

#include "ProtocolConfig.h"

FigureOnsetSelection::FigureOnsetSelection(
    std::shared_ptr<aleatoric::DurationsProducer> durationsProducer)
: numberProtocolSelector(durationsProducer)
{
    heading.setText("Onset selection", juce::dontSendNotification);
    addAndMakeVisible(&heading);
    heading.setFont(juce::Font(20.0f, juce::Font::bold));

    addAndMakeVisible(&numberProtocolSelector);
}

FigureOnsetSelection::~FigureOnsetSelection()
{}

void FigureOnsetSelection::paint(juce::Graphics &g)
{}

void FigureOnsetSelection::resized()
{
    auto area = getLocalBounds();
    heading.setBounds(area.removeFromTop(50));
    numberProtocolSelector.setBounds(area);
}
