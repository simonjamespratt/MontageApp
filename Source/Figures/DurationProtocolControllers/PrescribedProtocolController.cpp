#include "PrescribedProtocolController.h"

#include <iterator>

DurationView::DurationView(int &value,
                           int index,
                           std::function<void(int index)> onDelete)
: valueEditor(value, juce::String(index + 1), 50)
{
    deleteButton.setButtonText("Delete");
    deleteButton.onClick = [index, onDelete] {
        onDelete(index);
    };

    addAndMakeVisible(&valueEditor);
    addAndMakeVisible(&deleteButton);
};

void DurationView::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    valueEditor.setBounds(area.removeFromLeft(150));
    deleteButton.setBounds(area.reduced(margin));
}

DurationViewContainer::DurationViewContainer()
{}

void DurationViewContainer::resized()
{
    int viewInstanceHeight = 45;

    auto height = getNumChildComponents() * viewInstanceHeight;
    setSize(getWidth(), height);

    auto area = getLocalBounds();

    auto children = getChildren();
    for(auto *child : children) {
        child->setBounds(area.removeFromTop(viewInstanceHeight));
    }
}

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params), m_producer(producer), durationViewContainer()
{
    viewport.setViewedComponent(&durationViewContainer, false);
    viewport.setScrollBarsShown(true, false);
    addAndMakeVisible(&viewport);
    drawView();

    saveButton.setButtonText("Set protocol");
    saveButton.onClick = [this] {
        setProtocol();
    };
    addAndMakeVisible(&saveButton);

    addButton.setButtonText("Add value");
    addButton.onClick = [this] {
        onAdd();
    };
    addAndMakeVisible(&addButton);
}

void PrescribedProtocolController::paint(juce::Graphics &g)
{}

void PrescribedProtocolController::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();

    auto viewsArea = area.removeFromLeft(250);
    viewport.setBounds(viewsArea);
    durationViewContainer.setBounds(viewsArea);

    saveButton.setBounds(area.removeFromTop(45).reduced(margin));
    addButton.setBounds(area.removeFromTop(45).reduced(margin));
}

// Private methods
void PrescribedProtocolController::setProtocol()
{
    for(auto &&i : m_params.prescribed.durations) {
        DBG("duration: " << i);
    }

    m_producer->setDurationProtocol(
        aleatoric::DurationProtocol::createPrescribed(
            m_params.prescribed.durations));
}

void PrescribedProtocolController::drawView()
{
    auto &durations = m_params.prescribed.durations;
    for(auto it = begin(durations); it != end(durations); ++it) {
        int index = std::distance(durations.begin(), it);
        auto view =
            std::make_unique<DurationView>(*it, index, [this](int index) {
                onDelete(index);
            });
        durationViewContainer.addAndMakeVisible(*view);
        durationViews.emplace_back(std::move(view));
    }
}

void PrescribedProtocolController::onDelete(int index)
{
    durationViews.clear();
    m_params.prescribed.durations.erase(m_params.prescribed.durations.begin() +
                                        index);
    drawView();
    durationViewContainer.resized();
}

void PrescribedProtocolController::onAdd()
{
    durationViews.clear();
    m_params.prescribed.durations.emplace_back(1);
    drawView();
    durationViewContainer.resized();
}
