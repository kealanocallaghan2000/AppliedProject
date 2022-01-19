/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 4 Dec 2021 11:32:31pm
    Author:  keala

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId) // passing in apvts as constructor
{
	componentName = name;

	// calling methods and passing in slider reference
	setSliderParams(attackSlider, attackLabel, apvts, attackId, attackAttachment);
	setSliderParams(decaySlider, decayLabel, apvts, decayId, decayAttachment);
	setSliderParams(sustainSlider, sustainLabel, apvts, sustainId, sustainAttachment);
	setSliderParams(releaseSlider, releaseLabel, apvts, releaseId, releaseAttachment);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
	auto bounds = getLocalBounds().reduced(5);
	auto labelSpace = bounds.removeFromTop(25.0f);

	g.fillAll(juce::Colours::black);
	g.setColour(juce::Colours::white);
	g.setFont(20.0f);
	g.drawText(componentName, labelSpace.withX(5), juce::Justification::left);
	g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

// Sets the sizes and bounds for the sliders and box of the synth interface
void AdsrComponent::resized()
{
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getHeight() - 45;
	const auto sliderStartX = padding + 5;
	const auto sliderStartY = 55;

	const auto labelYOffset = 20;
	const auto labelHeight = 20;
	const auto labelStart = sliderStartY - labelYOffset;

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
	attackLabel.setBounds(attackSlider.getX(), labelStart, sliderWidth, labelHeight);

	decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	decayLabel.setBounds(decaySlider.getX(), labelStart, sliderWidth, labelHeight);

	sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sustainLabel.setBounds(sustainSlider.getX(), labelStart, sliderWidth, labelHeight);

	releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	releaseLabel.setBounds(releaseSlider.getX(), labelStart, sliderWidth, labelHeight);

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

// method to make setting slider parameters less bulky
void AdsrComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment) // apersand means reference
{
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);

	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
	label.setFont(15.0f);
	label.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(label);
}
