#pragma once
#include "DurationProtocolController.h"
#include "DurationProtocolParams.h"

#include <vector>

class PrescribedProtocolController : public DurationProtocolController {
  public:
    PrescribedProtocolController(DurationProtocolParams &params);
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    void setProtocol() override;
    DurationProtocolParams &m_params;
    std::vector<juce::Label> durationValues {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PrescribedProtocolController)
};
