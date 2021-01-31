#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

class DurationProtocolController : public juce::Component {
  public:
    virtual ~DurationProtocolController() = default;

    enum class Type { geometric, multiples, prescribed };

    // Factory
    static std::unique_ptr<DurationProtocolController> create(Type type);

  private:
    virtual void setProtocol() = 0;
};
