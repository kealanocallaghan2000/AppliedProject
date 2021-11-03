/*
  ==============================================================================

    SynthSound.h
    Created: 3 Nov 2021 2:56:16pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
	bool appliesToNote(int midiNoteNumber) override // returns true if sound should be played when midi is pressed
	{
		return true;
	}
	bool appliesToChannel(int midiChannel) override // returns true if sound should be triggered by midi events on a given channel
	{
		return true;
	}
};
