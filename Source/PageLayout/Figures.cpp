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

    generateButton.setButtonText("Generate");
    // TODO: Generate button should not be visible when there aren't enough
    // particles to make figure. This is another good reason why this should be
    // in the figure generator component
    addAndMakeVisible(&generateButton);
    generateButton.onClick = [this] {
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
    generateButton.setBounds(headingArea.removeFromLeft(200).reduced(10));

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
