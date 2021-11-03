/*
  ==============================================================================

    SynthVoice.cpp
    Created: 3 Nov 2021 2:55:41pm
    Author:  keala

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) // returns true if object is capable of playing sound
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr; // returns synthesiserSound pointer and makes sure its not null (is loaded)
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) // called to start a new note
{

}
void SynthVoice::stopNote(float velocity, bool allowTailOff) // called to stop a note
{

}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) // called to let the voice object know that controller was moved
{

}
void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) // renders the next block of data for this voice
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

