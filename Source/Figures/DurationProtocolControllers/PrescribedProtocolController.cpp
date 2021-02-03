#include "PrescribedProtocolController.h"

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    for(auto &&value : m_params.durations) {
        durationValues.emplace_back(juce::Label(juce::String(value)));
    }

    for(auto &&value : durationValues) {
        addAndMakeVisible(&value);
    }
}

void PrescribedProtocolController::paint(juce::Graphics &g)
{}

void PrescribedProtocolController::resized()
{
    auto area = getLocalBounds();
    for(auto &&value : durationValues) {
        value.setBounds(area.removeFromTop(45));
    }
}

// Private methods
void PrescribedProtocolController::setProtocol()
{}
