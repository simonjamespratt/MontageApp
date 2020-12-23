#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class BasicProtocolController : public juce::Component {
  public:
    BasicProtocolController();
    ~BasicProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    juce::Label text;
};
