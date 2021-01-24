#pragma once

#include "NumberProtocolSelector.h"

#include <DurationsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

// TODO: FIG-GEN-UI: check that the duration protocol is not set in such a way
// that it will have a collectionSize < 2 as this will cause the number protocol
// to throw error (or at least I think it will). Need to check this in
// Aleatoric. I don't think it is accounted for in the Aleatoric tests.
// Aleatoric should be throwing an error if this behaviour is not allowed
// and then Montage can catch the error and handle the UI messaging
// appropriately. So in short, check if this is disallowed behaviour in
// Aleatoric. If it is, change Aleatoric to handle it with errors, then
// catch them in Montage and handle UI messaging. If it isn't disallowed
// behaviour in Aleatoric, then don't worry about it here!

class FigureOnsetSelection : public juce::Component {
  public:
    FigureOnsetSelection(
        std::shared_ptr<aleatoric::DurationsProducer> durationsProducer);
    ~FigureOnsetSelection();

    void paint(juce::Graphics &) override;
    void resized() override;

  private:
    NumberProtocolSelector numberProtocolSelector;
    juce::Label heading;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureOnsetSelection)
};
