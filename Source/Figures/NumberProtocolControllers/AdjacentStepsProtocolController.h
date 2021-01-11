#pragma once
#include "NumberProtocolController.h"

class AdjacentStepsProtocolController : public NumberProtocolController {
  public:
    AdjacentStepsProtocolController();

    ~AdjacentStepsProtocolController();

    void paint(juce::Graphics &g) override;

    void resized() override;

    void
    setParams(aleatoric::NumberProtocolParameters::Protocols params) override;

    aleatoric::NumberProtocolParameters::Protocols getParams() override;

  private:
    juce::Label text;
};
