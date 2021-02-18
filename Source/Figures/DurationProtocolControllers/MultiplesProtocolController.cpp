#include "MultiplesProtocolController.h"

void MultiplesProtocolController::Container::resized()
{}

MultiplesProtocolController::MultiplesProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  baseIncrementEditor(m_params.multiples.baseIncrement, "Base increment"),
  rangeStartEditor(m_params.multiples.rangeStart, "Range start"),
  rangeEndEditor(m_params.multiples.rangeEnd, "Range end"),
  deviationFactorEditor(m_params.multiples.deviationFactor,
                        "Deviation factor",
                        0,
                        100.0,
                        "%",
                        1,
                        50)
{
    addAndMakeVisible(&baseIncrementEditor);
    addAndMakeVisible(&rangeStartEditor);
    addAndMakeVisible(&rangeEndEditor);
    addAndMakeVisible(&deviationFactorEditor);

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
    deviationFactorEditor.setBounds(paramsArea.removeFromTop(45));
    rangeStartEditor.setBounds(paramsArea.removeFromTop(45));
    rangeEndEditor.setBounds(paramsArea.removeFromTop(45));

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{
    DBG("dev factor: " << m_params.multiples.deviationFactor);
}
