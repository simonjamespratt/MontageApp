#pragma once
#include <NumberProtocol.hpp>
#include <NumberProtocolParameters.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

struct ProtocolConfig {
    // TODO: FIG-GEN-UI: Could Aleatoric use NumberProtocol::Type for
    // ActiveProtcol instead of having to have a separate enum class? Also
    // should the nested classes in NumberProtocolParameters be split out to
    // avoid the :: everywhere in the calling code?
    ProtocolConfig(
        int id,
        juce::String name,
        aleatoric::NumberProtocol::Type protocolType,
        aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
            activeProtocol);
    int getId() const;
    juce::String getName() const;
    aleatoric::NumberProtocol::Type getProtocolType() const;
    aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
    getActiveProtocol() const;

    static std::vector<ProtocolConfig> getConfigurations();

    static ProtocolConfig findByActiveProtocol(
        const aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
            &activeProtocol);

    static ProtocolConfig findById(const int &id);

  private:
    int m_id;
    juce::String m_name;
    aleatoric::NumberProtocol::Type m_protocolType;
    aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
        m_activeProtocol;

    static std::vector<ProtocolConfig> configs;
};
