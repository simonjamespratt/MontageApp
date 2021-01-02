#pragma once

#include "Figure.h"
#include "FigureParticleSelection.h"
#include "Identifiers.h"
#include "ParticleCollection.h"

#include <CollectionsProducer.hpp>
#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

class FigureGenerator : public juce::Component,
                        public juce::ValueTree::Listener {
  public:
    FigureGenerator(juce::ValueTree as);
    ~FigureGenerator();

    void paint(juce::Graphics &) override;
    void resized() override;

    // TODO: Data management: VT listeners - reevaluate when proper data
    // handling is implemented
    void valueTreeChildAdded(juce::ValueTree &parent,
                             juce::ValueTree &childAdded) override;

    void valueTreeChildRemoved(juce::ValueTree &parent,
                               juce::ValueTree &childRemoved,
                               int index) override;

    Figure generateFigure();

  private:
    juce::ValueTree appState;
    std::unique_ptr<ParticleCollection> particleCollection;
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> particleProducer;

    juce::Label blockedMessage;
    juce::Label globalSettingsHeading;
    juce::TextEditor numEventsInput;
    juce::Label numEventsLabel;

    std::unique_ptr<FigureParticleSelection> figureParticleSelection;

    juce::Label onsetSelectionHeading;

    // TODO: allow UI dropdown and settings UI to update protocol params

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureGenerator)
};
