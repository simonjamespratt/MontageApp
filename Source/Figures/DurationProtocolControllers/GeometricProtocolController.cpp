#include "GeometricProtocolController.h"

GeometricProtocolController::GeometricProtocolController()
{
    text.setText("Geometric Protocol Controller", juce::dontSendNotification);
    addAndMakeVisible(&text);
}

void GeometricProtocolController::paint(juce::Graphics &g)
{}

void GeometricProtocolController::resized()
{
    auto area = getLocalBounds();
    text.setBounds(area);
}

// Private methods
void GeometricProtocolController::setProtocol()
{}
