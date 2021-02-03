#include "MultiplesProtocolController.h"

MultiplesProtocolController::MultiplesProtocolController(
    DurationProtocolParams &params)
{
    text.setText("Multiples Protocol Controller", juce::dontSendNotification);
    addAndMakeVisible(&text);
}

void MultiplesProtocolController::paint(juce::Graphics &g)
{}

void MultiplesProtocolController::resized()
{
    auto area = getLocalBounds();
    text.setBounds(area);
}

// Private methods
void MultiplesProtocolController::setProtocol()
{}
