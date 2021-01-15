#include "ProtocolConfig.h"

ProtocolConfig::ProtocolConfig(
    int id,
    juce::String name,
    aleatoric::NumberProtocol::Type protocolType,
    aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
        activeProtocol)
: m_id(id),
  m_name(name),
  m_protocolType(protocolType),
  m_activeProtocol(activeProtocol)
{}

int ProtocolConfig::getId() const
{
    return m_id;
}

juce::String ProtocolConfig::getName() const
{
    return m_name;
}

aleatoric::NumberProtocol::Type ProtocolConfig::getProtocolType() const
{
    return m_protocolType;
}

aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
ProtocolConfig::getActiveProtocol() const
{
    return m_activeProtocol;
}

// Static stuff
std::vector<ProtocolConfig> ProtocolConfig::configs {
    ProtocolConfig(1,
                   "Adjacent Steps",
                   aleatoric::NumberProtocol::Type::adjacentSteps,
                   aleatoric::NumberProtocolParameters::Protocols::
                       ActiveProtocol::adjacentSteps),
    ProtocolConfig(
        2,
        "Basic",
        aleatoric::NumberProtocol::Type::basic,
        aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol::basic),
    ProtocolConfig(
        3,
        "Cycle",
        aleatoric::NumberProtocol::Type::cycle,
        aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol::cycle)};

std::vector<ProtocolConfig> ProtocolConfig::getConfigurations()
{
    return configs;
}
