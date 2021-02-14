#pragma once
#include "DurationProtocolController.h"

#include <juce_gui_basics/juce_gui_basics.h>
#include <vector>

struct PrescribedProtocolParams {
    std::vector<int> durations {1000, 2000};
};

struct GeometricProtocolParams {
    int rangeStart = 1;
    int rangeEnd = 10;
    int collectionSize = 5;
};

struct DurationProtocolParams {
    DurationProtocolParams(DurationProtocolController::Type type);
    DurationProtocolController::Type activeType;
    std::vector<int> durations {};
    PrescribedProtocolParams prescribed;
    GeometricProtocolParams geometric;
};
