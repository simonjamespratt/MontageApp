#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

#include <memory>
#include <tuple>
#include <vector>

// TODO: add value
// TODO: delete value
// TODO: add button to set protocol
// TODO: set the protocol using params
class PrescribedProtocolController : public DurationProtocolController {
  public:
    PrescribedProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    struct Value {
        Value(int &value);
        juce::Label label;
        juce::TextEditor input;
        int &paramsDurationValue;
    };

    void setProtocol() override;
    DurationProtocolParams &m_params;

    // NB: have to use pointers because juce components have their copy
    // constructors deleted and both vector and list (despite what link below
    // says) require objects being stored to have copy constructors. See:
    // https://forum.juce.com/t/adding-components-to-std-vector-with-emplace-back/35193
    std::vector<std::shared_ptr<Value>> durationValues {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrescribedProtocolController)
};
