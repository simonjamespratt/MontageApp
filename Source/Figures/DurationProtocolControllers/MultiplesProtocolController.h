#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"
#include "NumericValueEditorWithLabel.h"

#include <memory>

class MultiplesProtocolController : public DurationProtocolController {
  public:
    MultiplesProtocolController(
        DurationProtocolParams &params,
        std::shared_ptr<aleatoric::DurationsProducer> producer);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;

    DurationProtocolParams &m_params;
    std::shared_ptr<aleatoric::DurationsProducer> m_producer;

    NumericValueEditorWithLabel baseIncrementEditor;
    // TODO: Add deviation factor as a knob ot slider

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultiplesProtocolController)
};
