#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

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
    GeometricProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;

    DurationProtocolParams &m_params;
    juce::Label rangeStartLabel;
    juce::TextEditor rangeStartInput;
};
