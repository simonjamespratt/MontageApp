#include "SliderWithLabel.h"

SliderWithLabel::SliderWithLabel(double &value,
                                 juce::String labelText,
                                 double rangeMin,
                                 double rangeMax,
                                 juce::String unit,
                                 int decimalPlacesToDisplay,
                                 int textBoxWidth)
: m_value(value)
{
    slider.setRange(rangeMin, rangeMax);
    slider.setValue(m_value);
    slider.onValueChange = [this] {
        m_value = slider.getValue();
    };

    if(unit != "") {
        slider.setTextValueSuffix(" " + unit);
    }

    if(decimalPlacesToDisplay != -1) {
        slider.setNumDecimalPlacesToDisplay(decimalPlacesToDisplay);
    }

    if(textBoxWidth != -1) {
        slider.setTextBoxStyle(juce::Slider::TextBoxLeft,
                               false,
                               textBoxWidth,
                               slider.getTextBoxHeight());
    }

    addAndMakeVisible(&slider);

    label.setText((labelText + ": "), juce::dontSendNotification);
    label.attachToComponent(&slider, true);
    addAndMakeVisible(&label);
}

void SliderWithLabel::resized()
{
    auto margin = 10;
    auto area = getLocalBounds();
    area.removeFromLeft(100); // label gutter
    slider.setBounds(area.reduced(margin));
}
