#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

struct DurationProtocolConfig {
    DurationProtocolConfig(int id, juce::String name);
    int getId() const;
    juce::String getName() const;

    static std::vector<DurationProtocolConfig> getConfigurations();

  private:
    int m_id;
    juce::String m_name;

    static std::vector<DurationProtocolConfig> configs;
};
