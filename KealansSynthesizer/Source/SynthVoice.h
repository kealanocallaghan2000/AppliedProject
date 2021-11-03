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

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override; // returns true if object is capable of playing sound
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override; // called to start a new note
	void stopNote(float velocity, bool allowTailOff) override; // called to stop a note
	void controllerMoved(int controllerNumber, int newControllerValue) override; // called to let the voice object know that controller was moved
	void renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override; // renders the next block of data for this voice
	void pitchWheelMoved(int newPitchWheelValue)  override; // call to let voice object know the pitch wheel has been moved


private:
};