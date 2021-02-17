#include "MultiplesProtocolController.h"

MultiplesProtocolController::MultiplesProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  baseIncrementEditor(m_params.multiples.baseIncrement, "Base increment")
{
    addAndMakeVisible(&baseIncrementEditor);

    deviationFactorSlider.setRange(0.0, 100.0);
    deviationFactorSlider.setTextValueSuffix(" %");
    deviationFactorSlider.setValue(m_params.multiples.deviationFactor);
    deviationFactorSlider.onValueChange = [this] {
        m_params.multiples.deviationFactor = deviationFactorSlider.getValue();
    };
    addAndMakeVisible(&deviationFactorSlider);

    deviationFactorLabel.setText("Deviation factor: ",
                                 juce::dontSendNotification);
    deviationFactorLabel.attachToComponent(&deviationFactorSlider, true);
    addAndMakeVisible(&deviationFactorLabel);

    saveButton.setButtonText("Set protocol");
    saveButton.onClick = [this] {
        setProtocol();
    };
    addAndMakeVisible(&saveButton);
}

void MultiplesProtocolController::paint(juce::Graphics &g)
{}

void MultiplesProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    auto topBit = area.removeFromTop(45);
    baseIncrementEditor.setBounds(topBit.removeFromLeft(250));
    saveButton.setBounds(topBit.reduced(margin));
    auto devFactorArea = area.removeFromTop(45);
    devFactorArea.removeFromLeft(100); // label gutter
    deviationFactorSlider.setBounds(devFactorArea.reduced(margin));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{
    DBG("dev factor: " << m_params.multiples.deviationFactor);
}
