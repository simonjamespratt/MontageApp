#include "PrescribedProtocolController.h"

#include <iterator>

NumericItemEditor::NumericItemEditor(int &value,
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

void NumericItemEditor::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    valueEditor.setBounds(area.removeFromLeft(150));
    deleteButton.setBounds(area.reduced(margin));
}

// ==========================================================================

NumericCollectionEditor::NumericCollectionEditor(
    std::vector<int> &numericCollection)
: collection(numericCollection)
{
    drawView();
}

void NumericCollectionEditor::resized()
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

// Private methods
void NumericCollectionEditor::drawView()
{
    for(auto it = begin(collection); it != end(collection); ++it) {
        int index = std::distance(collection.begin(), it);
        auto editor =
            std::make_unique<NumericItemEditor>(*it, index, [this](int index) {
                onDelete(index);
            });
        addAndMakeVisible(*editor);
        editors.emplace_back(std::move(editor));
    }
}

void NumericCollectionEditor::onDelete(int index)
{
    editors.clear();
    collection.erase(collection.begin() + index);
    drawView();
    resized();
}

void NumericCollectionEditor::onAdd()
{
    editors.clear();
    collection.emplace_back(1);
    drawView();
    resized();
}

// =====================================================

PrescribedProtocolController::PrescribedProtocolController(
    DurationProtocolParams &params,
    std::shared_ptr<aleatoric::DurationsProducer> producer)
: m_params(params),
  m_producer(producer),
  durationsEditor(m_params.prescribed.durations)
{
    viewport.setViewedComponent(&durationsEditor, false);
    viewport.setScrollBarsShown(true, false);
    addAndMakeVisible(&viewport);

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
    durationsEditor.setBounds(viewsArea);

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

// TODO: When button is in DurationViewContainer, bin this
void PrescribedProtocolController::onAdd()
{
    durationsEditor.onAdd();
}
