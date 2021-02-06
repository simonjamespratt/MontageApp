#include "PrescribedProtocolController.h"

#include <iterator>

PrescribedProtocolController::Value::Value(int &value)
: paramsDurationValue(value) {};

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    auto &values = m_params.durations;
    for(auto it = begin(values); it != end(values); ++it) {
        auto durationValue = std::make_shared<Value>(*it);

        // Input
        durationValue->input.setText(juce::String(*it));
        durationValue->input.setInputRestrictions(0, "0123456789");
        durationValue->input.setJustification(juce::Justification::centredLeft);
        addAndMakeVisible(&durationValue->input);
        // durationValue->input.onTextChange = [durationValue] {
        //     durationValue->paramsDurationValue =
        //         durationValue->input.getText().getIntValue();
        // };

        // Label
        auto index = std::distance(values.begin(), it);
        auto listPosition = index + 1;
        auto labelName = juce::String(listPosition) + ": ";
        durationValue->label.setText(labelName, juce::dontSendNotification);
        addAndMakeVisible(&durationValue->label);
        durationValue->label.attachToComponent(&durationValue->input, true);

        durationValues.emplace_back(durationValue);
    }
}

void PrescribedProtocolController::paint(juce::Graphics &g)
{}

void PrescribedProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    area.removeFromLeft(50); // label gutter
    auto valueArea = area.removeFromLeft(100);
    for(auto &&value : durationValues) {
        value->input.setBounds(valueArea.removeFromTop(45).reduced(margin));
    }
}

// Private methods
void PrescribedProtocolController::setProtocol()
{}
