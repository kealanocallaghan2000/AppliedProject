/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KealansSynthesizerAudioProcessorEditor::KealansSynthesizerAudioProcessorEditor (KealansSynthesizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr(audioProcessor.apvts) // passing in apvts as constructor
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
	
	oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);
	
	//make adsr visible
	addAndMakeVisible(adsr);
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
	// set adsr bounds
	adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

