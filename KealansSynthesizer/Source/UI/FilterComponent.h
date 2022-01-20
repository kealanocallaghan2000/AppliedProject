/*
  ==============================================================================

    FilterComponent.h
    Created: 19 Jan 2022 8:27:47pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::Slider filterFreqSlider;
	juce::Slider filterResSlider;
	juce::ComboBox filterTypeSelector{ "Filter Type" };
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

	using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	std::unique_ptr<Attachment> filterFreqAttachment;
	std::unique_ptr<Attachment> filterResAttachment;

	juce::Label filterSelectorLabel{ "Filter Type", "Filter Type" };
	juce::Label filterFreqLabel{ "Filter Freq", "Filter Freq" };
	juce::Label filterResLabel{ "Filter Resonance", "Filter Resonance" };


	void setSliderWithLabel(juce::Slider& slider, juce::Label& label,
		juce::AudioProcessorValueTreeState& apvts, juce::String paramId,
		std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
