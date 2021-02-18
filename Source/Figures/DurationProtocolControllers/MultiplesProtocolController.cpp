#include "MultiplesProtocolController.h"

void MultiplesProtocolController::Container::resized()
{
    int componentHeight = 45;

    auto totalHeight = getNumChildComponents() * componentHeight;
    setSize(getWidth(), totalHeight);

    auto area = getLocalBounds();

    for(auto *child : getChildren()) {
        child->setBounds(area.removeFromTop(componentHeight));
    }
}

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
    container.addAndMakeVisible(&baseIncrementEditor);
    container.addAndMakeVisible(&rangeStartEditor);
    container.addAndMakeVisible(&rangeEndEditor);
    container.addAndMakeVisible(&deviationFactorEditor);

    viewport.setViewedComponent(&container, false);
    viewport.setScrollBarsShown(true, false);
    addAndMakeVisible(&viewport);

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
    container.setBounds(paramsArea);
    viewport.setBounds(paramsArea);
    // baseIncrementEditor.setBounds(paramsArea.removeFromTop(45));
    // deviationFactorEditor.setBounds(paramsArea.removeFromTop(45));
    // rangeStartEditor.setBounds(paramsArea.removeFromTop(45));
    // rangeEndEditor.setBounds(paramsArea.removeFromTop(45));

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{
    DBG("dev factor: " << m_params.multiples.deviationFactor);
}
