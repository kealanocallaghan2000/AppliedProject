/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"

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
	juce::ComboBox oscSelector;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
	KealansSynthesizerAudioProcessor& audioProcessor; // reference toplugin processor (access to apvts)
	AdsrComponent adsr; // reference to the sliders in AdsrComponent.h


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KealansSynthesizerAudioProcessorEditor)
};
