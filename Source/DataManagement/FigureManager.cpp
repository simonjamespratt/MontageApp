#include "FigureManager.h"

FigureManager::FigureManager(juce::ValueTree &as)
: appState(as), table({}, this)
{
    heading.setText("Figure Manager", juce::dontSendNotification);
    heading.setFont(juce::Font(24.0f, juce::Font::bold));
    addAndMakeVisible(&heading);

    addAndMakeVisible(table);
    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);
    table.setOutlineThickness(1);
    table.setMultipleSelectionEnabled(false);

    // Add table columns to the header
    // this is cols for figure events: id, onset, particleId - do need the array
    for(int i = 0; i < dataTypes.size(); i++) {
        int columnId = i + 1;
        table.getHeader().addColumn(dataTypes[i].toString(),
                                    columnId,
                                    100,
                                    50,
                                    400);
    }

    // Set the appState data and then set the number of rows for the table
    appState.addListener(this);
    setData();
}

FigureManager::~FigureManager()
{}

void FigureManager::paint(juce::Graphics &g)
{}

void FigureManager::resized()
{
    auto area = getLocalBounds();
    auto headerArea = area.removeFromTop(50);
    area.removeFromRight(5);
    area.removeFromBottom(10);
    area.removeFromLeft(5);

    juce::FlexBox headerContainer;
    headerContainer.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    headerContainer.alignContent = juce::FlexBox::AlignContent::center;
    headerContainer.items.add(
        juce::FlexItem(heading).withHeight(24.0f).withWidth(200.0f).withMargin(
            juce::FlexItem::Margin(5.0f)));
    headerContainer.performLayout(headerArea);

    table.setBounds(area);
}

int FigureManager::getNumRows()
{
    return numRows;
}

void FigureManager::paintRowBackground(juce::Graphics &g,
                                       int rowNumber,
                                       int /*width*/,
                                       int /*height*/,
                                       bool rowIsSelected)
{
    auto alternateRowColour =
        getLookAndFeel()
            .findColour(juce::ListBox::backgroundColourId)
            .interpolatedWith(
                getLookAndFeel().findColour(juce::ListBox::textColourId),
                0.03f);

    if(rowIsSelected) {
        g.fillAll(juce::Colours::lightblue);
    } else if(rowNumber % 2) {
        g.fillAll(alternateRowColour);
    }
}

void FigureManager::paintCell(juce::Graphics &g,
                              int rowNumber,
                              int columnId,
                              int width,
                              int height,
                              bool rowIsSelected)
{
    g.setColour(rowIsSelected
                    ? juce::Colours::darkblue
                    : getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(14.0f);

    juce::ValueTree rowElement =
        figure.getChild(rowNumber); // this is a figure event
    if(rowElement.isValid()) {
        // get prop from figureEvent (rowElement) by comparing columnId to
        // dataType array position (columnId -1)
        auto propIdentifier = dataTypes[columnId - 1];

        if(rowElement.hasProperty(propIdentifier)) {
            auto cellData = rowElement.getProperty(propIdentifier);
            g.drawText(cellData,
                       2,
                       0,
                       width - 4,
                       height,
                       juce::Justification::centredLeft,
                       true);
        }
    }

    // draw RH-side column separator
    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

void FigureManager::backgroundClicked(const juce::MouseEvent &)
{
    table.deselectAllRows();
}

void FigureManager::setData()
{
    figures = (appState.getChildWithName(IDs::FIGURES));
    figure = (figures.getChild(0)); // NB: when there are more than one figure
                                    // in figures, this will need changing
    numRows = figure.getNumChildren(); // this should be ok because it only
                                       // counts child trees, not direct props
}

// ========================================================
// ValueTree listeners
void FigureManager::valueTreeChildAdded(juce::ValueTree &parentTree,
                                        juce::ValueTree &childWhichHasBeenAdded)
{
    setData();
    table.updateContent();
}

void FigureManager::valueTreeChildRemoved(
    juce::ValueTree &parentTree,
    juce::ValueTree &childWhichHasBeenRemoved,
    int indexFromWhichChildWasRemoved)
{
    setData();
    table.updateContent();
}

// -====================================================
// Unused listeners
void FigureManager::valueTreePropertyChanged(
    juce::ValueTree &treeWhosePropertyHasChanged,
    const juce::Identifier &property)
{}
void FigureManager::valueTreeChildOrderChanged(
    juce::ValueTree &parentTreeWhoseChildrenHaveMoved,
    int oldInex,
    int newIndex)
{}
void FigureManager::valueTreeParentChanged(
    juce::ValueTree &treeWhoseParentHasChanged)
{}
// =====================================================
