/*
  ==============================================================================

    AdsrComponent.h
    Created: 4 Dec 2021 11:32:31pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId); // passing in apvts as constructor
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
	void setSliderParams(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; // code to shorten the below attachments

	// attachments to connect the front end sliders to the plugin processor
	// uses the unique pointer to free up memory
	std::unique_ptr<SliderAttachment> attackAttachment;
	std::unique_ptr<SliderAttachment> decayAttachment;
	std::unique_ptr<SliderAttachment> sustainAttachment;
	std::unique_ptr<SliderAttachment> releaseAttachment;

	// Taken from pluginEditor.h
	juce::Slider attackSlider;
	juce::Slider decaySlider;
	juce::Slider sustainSlider;
	juce::Slider releaseSlider;

	juce::Label attackLabel{ "Attack", "A" };
	juce::Label decayLabel{ "Decay", "D" };
	juce::Label sustainLabel{ "Sustain", "S" };
	juce::Label releaseLabel{ "Release", "R" };

	juce::String componentName{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
