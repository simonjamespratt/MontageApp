#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class AdjacentStepsProtocolController : public juce::Component {
  public:
    AdjacentStepsProtocolController();
    ~AdjacentStepsProtocolController();
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    juce::Label text;
};
