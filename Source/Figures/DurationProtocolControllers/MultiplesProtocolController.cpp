#include "MultiplesProtocolController.h"

MultiplesProtocolController::MultiplesProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  baseIncrementEditor(m_params.multiples.baseIncrement, "Base increment"),
  rangeStartEditor(m_params.multiples.rangeStart, "Range start"),
  rangeEndEditor(m_params.multiples.rangeEnd, "Range end"),
  deviationFactorEditor(m_params.multiples.deviationFactor,
                        "Deviation factor",
                        0,
                        100.0,
                        "%",
                        1,
                        50),
  multipliersByHandEditor(m_params.multiples.multipliers)
{
    addAndMakeVisible(&baseIncrementEditor);
    addAndMakeVisible(&deviationFactorEditor);
    addAndMakeVisible(&rangeStartEditor);
    addAndMakeVisible(&rangeEndEditor);

    // addChildComponent(&multipliersByHandEditor);

    multipliersByHandEditorViewport.setViewedComponent(&multipliersByHandEditor,
                                                       false);
    multipliersByHandEditorViewport.setScrollBarsShown(true, false);
    addChildComponent(&multipliersByHandEditorViewport);

    saveButton.setButtonText("Set protocol");
    saveButton.onClick = [this] {
        setProtocol();
    };
    addAndMakeVisible(&saveButton);

    multipliersSelectionHeading.setText("Multipliers",
                                        juce::dontSendNotification);
    addAndMakeVisible(&multipliersSelectionHeading);

    multipliersByRange.setRadioGroupId(multipliersRadioGroup);
    multipliersByHand.setRadioGroupId(multipliersRadioGroup);

    addAndMakeVisible(&multipliersByRange);
    addAndMakeVisible(&multipliersByHand);

    multipliersByRange.onClick = [this] {
        toggleMultiplierStrategy(&multipliersByRange, "RANGE");
    };
    multipliersByHand.onClick = [this] {
        toggleMultiplierStrategy(&multipliersByHand, "HAND");
    };

    multipliersByRange.setToggleState(true, juce::sendNotification);
}

void MultiplesProtocolController::paint(juce::Graphics &g)
{}

void MultiplesProtocolController::resized()
{
    auto margin = 10;
    auto marginSmall = 5;
    auto area = getLocalBounds();

    // params
    auto paramsArea = area.removeFromLeft(250);
    baseIncrementEditor.setBounds(paramsArea.removeFromTop(45));
    deviationFactorEditor.setBounds(paramsArea.removeFromTop(45));

    multipliersByHandEditorViewport.setBounds(paramsArea);

    rangeStartEditor.setBounds(paramsArea.removeFromTop(45));
    rangeEndEditor.setBounds(paramsArea.removeFromTop(45));

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));

    multipliersSelectionHeading.setBounds(
        area.removeFromTop(30).reduced(marginSmall));

    multipliersByRange.setBounds(area.removeFromTop(30).reduced(marginSmall));
    multipliersByHand.setBounds(area.removeFromTop(30).reduced(marginSmall));
}

// Private methods
void MultiplesProtocolController::setProtocol()
{
    DBG("dev factor: " << m_params.multiples.deviationFactor);
}

void MultiplesProtocolController::toggleMultiplierStrategy(juce::Button *button,
                                                           juce::String name)
{
    if(name == "HAND") {
        auto newState = button->getToggleState();
        multipliersByHandEditorViewport.setVisible(newState);
    }

    if(name == "RANGE") {
        auto newState = button->getToggleState();
        rangeStartEditor.setVisible(newState);
        rangeEndEditor.setVisible(newState);
    }
    resized();
}
