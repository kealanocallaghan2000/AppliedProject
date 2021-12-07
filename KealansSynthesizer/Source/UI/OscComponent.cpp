/*
  ==============================================================================

    OscComponent.cpp
    Created: 7 Dec 2021 6:25:00pm
    Author:  keala

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId) // combo box attachment needs access to apvts
{
	juce::StringArray choices{ "Sine", "Saw", "Square" };
	oscWaveSelector.addItemList(choices, 1);
	addAndMakeVisible(oscWaveSelector);

	oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
	oscWaveSelector.setBounds(0, 0, 90, 30);
}
