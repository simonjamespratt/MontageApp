#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

#include <memory>

struct NumericParamWithLabel : public juce::Component {
    NumericParamWithLabel(int &paramValue, juce::String labelText);
    void resized() override;

  private:
    int &value;
    juce::TextEditor input;
    juce::Label label;
};

class GeometricProtocolController : public DurationProtocolController {
  public:
    GeometricProtocolController(
        DurationProtocolParams &params,
        std::shared_ptr<aleatoric::DurationsProducer> producer);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;

    DurationProtocolParams &m_params;
    std::shared_ptr<aleatoric::DurationsProducer> m_producer;

    NumericParamWithLabel rangeStart;
    NumericParamWithLabel rangeEnd;
    NumericParamWithLabel collectionSize;
    juce::TextButton saveButton;
};
