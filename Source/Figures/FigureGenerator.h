#pragma once

#include "Figure.h"
#include "FigureOnsetSelection.h"
#include "FigureParticleSelection.h"
#include "Identifiers.h"
#include "ParticleCollection.h"

#include <CollectionsProducer.hpp>
#include <DurationsProducer.hpp>
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

    // TODO: I think there's a problem with AdjacentSteps protocol which doesn't
    // seem to be selecting anything other than the first and second particles.
    // Hunch is that this is because params are not being set correctly to
    // mirror the size of the collection that the CollectionProducer is working
    // with. This could be an indicator of a general problem at the
    // CollectionProducer level in Montage or in Aleatoric, or it could be a bug
    // with just AdjacentSteps protocol. Check the former first. Reason for
    // hunch is that protocols are set to a range of 0-1 on construction and
    // require params being set to change this.
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> particleProducer;
    std::unique_ptr<FigureParticleSelection> figureParticleSelection;

    // TODO: DurationProtocols take some of their constructor args by const ref.
    // (e.g. Prescribed takes durations this way) and keeps a const ref to them
    // as private members of the class instance. This means you can't pass by
    // value and more importantly, means that if you change the thing it is
    // referencing, it'll be updated in the DurationProtocol and therefore could
    // cause internal issues as I don't think this was ever the intention of
    // using const ref. I think the intention was to avoid passing potentially
    // large blocks of memory by value. This is a premature enhancement. Suggest
    // changing DurationProtocols to pass by value and set their members by
    // value also.
    aleatoric::DurationsProducer onsetProducer;
    FigureOnsetSelection figureOnsetSelection;

    juce::Label blockedMessage;
    juce::Label globalSettingsHeading;
    juce::TextEditor numEventsInput;
    juce::Label numEventsLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FigureGenerator)
};
