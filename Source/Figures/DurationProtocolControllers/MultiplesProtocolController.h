#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"
#include "NumericValueEditorWithLabel.h"

#include <memory>

class SliderWithLabel : public juce::Component {
  public:
    SliderWithLabel(double &value,
                    juce::String labelText,
                    int textBoxWidth = 100,
                    juce::String unit = "",
                    int decimalPlacesToDisplay = 2);
    void resized() override;

  private:
    double &m_value;
    juce::Slider slider;
    juce::Label label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderWithLabel)
};

class MultiplesProtocolController : public DurationProtocolController {
  public:
    MultiplesProtocolController(
        DurationProtocolParams &params,
        std::shared_ptr<aleatoric::DurationsProducer> producer);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    struct Container : public juce::Component {
        Container() = default;
        void resized() override;

      private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Container)
    };

    void setProtocol() override;

    DurationProtocolParams &m_params;
    std::shared_ptr<aleatoric::DurationsProducer> m_producer;

    NumericValueEditorWithLabel baseIncrementEditor;
    SliderWithLabel deviationFactorEditor;

    NumericValueEditorWithLabel rangeStartEditor;
    NumericValueEditorWithLabel rangeEndEditor;

    Container container;

    juce::Viewport viewport;

    juce::TextButton saveButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MultiplesProtocolController)
};
