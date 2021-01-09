#pragma once

#include <NumberProtocolParameters.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

class CycleProtocolController : public juce::Component {
    using Listener = std::function<void()>;

  public:
    CycleProtocolController();
    ~CycleProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;
    void
    setInitialDefaults(aleatoric::NumberProtocolParameters::Protocols params);

    // TODO: rename to attach()
    void addListener(Listener listener);

    // TODO: add method to detach()

    void notify();

  private:
    juce::ToggleButton bidirectional;
    juce::ToggleButton reverseDirection;

    std::vector<Listener> listeners;

    void updateState(juce::Button &button);
};
