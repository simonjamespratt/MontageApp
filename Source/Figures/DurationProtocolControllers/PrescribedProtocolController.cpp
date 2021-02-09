#include "PrescribedProtocolController.h"

#include <iterator>

PrescribedProtocolController::DurationView::DurationView(int &value, int index)
: paramsDurationValue(value)
{
    input.setText(juce::String(value));
    input.setInputRestrictions(0, "0123456789");
    input.setJustification(juce::Justification::centredLeft);
    input.onTextChange = [this] {
        // keep params and ui in sync
        paramsDurationValue = input.getText().getIntValue();
    };

    auto listPosition = index + 1;
    auto labelName = juce::String(listPosition) + ": ";
    label.setText(labelName, juce::dontSendNotification);
    label.attachToComponent(&input, true);

    deleteButton.setButtonText("Delete");
    // remove corresponding value from m_params.durations
    // remove durationView from vector durationViews
    // call resized()
};

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    for(auto &&value : m_params.durations) {
        juce::ValueTree duration(duration_id);
        duration.setProperty(duration_value_id, value, nullptr);
        durationsModel.addChild(duration, -1, nullptr);
    }

    auto numChildren = durationsModel.getNumChildren();

    for(int i = 0; i < numChildren; i++) {
        auto duration = durationsModel.getChild(i);
        int value = duration.getProperty(duration_value_id);
        DBG("value: " << value);
        auto index = durationsModel.indexOf(duration);
        DBG("value index: " << index);

        // TODO: remove value passed here
        // auto durationView = std::make_shared<DurationView>(999);
    }

    auto &values = m_params.durations;
    for(auto it = begin(values); it != end(values); ++it) {
        int index = std::distance(values.begin(), it);
        auto view = std::make_shared<DurationView>(*it, index);
        addAndMakeVisible(&view->input);
        addAndMakeVisible(&view->label);
        addAndMakeVisible(&view->deleteButton);
        durationViews.emplace_back(view);
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
    auto viewsArea = area.removeFromLeft(200);
    for(auto &&view : durationViews) {
        auto itemArea = viewsArea.removeFromTop(45);
        auto labelArea = itemArea.removeFromLeft(100);
        view->input.setBounds(labelArea.reduced(margin));
        view->deleteButton.setBounds(itemArea.reduced(margin));
    }
    saveButton.setBounds(area.removeFromRight(100));
}

// Private methods
void PrescribedProtocolController::setProtocol()
{
    for(auto &&value : durationViews) {
        DBG("in durationViews" << juce::String(value->paramsDurationValue));
    }

    for(auto &&value : m_params.durations) {
        DBG("in params.durations" << juce::String(value));
    }
}
