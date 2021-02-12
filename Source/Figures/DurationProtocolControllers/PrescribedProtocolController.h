#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

#include <functional>
#include <memory>
#include <vector>

// TODO: set the protocol using params
// TODO: make the area scrollable

struct DurationView : public juce::Component {
    DurationView(int &value,
                 int index,
                 std::function<void(int index)> onDelete);
    void resized() override;
    juce::Label label;
    juce::TextEditor input;
    juce::TextButton deleteButton;
    int &paramsDurationValue;

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DurationView)
};

struct DurationViewCollection : public juce::Component {
    void resized() override;

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DurationViewCollection)
};

class PrescribedProtocolController : public DurationProtocolController {
  public:
    PrescribedProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    void drawView();
    void onDelete(int index);
    void onAdd();
    DurationProtocolParams &m_params;

    // NB: have to use pointers because juce components have their copy
    // constructors deleted and both vector and list (despite what link below
    // says) require objects being stored to have copy constructors. See:
    // https://forum.juce.com/t/adding-components-to-std-vector-with-emplace-back/35193
    std::vector<std::unique_ptr<DurationView>> durationViews {};

    juce::TextButton saveButton;
    juce::TextButton addButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrescribedProtocolController)
};
