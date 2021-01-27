#include "NumberProtocolConfig.h"

#include <algorithm>

NumberProtocolConfig::NumberProtocolConfig(
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

int NumberProtocolConfig::getId() const
{
    return m_id;
}

juce::String NumberProtocolConfig::getName() const
{
    return m_name;
}

aleatoric::NumberProtocol::Type NumberProtocolConfig::getProtocolType() const
{
    return m_protocolType;
}

aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
NumberProtocolConfig::getActiveProtocol() const
{
    return m_activeProtocol;
}

// Static stuff
std::vector<NumberProtocolConfig> NumberProtocolConfig::configs {
    NumberProtocolConfig(1,
                         "Adjacent Steps",
                         aleatoric::NumberProtocol::Type::adjacentSteps,
                         aleatoric::NumberProtocolParameters::Protocols::
                             ActiveProtocol::adjacentSteps),
    NumberProtocolConfig(
        2,
        "Basic",
        aleatoric::NumberProtocol::Type::basic,
        aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol::basic),
    NumberProtocolConfig(
        3,
        "Cycle",
        aleatoric::NumberProtocol::Type::cycle,
        aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol::cycle)};

std::vector<NumberProtocolConfig> NumberProtocolConfig::getConfigurations()
{
    return configs;
}

NumberProtocolConfig NumberProtocolConfig::findByActiveProtocol(
    const aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
        &activeProtocol)
{
    auto it =
        std::find_if(configs.begin(),
                     configs.end(),
                     [&activeProtocol](const NumberProtocolConfig &config) {
                         return config.getActiveProtocol() == activeProtocol;
                     });
    jassert(it != configs.end());
    return *it;
}

NumberProtocolConfig NumberProtocolConfig::findById(const int &id)
{
    auto it = std::find_if(configs.begin(),
                           configs.end(),
                           [&id](const NumberProtocolConfig &config) {
                               return config.getId() == id;
                           });
    jassert(it != configs.end());
    return *it;
}
