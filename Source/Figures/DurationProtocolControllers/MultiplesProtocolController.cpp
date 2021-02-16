#include "MultiplesProtocolController.h"

MultiplesProtocolController::MultiplesProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  baseIncrementEditor(m_params.multiples.baseIncrement, "Base increment")
{
    addAndMakeVisible(&baseIncrementEditor);
}

void MultiplesProtocolController::paint(juce::Graphics &g)
{}

void MultiplesProtocolController::resized()
{
    auto area = getLocalBounds();
    baseIncrementEditor.setBounds(area.removeFromTop(45));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{}
