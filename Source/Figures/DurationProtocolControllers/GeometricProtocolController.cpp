#include "GeometricProtocolController.h"

NumericParamWithLabel::NumericParamWithLabel(int &paramValue,
                                             juce::String labelText) : value(paramValue)
{}

void NumericParamWithLabel::resized()
{}

GeometricProtocolController::GeometricProtocolController(
    DurationProtocolParams &params)
: m_params(params)
{
    rangeStartInput.setText(juce::String(m_params.geometric.rangeStart));
    rangeStartInput.setInputRestrictions(0, "0123456789");
    rangeStartInput.setJustification(juce::Justification::centredLeft);
    rangeStartInput.onTextChange = [this] {
        m_params.geometric.rangeStart = rangeStartInput.getText().getIntValue();
    };

    rangeStartLabel.setText("Range start: ", juce::dontSendNotification);
    rangeStartLabel.attachToComponent(&rangeStartInput, true);

    addAndMakeVisible(&rangeStartInput);
    addAndMakeVisible(&rangeStartLabel);
}

void GeometricProtocolController::paint(juce::Graphics &g)
{}

void GeometricProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    area.removeFromLeft(100); // labels gutter
    rangeStartInput.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void GeometricProtocolController::setProtocol()
{}
