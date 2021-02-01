#pragma once
#include "DurationProtocolController.h"

#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

// TODO: Data management: in future this could be a value tree.
struct DurationProtocolParams {
    DurationProtocolParams(DurationProtocolController::Type type);
    DurationProtocolController::Type activeType;
    std::vector<int> durations {};
};
