#include "GeometricProtocolController.h"

NumericParamWithLabel::NumericParamWithLabel(int &paramValue,
                                             juce::String labelText)
: value(paramValue)
{
    input.setText(juce::String(value));
    input.setInputRestrictions(0, "0123456789");
    input.setJustification(juce::Justification::centredLeft);
    input.onTextChange = [this] {
        value = input.getText().getIntValue();
    };

    label.setText(labelText + ": ", juce::dontSendNotification);
    label.attachToComponent(&input, true);

    addAndMakeVisible(&input);
    addAndMakeVisible(&label);
}

void NumericParamWithLabel::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    area.removeFromLeft(100); // label gutter
    input.setBounds(area.removeFromLeft(100).reduced(margin));
}

GeometricProtocolController::GeometricProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  rangeStart(m_params.geometric.rangeStart, "Range start"),
  rangeEnd(m_params.geometric.rangeEnd, "Range end"),
  collectionSize(m_params.geometric.collectionSize, "Collection size")
{
    addAndMakeVisible(&rangeStart);
    addAndMakeVisible(&rangeEnd);
    addAndMakeVisible(&collectionSize);

    saveButton.setButtonText("Set protocol");
    saveButton.onClick = [this] {
        setProtocol();
    };
    addAndMakeVisible(&saveButton);
}

void GeometricProtocolController::paint(juce::Graphics &g)
{}

void GeometricProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();

    // Params controllers
    auto paramsArea = area.removeFromLeft(250);
    rangeStart.setBounds(paramsArea.removeFromTop(45));
    rangeEnd.setBounds(paramsArea.removeFromTop(45));
    collectionSize.setBounds(paramsArea.removeFromTop(45));

    // Save
    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void GeometricProtocolController::setProtocol()
{
    auto &params = m_params.geometric;
    m_producer->setDurationProtocol(
        aleatoric::DurationProtocol::createGeometric(
            aleatoric::Range(params.rangeStart, params.rangeEnd),
            params.collectionSize));
}
