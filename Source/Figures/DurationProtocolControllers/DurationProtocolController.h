#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class DurationProtocolController : public juce::Component {
  public:
    virtual ~DurationProtocolController() = default;

    enum class Type { geometric, multiples, prescribed };

  private:
    virtual void setProtocol() = 0;
};
