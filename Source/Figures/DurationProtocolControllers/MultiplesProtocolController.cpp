#include "MultiplesProtocolController.h"

SliderWithLabel::SliderWithLabel(double &value,
                                 juce::String labelText,
                                 int textBoxWidth,
                                 juce::String unit,
                                 int decimalPlacesToDisplay)
: m_value(value)
{
    slider.setRange(0.0, 100.0);
    slider.setTextValueSuffix(" %");
    slider.setValue(m_value);
    slider.onValueChange = [this] {
        m_value = slider.getValue();
    };
    slider.setNumDecimalPlacesToDisplay(1);
    slider.setTextBoxStyle(juce::Slider::TextBoxLeft,
                           false,
                           50,
                           slider.getTextBoxHeight());

    addAndMakeVisible(&slider);

    label.setText("Deviation factor: ", juce::dontSendNotification);
    label.attachToComponent(&slider, true);
    addAndMakeVisible(&label);
}

void SliderWithLabel::resized()
{}

// =======================================================================

void MultiplesProtocolController::Container::resized()
{}

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

    // params
    auto paramsArea = area.removeFromLeft(250);

    baseIncrementEditor.setBounds(paramsArea.removeFromTop(45));

    auto devFactorArea = paramsArea.removeFromTop(45);
    devFactorArea.removeFromLeft(100); // label gutter
    deviationFactorSlider.setBounds(devFactorArea.reduced(margin));

    rangeStartEditor.setBounds(paramsArea.removeFromTop(45));
    rangeEndEditor.setBounds(paramsArea.removeFromTop(45));

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{
    DBG("dev factor: " << m_params.multiples.deviationFactor);
}
