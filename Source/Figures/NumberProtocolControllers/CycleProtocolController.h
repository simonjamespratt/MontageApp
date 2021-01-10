#pragma once

#include <NumberProtocolParameters.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

class CycleProtocolController : public juce::Component {
    using Observer = std::function<void(
        aleatoric::NumberProtocolParameters::Protocols newParams)>;

  public:
    CycleProtocolController();
    ~CycleProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;
    void
    setInitialDefaults(aleatoric::NumberProtocolParameters::Protocols params);
    aleatoric::NumberProtocolParameters::Protocols getParams();

    // Observers
    void attach(Observer observer);
    void notifyParamsChanged();

  private:
    bool isBidirectional = false;
    bool isReverseDirection = false;
    juce::ToggleButton bidirectionalToggle;
    juce::ToggleButton reverseDirectionToggle;

    std::vector<Observer> observers;

    void updateState(juce::Button &button);
};
