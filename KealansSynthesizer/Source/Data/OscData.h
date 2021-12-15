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
	void setFmParams(const float depth, const float frequency);

private:
	juce::dsp::Oscillator<float> fmOscillator{ [](float x) { return std::sin(x); } }; // fm oscillator is a sine wave
	float fmMod{ 0.0f };
	float fmDepth{ 0.0f };
	int lastMidiNote{ 0 };


};
