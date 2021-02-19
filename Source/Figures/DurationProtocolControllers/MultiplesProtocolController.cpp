#include "MultiplesProtocolController.h"

void MultiplesProtocolController::Container::resized()
{
    int componentHeight = 45;

    auto totalHeight = getNumChildComponents() * componentHeight;
    setSize(getWidth(), totalHeight);

    auto area = getLocalBounds();

    for(auto *child : getChildren()) {
        child->setBounds(area.removeFromTop(componentHeight));
    }
}

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
                        50)
{
    container.addAndMakeVisible(&baseIncrementEditor);
    container.addAndMakeVisible(&deviationFactorEditor);
    container.addAndMakeVisible(&rangeStartEditor);
    container.addAndMakeVisible(&rangeEndEditor);

    holdingForMultiples.setText("Holding for multiples",
                                juce::dontSendNotification);
    container.addChildComponent(&holdingForMultiples);

    viewport.setViewedComponent(&container, false);
    viewport.setScrollBarsShown(true, false);
    addAndMakeVisible(&viewport);

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
    auto area = getLocalBounds();

    // params
    auto paramsArea = area.removeFromLeft(250);
    container.setBounds(paramsArea);
    viewport.setBounds(paramsArea);

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));

    multipliersSelectionHeading.setBounds(
        area.removeFromTop(45).reduced(margin));

    multipliersByRange.setBounds(area.removeFromTop(45).reduced(margin));
    multipliersByHand.setBounds(area.removeFromTop(45).reduced(margin));
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
        holdingForMultiples.setVisible(newState);
    }

    if(name == "RANGE") {
        auto newState = button->getToggleState();
        rangeStartEditor.setVisible(newState);
        rangeEndEditor.setVisible(newState);
    }
}
