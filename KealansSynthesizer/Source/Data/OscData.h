/*
  ==============================================================================

    OscData.h
    Created: 7 Dec 2021 4:30:41pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float> // ineherits from the juce oscillator class
{
public:
	// set oscillator wave type
	void setWaveType(const int choice);
	void prepareToPlay(juce::dsp::ProcessSpec& spec); // future proofing
	void setWaveFrequency(const int midiNoteNumber);
	void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

private:



};
