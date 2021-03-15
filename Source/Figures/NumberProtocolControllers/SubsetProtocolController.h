#pragma once

#include "NumberProtocolController.h"
#include "NumericValueEditorWithLabel.h"

class SubsetProtocolController : public NumberProtocolController {
  public:
    SubsetProtocolController(aleatoric::NumberProtocolParams initialParams);
    void setParams(aleatoric::NumberProtocolParams params) override;
    aleatoric::NumberProtocolParams getParams() override;
    void resized() override;

  private:
    int min;
    int max;

    NumericValueEditorWithLabel minEditor;
    NumericValueEditorWithLabel maxEditor;
};
