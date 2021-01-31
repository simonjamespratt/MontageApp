#include "PrescribedProtocolController.h"

PrescribedProtocolController::PrescribedProtocolController()
{
    text.setText("Prescribed Protocol Controller", juce::dontSendNotification);
    addAndMakeVisible(&text);
}

void PrescribedProtocolController::paint(juce::Graphics &g)
{}

void PrescribedProtocolController::resized()
{
    auto area = getLocalBounds();
    text.setBounds(area);
}

// Private methods
void PrescribedProtocolController::setProtocol()
{}
