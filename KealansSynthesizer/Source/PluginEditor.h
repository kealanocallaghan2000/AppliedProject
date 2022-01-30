/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI//OscComponent.h"
#include "UI/FilterComponent.h"


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
	KealansSynthesizerAudioProcessor& audioProcessor; // reference toplugin processor (access to apvts)
	OscComponent osc; // declaringb the oscillator component
	AdsrComponent adsr; // reference to the sliders in AdsrComponent.h
	FilterComponent filter;
	AdsrComponent modAdsr;
	


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KealansSynthesizerAudioProcessorEditor)
};
