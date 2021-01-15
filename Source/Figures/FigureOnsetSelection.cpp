#include "FigureOnsetSelection.h"

FigureOnsetSelection::FigureOnsetSelection()
{
    onsetSelectionHeading.setText("Onset selection",
                                  juce::dontSendNotification);
    addAndMakeVisible(&onsetSelectionHeading);
    onsetSelectionHeading.setFont(juce::Font(20.0f, juce::Font::bold));
}

FigureOnsetSelection::~FigureOnsetSelection()
{}

void FigureOnsetSelection::paint(juce::Graphics &g)
{}

void FigureOnsetSelection::resized()
{
    auto area = getLocalBounds();
    onsetSelectionHeading.setBounds(area.removeFromTop(50));
}
