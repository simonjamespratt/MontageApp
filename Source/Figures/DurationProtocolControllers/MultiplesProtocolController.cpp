#include "MultiplesProtocolController.h"

MultiplesProtocolController::MultiplesProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  baseIncrementEditor(m_params.multiples.baseIncrement, "Base increment"),
  rangeStartEditor(m_params.multiples.rangeStart, "Range start"),
  rangeEndEditor(m_params.multiples.rangeEnd, "Range end")
{
    addAndMakeVisible(&baseIncrementEditor);

    deviationFactorSlider.setRange(0.0, 100.0);
    deviationFactorSlider.setTextValueSuffix(" %");
    deviationFactorSlider.setValue(m_params.multiples.deviationFactor);
    deviationFactorSlider.onValueChange = [this] {
        m_params.multiples.deviationFactor = deviationFactorSlider.getValue();
    };
    deviationFactorSlider.setNumDecimalPlacesToDisplay(1);
    deviationFactorSlider.setTextBoxStyle(
        juce::Slider::TextBoxLeft,
        false,
        50,
        deviationFactorSlider.getTextBoxHeight());

    addAndMakeVisible(&deviationFactorSlider);

    deviationFactorLabel.setText("Deviation factor: ",
                                 juce::dontSendNotification);
    deviationFactorLabel.attachToComponent(&deviationFactorSlider, true);
    addAndMakeVisible(&deviationFactorLabel);

    addAndMakeVisible(&rangeStartEditor);
    addAndMakeVisible(&rangeEndEditor);

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
    auto paramsArea = area.removeFromLeft(250);
    // auto topBit = area.removeFromTop(45);
    baseIncrementEditor.setBounds(paramsArea.removeFromTop(45));

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));

    auto devFactorArea = paramsArea.removeFromTop(45);
    devFactorArea.removeFromLeft(100); // label gutter
    deviationFactorSlider.setBounds(devFactorArea.reduced(margin));

    rangeStartEditor.setBounds(paramsArea.removeFromTop(45));
    rangeEndEditor.setBounds(paramsArea.removeFromTop(45));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{
    DBG("dev factor: " << m_params.multiples.deviationFactor);
}
