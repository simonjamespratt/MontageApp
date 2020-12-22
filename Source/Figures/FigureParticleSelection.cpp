#include "FigureParticleSelection.h"

FigureParticleSelection::FigureParticleSelection()
{
    heading.setText("Particle selection", juce::dontSendNotification);
    addAndMakeVisible(&heading);
    heading.setFont(juce::Font(20.0f, juce::Font::bold));

    protocolLabel.setText("Selection strategy: ", juce::dontSendNotification);
    addAndMakeVisible(&protocolLabel);

    addAndMakeVisible(&protocol);
    protocol.addItem("AdjacentSteps", 1);
    protocol.addItem("Basic", 2);
}

FigureParticleSelection::~FigureParticleSelection()
{}

void FigureParticleSelection::paint(juce::Graphics &g)
{}

void FigureParticleSelection::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();

    heading.setBounds(area.removeFromTop(50));

    auto protocolArea = area.removeFromTop(45);
    auto protocolColWidth = protocolArea.getWidth() / 2;
    protocolLabel.setBounds(
        protocolArea.removeFromLeft(protocolColWidth).reduced(margin));
    protocol.setBounds(protocolArea.reduced(margin));
}
