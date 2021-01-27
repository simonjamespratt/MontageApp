#include "DurationProtocolSelector.h"

#include "DurationProtocolConfig.h"

DurationProtocolSelector::DurationProtocolSelector(
    std::shared_ptr<aleatoric::DurationsProducer> durationsProducer)
: producer(durationsProducer)
{
    protocolSelectorLabel.setText("Durations strategy: ",
                                  juce::dontSendNotification);
    addAndMakeVisible(&protocolSelectorLabel);

    addAndMakeVisible(&protocolSelector);
    configureProtocolSelector();
}

void DurationProtocolSelector::paint(juce::Graphics &g)
{}

void DurationProtocolSelector::resized()
{
    auto area = getLocalBounds();
    auto margin = 10;
    auto chooseProtocolArea = area.removeFromTop(45);
    auto protocolColWidth = chooseProtocolArea.getWidth() / 2;
    protocolSelectorLabel.setBounds(
        chooseProtocolArea.removeFromLeft(protocolColWidth).reduced(margin));
    protocolSelector.setBounds(chooseProtocolArea.reduced(margin));

    auto controlsArea = area;

    // TODO: set the controller area if controller exists
}

// Private methods
void DurationProtocolSelector::configureProtocolSelector()
{
    for(auto &&config : DurationProtocolConfig::getConfigurations()) {
        protocolSelector.addItem(config.getName(), config.getId());
    }
}
