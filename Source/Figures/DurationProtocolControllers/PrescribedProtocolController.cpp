#include "PrescribedProtocolController.h"

#include <iterator>

PrescribedProtocolController::Value::Value(int &value)
: paramsDurationValue(value) {};

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    // TODO: Tidy up naming. Is horrible atm
    // TODO: consider moving a lot of this into the constructor of Value
    auto &values = m_params.durations;
    for(auto it = begin(values); it != end(values); ++it) {
        auto durationValue = std::make_shared<Value>(*it);

        // Input
        durationValue->input.setText(juce::String(*it));
        durationValue->input.setInputRestrictions(0, "0123456789");
        durationValue->input.setJustification(juce::Justification::centredLeft);
        addAndMakeVisible(&durationValue->input);

        // NB: durationValue has to be captured as a weak pointer in lambda to
        // avoid memory leak caused by shared pointer reference counting and
        // cyclical references. See
        // https://stackoverflow.com/questions/18818260/passing-shared-ptr-to-lambda-by-value-leaks-memory/18818407
        // and also https://floating.io/2017/07/lambda-shared_ptr-memory-leak/
        durationValue->input.onTextChange =
            [durationValueWeak = std::weak_ptr<Value>(durationValue)] {
                auto durValue = durationValueWeak.lock();
                if(durValue) {
                    // keep params and ui in sync
                    durValue->paramsDurationValue =
                        durValue->input.getText().getIntValue();
                }
            };

        // Label
        auto index = std::distance(values.begin(), it);
        auto listPosition = index + 1;
        auto labelName = juce::String(listPosition) + ": ";
        durationValue->label.setText(labelName, juce::dontSendNotification);
        addAndMakeVisible(&durationValue->label);
        durationValue->label.attachToComponent(&durationValue->input, true);

        // Delete button
        durationValue->deleteButton.setButtonText("Delete");
        // remove corresponding value from m_params.durations
        // remove durationValue from vector durationValues
        // call resized()
        addAndMakeVisible(&durationValue->deleteButton);

        durationValues.emplace_back(durationValue);
    }

    saveButton.setButtonText("Set protocol");
    saveButton.onClick = [this] {
        setProtocol();
    };
    addAndMakeVisible(&saveButton);
}

void PrescribedProtocolController::paint(juce::Graphics &g)
{}

void PrescribedProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    area.removeFromLeft(50); // label gutter
    auto valueArea = area.removeFromLeft(200);
    for(auto &&value : durationValues) {
        auto itemArea = valueArea.removeFromTop(45);
        auto labelArea = itemArea.removeFromLeft(100);
        value->input.setBounds(labelArea.reduced(margin));
        value->deleteButton.setBounds(itemArea.reduced(margin));
    }
    saveButton.setBounds(area.removeFromRight(100));
}

// Private methods
void PrescribedProtocolController::setProtocol()
{
    for(auto &&value : durationValues) {
        DBG("in durationValues" << juce::String(value->paramsDurationValue));
    }

    for(auto &&value : m_params.durations) {
        DBG("in params.durations" << juce::String(value));
    }
}
