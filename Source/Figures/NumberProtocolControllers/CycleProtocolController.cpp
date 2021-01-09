#include "CycleProtocolController.h"

CycleProtocolController::CycleProtocolController()
: bidirectionalToggle("Bidirectional"),
  reverseDirectionToggle("Reverse Direction")
{
    addAndMakeVisible(&bidirectionalToggle);
    addAndMakeVisible(&reverseDirectionToggle);
    bidirectionalToggle.onClick = [this] {
        updateState(bidirectionalToggle);
    };
    reverseDirectionToggle.onClick = [this] {
        updateState(reverseDirectionToggle);
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
    bidirectionalToggle.setBounds(area.removeFromTop(45).reduced(margin));
    reverseDirectionToggle.setBounds(area.removeFromTop(45).reduced(margin));
}

void CycleProtocolController::setInitialDefaults(
    aleatoric::NumberProtocolParameters::Protocols params)
{
    jassert(
        params.getActiveProtocol() ==
        aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol::cycle);

    auto cylceParams = params.getCycle();

    isBidirectional = cylceParams.getBidirectional();
    bidirectionalToggle.setToggleState(isBidirectional,
                                       juce::dontSendNotification);

    isReverseDirection = cylceParams.getReverseDirection();
    reverseDirectionToggle.setToggleState(isReverseDirection,
                                          juce::dontSendNotification);
}

aleatoric::NumberProtocolParameters::Protocols
CycleProtocolController::getParams()
{
    return aleatoric::NumberProtocolParameters::Protocols(
        aleatoric::NumberProtocolParameters::Cycle(isBidirectional,
                                                   isReverseDirection));
}

// Observers
void CycleProtocolController::attach(Observer observer)
{
    observers.emplace_back(observer);
}

void CycleProtocolController::notifyParamsChanged()
{
    for(auto const &observer : observers) {
        observer();
    }
}

// Private methods
void CycleProtocolController::updateState(juce::Button &button)
{
    auto buttonName = button.getName();
    auto state = button.getToggleState();

    if(buttonName == "Bidirectional") {
        isBidirectional = state;
    }

    if(buttonName == "Reverse Direction") {
        isReverseDirection = state;
    }

    notifyParamsChanged();
}
