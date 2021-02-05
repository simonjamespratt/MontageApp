#include "PrescribedProtocolController.h"

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    for(auto &&value : m_params.durations) {
        auto durationValue = std::make_unique<Value>();
        durationValue->label.setText(
            "Label",
            juce::dontSendNotification); // TODO: this should be a number
                                         // denoting order in list of values
        durationValue->input.setText(juce::String(value));
        addAndMakeVisible(&durationValue->label);
        durationValue->label.attachToComponent(&durationValue->input, true);
        addAndMakeVisible(&durationValue->input);
        durationValue->input.setInputRestrictions(0, "0123456789");
        durationValue->input.setJustification(juce::Justification::centredLeft);

        durationValues.emplace_back(std::move(durationValue));
    }
}

void PrescribedProtocolController::paint(juce::Graphics &g)
{}

void PrescribedProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    auto valueDisplayColWidth = area.getWidth() / 3;
    for(auto &&value : durationValues) {
        auto valueDisplayArea = area.removeFromTop(45);

        value->input.setBounds(
            valueDisplayArea.removeFromRight(valueDisplayColWidth)
                .reduced(margin));
    }
}

// Private methods
void PrescribedProtocolController::setProtocol()
{}
