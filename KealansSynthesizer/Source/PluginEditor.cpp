/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KealansSynthesizerAudioProcessorEditor::KealansSynthesizerAudioProcessorEditor (KealansSynthesizerAudioProcessor& p)
    : AudioProcessorEditor (&p)
	, audioProcessor (p)
	, osc(audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQUENCY", "OSC1FMDEPTH")
	, adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE") // passing in apvts as constructor
	, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (620, 500);
	//make adsr & osc visible
	addAndMakeVisible(adsr);
	addAndMakeVisible(osc);
	addAndMakeVisible(filter);
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
	const auto paddingX = 5;
	const auto paddingY = 35;

	const auto paddingBottomY = 235;

	// set adsr & osc bounds
	osc.setBounds(paddingX, paddingY, 300, 200);
	filter.setBounds(osc.getRight(), paddingY, 300, 200);
	adsr.setBounds(paddingX, paddingBottomY, 300, 200);
}

