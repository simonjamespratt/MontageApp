#include "AdjacentStepsProtocolController.h"

AdjacentStepsProtocolController::AdjacentStepsProtocolController()
{
    text.setText("No parameters to display", juce::dontSendNotification);
    addAndMakeVisible(&text);
}

AdjacentStepsProtocolController::~AdjacentStepsProtocolController()
{}

void AdjacentStepsProtocolController::paint(juce::Graphics &g)
{}

void AdjacentStepsProtocolController::resized()
{
    auto area = getLocalBounds();
    text.setBounds(area);
}

void AdjacentStepsProtocolController::setParams(
    aleatoric::NumberProtocolParameters::Protocols params)
{}

aleatoric::NumberProtocolParameters::Protocols
AdjacentStepsProtocolController::getParams()
{
    return aleatoric::NumberProtocolParameters::Protocols(
        aleatoric::NumberProtocolParameters::AdjacentSteps());
}
