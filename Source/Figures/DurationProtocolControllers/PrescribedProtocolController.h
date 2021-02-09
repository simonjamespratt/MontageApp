#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

#include <memory>
#include <tuple>
#include <vector>

// TODO: add value
// TODO: delete value
// TODO: set the protocol using params
class PrescribedProtocolController : public DurationProtocolController {
  public:
    PrescribedProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    juce::Identifier duration_id {"duration"};
    juce::Identifier duration_value_id {"duration_value"};
    juce::Identifier durations_model_id {"durations_model"};
    juce::ValueTree durationsModel {durations_model_id};

    struct DurationView {
        DurationView(int &value, int index);
        juce::Label label;
        juce::TextEditor input;
        juce::TextButton deleteButton;
        juce::ValueTree duration;
        int &paramsDurationValue;
    };

    void setProtocol() override;
    DurationProtocolParams &m_params;

    // NB: have to use pointers because juce components have their copy
    // constructors deleted and both vector and list (despite what link below
    // says) require objects being stored to have copy constructors. See:
    // https://forum.juce.com/t/adding-components-to-std-vector-with-emplace-back/35193
    std::vector<std::shared_ptr<DurationView>> durationViews {};

    juce::TextButton saveButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrescribedProtocolController)
};
