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
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts) // passing in apvts as constructor
{
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	// attachments for front end
	attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
	decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
	sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
	releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);

	// calling methods and passing in slider reference
	setSliderParams(attackSlider);
	setSliderParams(decaySlider);
	setSliderParams(sustainSlider);
	setSliderParams(releaseSlider);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

// Sets the sizes and bounds for the sliders and box of the synth interface
void AdsrComponent::resized()
{
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getHeight();
	const auto sliderStartX = 0;
	const auto sliderStartY = 0;

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
	decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

// method to make setting slider parameters less bulky
void AdsrComponent::setSliderParams(juce::Slider& slider) // apersand means reference
{
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);
}
