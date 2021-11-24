/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
//==============================================================================
/**
*/
class KealansSynthesizerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KealansSynthesizerAudioProcessorEditor (KealansSynthesizerAudioProcessor&);
    ~KealansSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
	juce::Slider attackSlider;
	juce::Slider decaySlider;
	juce::Slider sustainSlider;
	juce::Slider releaseSlider;
	juce::ComboBox oscSelector;

	KealansSynthesizerAudioProcessor& audioProcessor; // reference toplugin processor (access to apvts)

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; // code to shorten the below attachments

	// attachments to connect the front end sliders to the plugin processor
	// uses the unique pointer to free up memory
	std::unique_ptr<SliderAttachment> attackAttachment;
	std::unique_ptr<SliderAttachment> decayAttachment;
	std::unique_ptr<SliderAttachment> sustainAttachment;
	std::unique_ptr<SliderAttachment> releaseAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KealansSynthesizerAudioProcessorEditor)
};
