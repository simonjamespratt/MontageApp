#include "NumericCollectionEditor.h"

#include <iterator>

NumericItemEditor::NumericItemEditor(int &value,
                                     int index,
                                     std::function<void(int index)> onDelete)
: valueEditor(value, juce::String(index + 1), 25)
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

    addButton.setButtonText("Add value");
    addButton.onClick = [this] {
        onAdd();
    };
    addAndMakeVisible(&addButton);
}

void NumericCollectionEditor::resized()
{
    auto margin = 10;
    int componentHeight = 45;

    auto totalHeight = getNumChildComponents() * componentHeight;
    setSize(getWidth(), totalHeight);

    auto area = getLocalBounds();

    for(auto &&editor : editors) {
        editor->setBounds(area.removeFromTop(componentHeight));
    }

    addButton.setBounds(area.removeFromTop(componentHeight).reduced(margin));
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
