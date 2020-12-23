#include "CycleProtocolController.h"

CycleProtocolController::CycleProtocolController()
: bidirectional("Bidirectional"), reverseDirection("Reverse Direction")
{
    addAndMakeVisible(&bidirectional);
    addAndMakeVisible(&reverseDirection);
    bidirectional.onClick = [this] {
        updateState(bidirectional);
    };
    reverseDirection.onClick = [this] {
        updateState(reverseDirection);
    };
}

CycleProtocolController::~CycleProtocolController()
{}

void CycleProtocolController::paint(juce::Graphics &g)
{}

void CycleProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    bidirectional.setBounds(area.removeFromTop(45).reduced(margin));
    reverseDirection.setBounds(area.removeFromTop(45).reduced(margin));
}

void CycleProtocolController::updateState(juce::Button &button)
{
    auto buttonName = button.getName();
    auto state = button.getToggleState();

    if(buttonName == "Bidirectional") {
        // do something abour bidirectional using state
    }

    if(buttonName == "Reverse Direction") {
        // do something abour Reverse Direction using state
    }
}
