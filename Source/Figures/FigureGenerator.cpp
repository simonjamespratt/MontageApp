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
    if(figureParticleSelection != nullptr) {
        figureParticleSelection->setBounds(particleSelectionArea);
    }

    auto onsetSelectionArea = area;
    onsetSelectionHeading.setBounds(onsetSelectionArea.removeFromTop(50));
}

Figure FigureGenerator::generateFigure()
{
    using namespace aleatoric;

    jassert(particleProducer != nullptr);

    auto figureCollectionState = appState.getChildWithName(IDs::FIGURES);
    FigureCollection figureCollection(figureCollectionState);

    auto numOfEventsToMake = numEventsInput.getText().getIntValue();

    // TODO: replace this with user error message
    jassert(numOfEventsToMake > 0);

    // TODO: delete this when UI for selection of protocol etc. is in place
    // Basic predictable results using prescribed durations and cycling of
    // durations
    std::vector<int> durations {1000, 2000};
    DurationsProducer durationsProducer(
        DurationProtocol::createPrescribed(durations),
        NumberProtocol::create(NumberProtocol::Type::cycle));

    FigureProcessor processor;
    return processor.composeFigure(numOfEventsToMake,
                                   durationsProducer,
                                   *particleProducer,
                                   figureCollection);
}

void FigureGenerator::valueTreeChildAdded(juce::ValueTree &parent,
                                          juce::ValueTree &childAdded)
{
    auto childType = childAdded.getType();

    if(childType == IDs::PARTICLES) {
        // when the particles sub-tree is added, create the particles collection
        particleCollection = std::make_unique<ParticleCollection>(childAdded);
    }

    if(childType == IDs::PARTICLE) {
        jassert(particleCollection != nullptr);

        auto particles = particleCollection->getParticles();

        if(particles.size() > 1) {
            if(particleProducer == nullptr) {
                particleProducer =
                    std::make_shared<aleatoric::CollectionsProducer<Particle>>(
                        particles,
                        aleatoric::NumberProtocol::create(
                            aleatoric::NumberProtocol::Type::basic));
            } else {
                particleProducer->setSource(particles);
            }

            if(figureParticleSelection == nullptr) {
                figureParticleSelection =
                    std::make_unique<FigureParticleSelection>(particleProducer);
                addAndMakeVisible(*figureParticleSelection);
            } else {
                figureParticleSelection->resetParams();
            }

            blockedMessage.setVisible(false);
            globalSettingsHeading.setVisible(true);
            numEventsInput.setVisible(true);
            numEventsLabel.setVisible(true);
            onsetSelectionHeading.setVisible(true);

            resized();
        }
    }
}

void FigureGenerator::valueTreeChildRemoved(juce::ValueTree &parent,
                                            juce::ValueTree &childRemoved,
                                            int index)
{
    auto childType = childRemoved.getType();

    if(childType == IDs::PARTICLE) {
        jassert(particleCollection != nullptr);

        auto particles = particleCollection->getParticles();

        if(particles.size() < 2) {
            particleProducer = nullptr;
            figureParticleSelection = nullptr;

            blockedMessage.setVisible(true);
            globalSettingsHeading.setVisible(false);
            numEventsInput.setVisible(false);
            numEventsLabel.setVisible(false);
            onsetSelectionHeading.setVisible(false);

            resized();
        } else {
            particleProducer->setSource(particles);
            figureParticleSelection->resetParams();
        }
    }
}
