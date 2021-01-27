#include "DurationProtocolConfig.h"

DurationProtocolConfig::DurationProtocolConfig(int id, juce::String name)
: m_id(id), m_name(name)
{}

int DurationProtocolConfig::getId() const
{
    return m_id;
}

juce::String DurationProtocolConfig::getName() const
{
    return m_name;
}

// Static stuff
std::vector<DurationProtocolConfig> DurationProtocolConfig::configs {
    DurationProtocolConfig(1, "Geometric"),
    DurationProtocolConfig(2, "Multiples"),
    DurationProtocolConfig(3, "Prescribed")};

std::vector<DurationProtocolConfig> DurationProtocolConfig::getConfigurations()
{
    return configs;
}
