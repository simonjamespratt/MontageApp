#pragma once
#include <NumberProtocolParameters.hpp>
#include <functional>
#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

class NumberProtocolController : public juce::Component {
    using Observer = std::function<void(
        aleatoric::NumberProtocolParameters::Protocols newParams)>;

  public:
    virtual aleatoric::NumberProtocolParameters::Protocols getParams() = 0;
    virtual ~NumberProtocolController() = default;

    // Observers
    void attach(Observer observer);
    void notifyParamsChanged();

  private:
    std::vector<Observer> observers;
};
