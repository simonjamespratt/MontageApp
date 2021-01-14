#include "ProtocolConfig.h"

ProtocolConfig::ProtocolConfig(int id,
                               juce::String name,
                               Type type,
                               Params::Protocols::ActiveProtocol activeType)
: selectorId(id),
  humanName(name),
  protocolType(type),
  activeProtocolType(activeType)
{}

std::vector<ProtocolConfig> ProtocolConfig::configs {
    ProtocolConfig(1,
                   "Adjacent Steps",
                   Type::adjacentSteps,
                   Params::Protocols::ActiveProtocol::adjacentSteps),
    ProtocolConfig(
        2, "Basic", Type::basic, Params::Protocols::ActiveProtocol::basic),
    ProtocolConfig(
        3, "Cycle", Type::cycle, Params::Protocols::ActiveProtocol::cycle)};

std::vector<ProtocolConfig> ProtocolConfig::getConfigurations()
{
    return configs;
}
