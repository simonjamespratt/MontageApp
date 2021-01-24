#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class DurationProtocolSelector : public juce::Component {
    DurationProtocolSelector();
    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    juce::Label protocolSelectorLabel;
    juce::ComboBox protocolSelector;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DurationProtocolSelector)
};
