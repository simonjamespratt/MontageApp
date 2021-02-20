#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"
#include "NumericCollectionEditor.h"
#include "NumericValueEditorWithLabel.h"
#include "SliderWithLabel.h"

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
    SliderWithLabel deviationFactorEditor;

    NumericValueEditorWithLabel rangeStartEditor;
    NumericValueEditorWithLabel rangeEndEditor;

    NumericCollectionEditor multipliersByHandEditor;
    juce::Viewport multipliersByHandEditorViewport;

    juce::TextButton saveButton;

    juce::Label multipliersSelectionHeading;
    juce::ToggleButton multipliersByRange {"By Range"};
    juce::ToggleButton multipliersByHand {"By hand"};
    int multipliersRadioGroup = 1001;
    void toggleMultiplierStrategy(juce::Button *button, juce::String name);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultiplesProtocolController)
};
