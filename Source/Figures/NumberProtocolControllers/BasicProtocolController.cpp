#include "BasicProtocolController.h"

BasicProtocolController::BasicProtocolController()
{
    text.setText("No parameters to display", juce::dontSendNotification);
    addAndMakeVisible(&text);
}

BasicProtocolController::~BasicProtocolController()
{}

void BasicProtocolController::paint(juce::Graphics &g)
{}

void BasicProtocolController::resized()
{
    auto area = getLocalBounds();
    text.setBounds(area);
}
