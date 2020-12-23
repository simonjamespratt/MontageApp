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
    protocol.onChange = [this] {
        protocolChanged();
    };

    addChildComponent(&adjacentStepsCtrl);
    addChildComponent(&basicCtrl);
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

    auto chooseProtocolArea = area.removeFromTop(45);
    auto protocolColWidth = chooseProtocolArea.getWidth() / 2;
    protocolLabel.setBounds(
        chooseProtocolArea.removeFromLeft(protocolColWidth).reduced(margin));
    protocol.setBounds(chooseProtocolArea.reduced(margin));

    auto controlsArea = area.removeFromTop(50);

    adjacentStepsCtrl.setBounds(controlsArea);
    basicCtrl.setBounds(controlsArea);
}

// Private methods
void FigureParticleSelection::protocolChanged()
{
    adjacentStepsCtrl.setVisible(false);
    basicCtrl.setVisible(false);

    switch(protocol.getSelectedId()) {
    case 1:
        adjacentStepsCtrl.setVisible(true);
        break;
    case 2:
        basicCtrl.setVisible(true);
        break;

    default:
        break;
    }
}
