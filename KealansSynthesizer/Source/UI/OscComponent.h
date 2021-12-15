/*
  ==============================================================================

    OscComponent.h
    Created: 7 Dec 2021 6:25:00pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	// box for the osc selector
	juce::ComboBox oscWaveSelector;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

	juce::Slider fmFrequencySlider;
	juce::Slider fmDepthSlider;

	using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	std::unique_ptr<Attachment> fmFrequencyAttachment;
	std::unique_ptr<Attachment> fmDepthAttachment;

	juce::Label fmFrequencyLabel{ "FM Freq", "FM Freq" };
	juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

	void setSliderWithLabel(juce::Slider& slider, juce::Label& label,
		juce::AudioProcessorValueTreeState& apvts, juce::String paramId,
		std::unique_ptr<Attachment>& attachment);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
