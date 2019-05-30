/*
  ==============================================================================

    Sequencer.cpp
    Created: 13 Mar 2019 7:34:49pm
    Author:  Simon Pratt

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sequencer.h"

//==============================================================================
Sequencer::Sequencer(te::Engine &eng, ValueTree &as) : engine(eng),
                                                       edit(engine, te::createEmptyEdit(), te::Edit::forEditing, nullptr, 0),
                                                       transport(edit.getTransport()),
                                                       appState(as),
                                                       timeline(edit),
                                                       arrangement(edit, transport),
                                                       cursor(transport, edit),
                                                       transportInteractor(transport, edit),
                                                       transportController(transport)
{
    noOfTracks = 0;

    addAndMakeVisible(&timeline);
    addAndMakeVisible(&arrangement);
    addAndMakeVisible(&cursor);
    addAndMakeVisible(&transportInteractor);
    addAndMakeVisible(&transportController);
}

Sequencer::~Sequencer()
{
    edit.getTempDirectory(false).deleteRecursively();
}

void Sequencer::paint(Graphics &g)
{
}

void Sequencer::resized()
{
    auto area = getLocalBounds();
    area.removeFromTop(10);
    area.removeFromRight(10);
    area.removeFromBottom(10);
    area.removeFromLeft(10);
    auto transportArea = area.removeFromBottom(50);
    auto timelineArea = area.removeFromTop(20);
    auto arrangementArea = area;

    timeline.setBounds(timelineArea);
    arrangement.setBounds(arrangementArea);
    cursor.setBounds(arrangementArea);
    transportInteractor.setBounds(arrangementArea);
    transportController.setBounds(transportArea);
}

void Sequencer::readFigure(ValueTree &figure)
{
    std::vector<ClipData> clips;
    int noOfFigureEvents = figure.getNumChildren();
    auto sources = appState.getChildWithName(sourcesIdentifier);
    auto particles = appState.getChildWithName(particlesIdentifier);
    int noOfParticles = particles.getNumChildren();
    prepareForNewFigure(noOfParticles);

    for (int i = 0; i < noOfFigureEvents; i++)
    {
        // unpack each figure event value tree:- particleId, onset
        auto currentFigure = figure.getChild(i);

        int particleId = int(currentFigure[figureEventPropParticleIdIdentifier]);
        auto particle = particles.getChildWithProperty(particlePropIdIdentifier, particleId);
        double particleRangeStart = double(particle[particlePropRangeStartIdentifier]);
        double particleRangeEnd = double(particle[particlePropRangeEndIdentifier]);

        int trackIndex = particleId - 1;
        double clipStart = double(currentFigure[figureEventPropOnsetIdentifier]);
        double clipEnd = (particleRangeEnd - particleRangeStart) + clipStart;
        double offset = particleRangeStart;
        int sourceId = int(particle[particlePropIdIdentifier]);
        auto requestedSource = sources.getChildWithProperty(sourcePropIdIdentifier, sourceId);

        if (requestedSource.isValid())
        {
            FileManager fileManager;
            fileManager.loadExistingSourceFile(requestedSource);

            if (!fileManager.fileIsValid())
            {
                showErrorMessaging(FileInvalid);
                return;
            }

            auto file = fileManager.getFile();
            auto clip = addClipToTrack(file, trackIndex, clipStart, clipEnd, offset);
            clips.push_back({clip,
                             trackIndex,
                             clipStart,
                             clipEnd,
                             offset});
        }
    }

    for (auto &&entry : clips)
    {
        arrangement.addClipToArrangement(entry.clip, entry.trackIndex, entry.clipStart, entry.clipEnd, entry.offset);
    }

    timeline.recalculate();
    transport.position = 0.0;
    transport.play(false);
}

void Sequencer::showErrorMessaging(const ErrorType &errorType)
{
    std::make_shared<ErrorManager>(errorType);
}

void Sequencer::prepareForNewFigure(int noOfParticles)
{
    // for each track in use from the last figure, remove all clips
    for (int i = 0; i < noOfTracks; i++)
    {
        auto track = edit.getOrInsertAudioTrackAt(i);
        auto clipsToRemove = track->getClips();
        for (int i = clipsToRemove.size(); --i >= 0;)
        {
            clipsToRemove.getUnchecked(i)->removeFromParentTrack();
        }
    }

    // set the no of tracks required for the incoming figure
    noOfTracks = noOfParticles;
    // prepare the new tracks
    prepareTracks();
    arrangement.prepareArrangement(noOfTracks);

    // NB: find a way to delete audio tracks from edit: cannot see a good way to this at the moment, which means there will be empty unused tracks in the ether
    // these unused tracks will not have clips on them because clips will be cleared from all previously used tracks in this method
    // they will also not be displayed as display is the result of the noOfTracks member of this class
    // but they will still just be hanging around
}

void Sequencer::prepareTracks()
{
    for (int i = 0; i < noOfTracks; i++)
    {
        edit.getOrInsertAudioTrackAt(i);
    }
    repaint();
}

juce::ReferenceCountedObjectPtr<tracktion_engine::WaveAudioClip> Sequencer::addClipToTrack(const File &file, const int trackIndex, const double &clipStart, const double &clipEnd, const double &offset)
{
    /*
        NB: ClipPosition has the following structure: { {startClip, endClip}, offset }
        Where the above mean:
        - startClip: the start position of the clip as placed on the track, e.g. 1.0 would mean the clip starts at 1 second from the beginning of the transport start
        - endClip: the end of the clip; the difference between clipEnd and clipStart gives you the length of the clip
        - offset: the start of the clip in relation to the start of the audio file, e.g. 1.0 would mean the clip start is 1 second from the beginning of the audio file

        Mapping figure and particle value trees to a ClipPosition:
        - particle.rangeStart -> ClipPosition.offset
        - figure.figureEvent.onset -> ClipPosition.clipStart
        - (particle.rangeEnd - particle.rangeStart) + ClipPosition.clipStart -> ClipPosition.clipEnd
    */
    auto track = edit.getOrInsertAudioTrackAt(trackIndex);
    auto newClip = track->insertWaveClip(
        file.getFileNameWithoutExtension(),
        file,
        {{clipStart, clipEnd}, offset},
        false);

    return newClip;
}
