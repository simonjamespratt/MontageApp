#pragma once
#include <NumberProtocol.hpp>
#include <NumberProtocolParameters.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

struct ProtocolConfig {
    // TODO: Could Aleatoric use NumberProtocol::Type for ActiveProtcol instead
    // of having to have a separate enum class? Also should the nested classes
    // in NumberProtocolParameters be split out to avoid the :: everywhere in
    // the calling code?
    using Type = aleatoric::NumberProtocol::Type;
    using Params = aleatoric::NumberProtocolParameters;
    ProtocolConfig(int id,
                   juce::String name,
                   Type type,
                   Params::Protocols::ActiveProtocol activeType);
    int selectorId;
    juce::String humanName;
    Type protocolType;
    Params::Protocols::ActiveProtocol activeProtocolType;

    static std::vector<ProtocolConfig> getConfigurations();

  private:
    static std::vector<ProtocolConfig> configs;
};
