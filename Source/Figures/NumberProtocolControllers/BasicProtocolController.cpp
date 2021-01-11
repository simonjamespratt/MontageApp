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

void BasicProtocolController::setParams(
    aleatoric::NumberProtocolParameters::Protocols params)
{}

aleatoric::NumberProtocolParameters::Protocols
BasicProtocolController::getParams()
{
    return aleatoric::NumberProtocolParameters::Protocols(
        aleatoric::NumberProtocolParameters::Basic());
}
