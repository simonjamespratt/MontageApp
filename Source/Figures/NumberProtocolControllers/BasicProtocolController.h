#pragma once

#include "NumberProtocolController.h"

class BasicProtocolController : public NumberProtocolController {
  public:
    BasicProtocolController();

    ~BasicProtocolController();

    void paint(juce::Graphics &g) override;

    void resized() override;

    void
    setParams(aleatoric::NumberProtocolParameters::Protocols params) override;

    aleatoric::NumberProtocolParameters::Protocols getParams() override;

  private:
    juce::Label text;
};
