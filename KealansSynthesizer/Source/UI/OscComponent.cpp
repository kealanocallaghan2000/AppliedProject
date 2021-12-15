/*
  ==============================================================================

    OscComponent.cpp
    Created: 7 Dec 2021 6:25:00pm
    Author:  keala

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId) // combo box attachment needs access to apvts
{
	juce::StringArray choices{ "Sine", "Saw", "Square" };
	oscWaveSelector.addItemList(choices, 1);
	addAndMakeVisible(oscWaveSelector);

	oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);

	setSliderWithLabel(fmFrequencySlider, fmFrequencyLabel, apvts, fmFreqId, fmFrequencyAttachment);
	setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);
	// fmDepthSlider.setSliderStyle()
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
	const auto sliderWidth = 100;
	const auto sliderHeight = 90;
	const auto labelYOffset = 20;
	const auto labelHeight = 20;
	const auto sliderPosY = 80;

	oscWaveSelector.setBounds(0, 0, 90, 30);
	fmFrequencySlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
	fmFrequencyLabel.setBounds(fmFrequencySlider.getX(), fmFrequencySlider.getY() - labelYOffset, fmFrequencySlider.getWidth(), labelHeight);

	fmDepthSlider.setBounds(fmFrequencySlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
	fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, 
	juce::AudioProcessorValueTreeState& apvts, juce::String paramId,
	std::unique_ptr<Attachment>& attachment)
{
	slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);

	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::grey);
	label.setFont(15.0f);
	label.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(label);
}
