#pragma once
#include <NumberProtocol.hpp>
#include <NumberProtocolParameters.hpp>
#include <functional>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>
#include <vector>

class NumberProtocolController : public juce::Component {
    using Params = aleatoric::NumberProtocolParameters::Protocols;
    using Observer = std::function<void(Params newParams)>;
    using Type = aleatoric::NumberProtocol::Type;

  public:
    virtual void
    setParams(aleatoric::NumberProtocolParameters::Protocols params) = 0;

    virtual aleatoric::NumberProtocolParameters::Protocols getParams() = 0;

    virtual ~NumberProtocolController() = default;

    // Observers
    void attach(Observer observer);

    void notifyParamsChanged();

    // Factory
    static std::unique_ptr<NumberProtocolController> create(Type type,
                                                            Params params);

  private:
    std::vector<Observer> observers;
};
