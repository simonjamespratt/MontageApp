/*
  ==============================================================================

    Sequencer.h
    Created: 13 Mar 2019 7:34:49pm
    Author:  Simon Pratt

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "./Timeline.h"
#include "./Cursor.h"
#include "./Arrangement.h"
#include "./TimeDisplay.h"
#include "./TransportInteractor.h"

namespace te = te;

//==============================================================================
/*
*/
class Sequencer : public Component, public ChangeListener
{
public:
  Sequencer(te::Engine &eng);
  ~Sequencer();

  void resized() override;

private:
  te::Engine &engine;
  // NB: note that the edit is set up with en empty edit rather than by referencing a file to write to
  // when the sequencer is working seriously, probably need to change this
  te::Edit edit;
  te::TransportControl &transport;

  TextButton loadFileButton;
  TextButton playPauseButton;
  TextButton stopButton;
  TimeDisplay transportPosition;
  Timeline timeline;
  Arrangement arrangement;
  Cursor cursor;
  TransportInteractor transportInteractor;

  void selectAudioFile();

  void changeListenerCallback(ChangeBroadcaster *) override;
  void togglePlayPause();
  void stop();
  void updatePlayPauseButtonText();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sequencer)
};
