#include "Figures.h"

Figures::Figures(te::Engine &e, juce::ValueTree &as)
: engine(e),
  appState(as),
  sequencer(engine, appState),
  figureGenerator(appState),
  figureManager(appState)
{
    addAndMakeVisible(&figureGenerator);
    addAndMakeVisible(&figureManager);
    addAndMakeVisible(&sequencer);

    heading.setText("Figures", juce::dontSendNotification);
    heading.setFont(juce::Font(24.0f, juce::Font::bold));
    addAndMakeVisible(&heading);

    // TODO: Data management: This is a hack. Ideally this component would
    // listen to a value tree to know a figure has been added and then get a
    // Figure data object and call the sequencer with it.
    figureGenerator.generateButton.onClick = [this] {
        generateAndArrangeFigure();
    };
}

Figures::~Figures()
{}

void Figures::paint(juce::Graphics &g)
{}

void Figures::resized()
{
    auto area = getLocalBounds();

    auto headingArea = area.removeFromTop(50);
    heading.setBounds(headingArea.removeFromLeft(250));

    auto heightUnit = area.getHeight() / 3;
    auto figureControlArea = area.removeFromTop(heightUnit);

    auto figureManagerAreaColUnit = figureControlArea.getWidth() / 3.0;

    figureManager.setBounds(
        figureControlArea.removeFromRight(figureManagerAreaColUnit));

    figureGenerator.setBounds(figureControlArea);

    sequencer.setBounds(area);
}

void Figures::generateAndArrangeFigure()
{
    auto figure = figureGenerator.generateFigure();
    sequencer.readFigure(figure);
}
