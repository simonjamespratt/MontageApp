#include "NumberProtocolSelector.h"

#include "ProtocolConfig.h"

NumberProtocolSelector::NumberProtocolSelector(
    std::shared_ptr<aleatoric::CollectionsProducer<Particle>> particleProducer)
: m_particleProducer(particleProducer)
{
    initialise();
}

NumberProtocolSelector::NumberProtocolSelector(
    std::shared_ptr<aleatoric::DurationsProducer> durationsProducer)
: m_durationsProducer(durationsProducer)
{
    initialise();
}

NumberProtocolSelector::~NumberProtocolSelector()
{}

void NumberProtocolSelector::paint(juce::Graphics &g)
{}

void NumberProtocolSelector::resized()
{
    auto area = getLocalBounds();
    auto margin = 10;
    auto chooseProtocolArea = area.removeFromTop(45);
    auto protocolColWidth = chooseProtocolArea.getWidth() / 2;
    protocolSelectorLabel.setBounds(
        chooseProtocolArea.removeFromLeft(protocolColWidth).reduced(margin));
    protocolSelector.setBounds(chooseProtocolArea.reduced(margin));

    auto controlsArea = area;

    if(controller != nullptr) {
        controller->setBounds(controlsArea);
    }
}

void NumberProtocolSelector::resetParams()
{
    if(controller != nullptr) {
        if(m_particleProducer != nullptr) {
            controller->setParams(m_particleProducer->getParams());
        }
    }
}

// Private methods
void NumberProtocolSelector::initialise()
{
    protocolSelectorLabel.setText("Selection strategy: ",
                                  juce::dontSendNotification);
    addAndMakeVisible(&protocolSelectorLabel);

    addAndMakeVisible(&protocolSelector);
    configureProtocolSelector();
    protocolSelector.onChange = [this] {
        protocolChanged();
    };
    setInitialActiveProtocol();
}

void NumberProtocolSelector::configureProtocolSelector()
{
    for(auto &&config : ProtocolConfig::getConfigurations()) {
        protocolSelector.addItem(config.getName(), config.getId());
    }
}

void NumberProtocolSelector::protocolChanged()
{
    using namespace aleatoric;

    auto id = protocolSelector.getSelectedId();
    auto selectedConfig = ProtocolConfig::findById(id);

    if(m_particleProducer != nullptr) {
        m_particleProducer->setProtocol(
            NumberProtocol::create(selectedConfig.getProtocolType()));

        controller =
            NumberProtocolController::create(selectedConfig.getProtocolType(),
                                             m_particleProducer->getParams());
    }

    controller->attach(
        [this](aleatoric::NumberProtocolParameters::Protocols newParams) {
            updateParams(newParams);
        });

    addAndMakeVisible(*controller);
    resized();
}

void NumberProtocolSelector::updateParams(
    aleatoric::NumberProtocolParameters::Protocols newParams)
{
    if(m_particleProducer != nullptr) {
        m_particleProducer->setParams(newParams);
    }
}

void NumberProtocolSelector::setInitialActiveProtocol()
{
    if(m_particleProducer != nullptr) {
        auto activeProtocol =
            m_particleProducer->getParams().getActiveProtocol();
        auto config = ProtocolConfig::findByActiveProtocol(activeProtocol);
        protocolSelector.setSelectedId(config.getId(),
                                       juce::dontSendNotification);
    }
}
