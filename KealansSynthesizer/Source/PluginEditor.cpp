/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KealansSynthesizerAudioProcessorEditor::KealansSynthesizerAudioProcessorEditor (KealansSynthesizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	// attachments for front end
	attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attackSlider);
	decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
	sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
	releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", releaseSlider);

	oscSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);

	// calling method below
	setSliderParams(attackSlider);
	setSliderParams(decaySlider);
	setSliderParams(sustainSlider);
	setSliderParams(releaseSlider);

}

KealansSynthesizerAudioProcessorEditor::~KealansSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void KealansSynthesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void KealansSynthesizerAudioProcessorEditor::resized()
{
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getWidth() / 4 - padding;
	const auto sliderStartX = 0;
	const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
	decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

// method to make setting slider parameters less bulky
void KealansSynthesizerAudioProcessorEditor::setSliderParams(juce::Slider& slider) // apersand means reference
{
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);
}
