/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KealansSynthesizerAudioProcessorEditor::KealansSynthesizerAudioProcessorEditor (KealansSynthesizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC1WAVETYPE"), adsr(audioProcessor.apvts) // passing in apvts as constructor
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
	//make adsr & osc visible
	addAndMakeVisible(adsr);
	addAndMakeVisible(osc);
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
	// set adsr & osc bounds
	osc.setBounds(10, 20, 100, 30);
	adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

