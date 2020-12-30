#include "FigureGenerator.h"

#include "FigureCollection.h"
#include "FigureProcessor.h"

#include <DurationsProducer.hpp>

FigureGenerator::FigureGenerator(juce::ValueTree as) : appState(as)
{
    // TODO: Data management: when proper data handling is in place this will
    // need to be addressed
    appState.addListener(this);

    addAndMakeVisible(&blockedMessage);
    blockedMessage.setText("Not enough particles to generate a figure",
                           juce::dontSendNotification);

    // GLOBAL
    globalSettingsHeading.setText("Global settings",
                                  juce::dontSendNotification);
    addChildComponent(&globalSettingsHeading);
    globalSettingsHeading.setFont(juce::Font(20.0f, juce::Font::bold));

    numEventsInput.setText("0", juce::dontSendNotification);
    addChildComponent(&numEventsInput);
    numEventsInput.setInputRestrictions(0, "0123456789");
    numEventsInput.setJustification(juce::Justification::centredLeft);

    numEventsLabel.setText("Number of events: ", juce::dontSendNotification);
    addChildComponent(&numEventsLabel);

    addChildComponent(&figureParticleSelection);

    // ONSET SELECTION
    onsetSelectionHeading.setText("Onset selection",
                                  juce::dontSendNotification);
    addChildComponent(&onsetSelectionHeading);
    onsetSelectionHeading.setFont(juce::Font(20.0f, juce::Font::bold));
}

FigureGenerator::~FigureGenerator()
{}

void FigureGenerator::paint(juce::Graphics &g)
{}

void FigureGenerator::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    auto colWidth = area.getWidth() / 3;

    blockedMessage.setBounds(area);

    auto globalSettingsArea = area.removeFromLeft(colWidth);
    globalSettingsHeading.setBounds(globalSettingsArea.removeFromTop(50));

    auto numEventsArea = globalSettingsArea.removeFromTop(45);
    auto numEventsColWidth = numEventsArea.getWidth() / 3;
    numEventsLabel.setBounds(
        numEventsArea.removeFromLeft(numEventsColWidth * 2).reduced(margin));
    numEventsInput.setBounds(
        numEventsArea.removeFromRight(numEventsColWidth).reduced(margin));

    auto particleSelectionArea = area.removeFromLeft(colWidth);
    figureParticleSelection.setBounds(particleSelectionArea);

    auto onsetSelectionArea = area;
    onsetSelectionHeading.setBounds(onsetSelectionArea.removeFromTop(50));
}

Figure FigureGenerator::generateFigure()
{
    using namespace aleatoric;

    // NB: note that particles is NOT a member of the class and only gets
    // particles from appState at the last minute, just before using it. This is
    // because of the difference between a copy and a reference. appState is a
    // reference which will update, whereas a copy won't so if you try and take
    // a copy of particles from appState in the constructor, you will have an
    // outdated version copies as members work fine when you are using ValueTree
    // listeners because you can update the member (copy) when you get a
    // notification from the listener but all you are really doing is the same
    // as here - taking a copy from the reference to appState particles here
    // could be a reference but I can't work out how to initialize it properly
    auto particleCollectionState = appState.getChildWithName(IDs::PARTICLES);
    ParticleCollection particleCollection(particleCollectionState);

    auto figureCollectionState = appState.getChildWithName(IDs::FIGURES);
    FigureCollection figureCollection(figureCollectionState);

    // TODO: delete this when UI for selection of protocol etc. is in place
    int numOfEventsToMake = 8;
    std::vector<int> durations {1000, 2000};

    // Basic predictable results using prescribed durations and cycling of
    // durations and particles
    DurationsProducer durationsProducer(
        DurationProtocol::createPrescribed(durations),
        NumberProtocol::create(NumberProtocol::Type::cycle));

    CollectionsProducer<Particle> collectionsProducer(
        particleCollection.getParticles(),
        NumberProtocol::create(NumberProtocol::Type::cycle));

    FigureProcessor processor;
    return processor.composeFigure(numOfEventsToMake,
                                   durationsProducer,
                                   collectionsProducer,
                                   figureCollection);
}

void FigureGenerator::valueTreeChildAdded(juce::ValueTree &parent,
                                          juce::ValueTree &childAdded)
{
    auto childType = childAdded.getType();

    if(childType == IDs::PARTICLES) {
        DBG("Particles added!!!!!!!");
        // when the particles sub-tree is added, create the particles collection
        // TODO: rename this to particleCollection
        particleCollectionMember =
            std::make_unique<ParticleCollection>(childAdded);
    }

    if(childType == IDs::PARTICLE) {
        jassert(particleCollectionMember != nullptr);

        auto particles = particleCollectionMember->getParticles();

        if(particles.size() > 1) {
            DBG("Got enough particles!!!!!!!!!");

            if(particleProducer == nullptr) {
                particleProducer =
                    std::make_unique<aleatoric::CollectionsProducer<Particle>>(
                        particles,
                        aleatoric::NumberProtocol::create(
                            aleatoric::NumberProtocol::Type::basic));

                auto paramType =
                    particleProducer->getParams().getActiveProtocol();

                if(paramType == aleatoric::NumberProtocolParameters::Protocols::
                                    ActiveProtocol::basic) {
                    DBG("protocol type is basic");
                }
            }

            // remove the UI figure gen blocked message (may need to check if it
            // already exists first)

            // add the components for generating figures (setVisible())

            // add the FigureParticleSelection component and pass it the current
            // params for the producer

            // also set its dropdown to the currently used protocol (basic in
            // this case)
        } else {
            DBG("Not enough particles!!!!!!!!!");
        }
    }

    // TODO: Add listener for removal of child trees (particle) and reverse the
    // above
}
