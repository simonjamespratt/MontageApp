#include "NumberProtocolSelector.h"

#include "NumberProtocolConfig.h"

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
    for(auto &&config : NumberProtocolConfig::getConfigurations()) {
        protocolSelector.addItem(config.getName(), config.getId());
    }
}

void NumberProtocolSelector::protocolChanged()
{
    using namespace aleatoric;

    auto id = protocolSelector.getSelectedId();
    auto selectedConfig = NumberProtocolConfig::findById(id);

    if(m_particleProducer != nullptr) {
        m_particleProducer->setProtocol(
            NumberProtocol::create(selectedConfig.getProtocolType()));

        controller =
            NumberProtocolController::create(selectedConfig.getProtocolType(),
                                             m_particleProducer->getParams());
    }

    if(m_durationsProducer != nullptr) {
        m_durationsProducer->setNumberProtocol(
            NumberProtocol::create(selectedConfig.getProtocolType()));

        controller =
            NumberProtocolController::create(selectedConfig.getProtocolType(),
                                             m_durationsProducer->getParams());
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

    if(m_durationsProducer != nullptr) {
        m_durationsProducer->setParams(newParams);
    }
}

void NumberProtocolSelector::setInitialActiveProtocol()
{
    aleatoric::NumberProtocolParameters::Protocols::ActiveProtocol
        activeProtocol;

    if(m_particleProducer != nullptr) {
        activeProtocol = m_particleProducer->getParams().getActiveProtocol();
    }

    if(m_durationsProducer != nullptr) {
        activeProtocol = m_durationsProducer->getParams().getActiveProtocol();
    }

    auto config = NumberProtocolConfig::findByActiveProtocol(activeProtocol);
    protocolSelector.setSelectedId(config.getId(), juce::dontSendNotification);
}
