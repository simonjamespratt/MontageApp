#include "PrescribedProtocolController.h"

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  durationsEditor(m_params.prescribed.durations)
{
    viewport.setViewedComponent(&durationsEditor, false);
    viewport.setScrollBarsShown(true, false);
    addAndMakeVisible(&viewport);

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

    auto viewsArea = area.removeFromLeft(250);
    viewport.setBounds(viewsArea);
    durationsEditor.setBounds(viewsArea);

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void PrescribedProtocolController::setProtocol()
{
    for(auto &&i : m_params.prescribed.durations) {
        DBG("duration: " << i);
    }

    m_producer->setDurationProtocol(
        aleatoric::DurationProtocol::createPrescribed(
            m_params.prescribed.durations));
}
