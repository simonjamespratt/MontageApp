#include "PrescribedProtocolController.h"

#include <iterator>

DurationView::DurationView(int &value,
                           int index,
                           std::function<void(int index)> onDelete)
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
    deleteButton.onClick = [index, onDelete] {
        onDelete(index);
    };
};

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    drawView();

    saveButton.setButtonText("Set protocol");
    saveButton.onClick = [this] {
        setProtocol();
    };
    addAndMakeVisible(&saveButton);

    addButton.setButtonText("Add value");
    addButton.onClick = [this] {
        onAdd();
    };
    addAndMakeVisible(&addButton);
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
    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
    addButton.setBounds(area.removeFromTop(45).reduced(margin));
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

void PrescribedProtocolController::drawView()
{
    auto &values = m_params.durations;
    for(auto it = begin(values); it != end(values); ++it) {
        int index = std::distance(values.begin(), it);
        auto view =
            std::make_unique<DurationView>(*it, index, [this](int index) {
                onDelete(index);
            });
        addAndMakeVisible(&view->input);
        addAndMakeVisible(&view->label);
        addAndMakeVisible(&view->deleteButton);
        durationViews.emplace_back(std::move(view));
    }
}

void PrescribedProtocolController::onDelete(int index)
{
    durationViews.clear();
    m_params.durations.erase(m_params.durations.begin() + index);
    drawView();
    resized();
}

void PrescribedProtocolController::onAdd()
{
    durationViews.clear();
    m_params.durations.emplace_back(1);
    drawView();
    resized();
}
