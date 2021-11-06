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
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)); // setting the frequency level
	adsr.noteOn(); // starts the attack of the envelopemk

}

void SynthVoice::stopNote(float velocity, bool allowTailOff) // called to stop a note
{
	adsr.noteOff(); // starts the release of the envelope
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) // called to let the voice object know that controller was moved
{

}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) // renders the next block of data for this voice
{
	jassert(isPrepared = true); // make sure prepareToPlay is called

	juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

	// process oscillator through the buffer
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	// osc process runs and audio block contains sine wave info
	// takes values and turns them down
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	adsr.setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock; // how big our sample size is
	spec.sampleRate = sampleRate; // sample rate of wave
	spec.numChannels = outputChannels; // number of output channels 

	osc.prepare(spec); // pass reference into oscillator

	gain.prepare(spec); // passing gain process spec

	gain.setGainLinear(0.4); // setting the linear gain (between 0 and 1)

	isPrepared = true; // lets us know that the prepare to play is initialized
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

