/*
  ==============================================================================

    SynthVoice.h
    Created: 3 Nov 2021 2:55:41pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"


// inheriting from the Juce Class SynthesiserVoice
class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override; // returns true if object is capable of playing sound
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override; // called to start a new note
	void stopNote(float velocity, bool allowTailOff) override; // called to stop a note
	void controllerMoved(int controllerNumber, int newControllerValue) override; // called to let the voice object know that controller was moved
	void renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override; // renders the next block of data for this voice
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels); // no override
	void pitchWheelMoved(int newPitchWheelValue)  override; // call to let voice object know the pitch wheel has been moved

	void updateAdsr(const float attack, const float decay, const float sustain, const float release);
	void updateFilter(const int filterType, const float cutoff, const float resonance);
	void updateModAdsr(const float attack, const float decay, const float sustain, const float release);

	OscData& getOscillator() { return osc; }


private:
	juce::AudioBuffer<float> synthBuffer; // audio buffer to prevent clicking

	OscData osc; // instance of our own oscillator data class
	AdsrData adsr;
	FilterData filter;
	AdsrData modAdsr;
	juce::dsp::Gain<float> gain;


	bool isPrepared{ false };
};